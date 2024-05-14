#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <version.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/posix/unistd.h>
#include <zephyr/shell/shell.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>
#include <zephyr/usb/usb_device.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device* dev_sensor;

static inline float out_ev(struct sensor_value* val)
{
    return (val->val1 + (float)val->val2 / 1000000);
}

static void fetch_and_display(const struct device* dev)
{
    struct sensor_value x, y, z;
    static int trig_cnt;

    trig_cnt++;

    /* lsm6dso accel */
    sensor_sample_fetch_chan(dev, SENSOR_CHAN_ACCEL_XYZ);
    sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &x);
    sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Y, &y);
    sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Z, &z);

    printk("accel x:%f ms/2 y:%f ms/2 z:%f ms/2\n", (float)out_ev(&x), (float)out_ev(&y), (float)out_ev(&z));

    /* lsm6dso gyro */
    sensor_sample_fetch_chan(dev, SENSOR_CHAN_GYRO_XYZ);
    sensor_channel_get(dev, SENSOR_CHAN_GYRO_X, &x);
    sensor_channel_get(dev, SENSOR_CHAN_GYRO_Y, &y);
    sensor_channel_get(dev, SENSOR_CHAN_GYRO_Z, &z);

    printk("gyro x:%f rad/s y:%f rad/s z:%f rad/s\n", (float)out_ev(&x), (float)out_ev(&y), (float)out_ev(&z));

    printk("trig_cnt:%d\n\n", trig_cnt);
}

void timer_expired_handler(struct k_timer* timer)
{
    // fetch_and_display(dev_sensor);
    gpio_pin_toggle_dt(&led);
}

K_TIMER_DEFINE(log_timer, timer_expired_handler, NULL);

static int cmd_version(const struct shell* sh, size_t argc, char** argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    shell_print(sh, "Zephyr version %s", KERNEL_VERSION_STRING);

    return 0;
}

SHELL_CMD_ARG_REGISTER(version, NULL, "Show kernel version", cmd_version, 1, 0);

static int set_sampling_freq(const struct device* dev)
{
    int ret = 0;
    struct sensor_value odr_attr;

    /* set accel/gyro sampling frequency to 12.5 Hz */
    odr_attr.val1 = 12;
    odr_attr.val2 = 500000;

    ret = sensor_attr_set(dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr);
    if (ret != 0)
    {
        printk("Cannot set sampling frequency for accelerometer.\n");
        return ret;
    }

    ret = sensor_attr_set(dev, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr);
    if (ret != 0)
    {
        printk("Cannot set sampling frequency for gyro.\n");
        return ret;
    }

    return 0;
}

extern "C"
{
    extern void bt_ready(int err);
}

int main(void)
{
    const struct device* dev_shell;

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    dev_shell = DEVICE_DT_GET(DT_CHOSEN(zephyr_shell_uart));

    if (!device_is_ready(dev_shell))
    {
        printk("%s: device not ready.\n", dev_shell->name);
        return 0;
    }

    dev_sensor = DEVICE_DT_GET(DT_NODELABEL(lsm6ds3tr_c));

    if (!device_is_ready(dev_sensor))
    {
        printk("Device lsm6ds3 is not ready\n");
        return -1;
    }

    if (set_sampling_freq(dev_sensor) != 0)
    {
        printk("Device lsm6ds3 failed to set sampling frequency\n");
        return;
    }

    k_timer_start(&log_timer, K_MSEC(1000), K_MSEC(1000));

    uint32_t dtr = 0;

    int err = bt_enable(bt_ready);
    if (err)
    {
        printk("Bluetooth init failed (err %d)\n", err);
    }

    while (!dtr)
    {
        uart_line_ctrl_get(dev_shell, UART_LINE_CTRL_DTR, &dtr);
        k_sleep(K_MSEC(100));
    }

    return 0;
}
