#include "accelerometer.h"

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

const struct device* dev_sensor;

static inline float out_ev(struct sensor_value* val)
{
    return (val->val1 + (float)val->val2 / 1000000);
}

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

void init_accelerometer()
{
    dev_sensor = DEVICE_DT_GET(DT_NODELABEL(lsm6ds3tr_c));

    if (!device_is_ready(dev_sensor))
    {
        printk("Device lsm6ds3 is not ready\n");
        return;
    }

    if (set_sampling_freq(dev_sensor) != 0)
    {
        printk("Device lsm6ds3 failed to set sampling frequency\n");
        return;
    }
}

void get_accelerometer_data(accelerometer_data& data)
{
    struct sensor_value x, y, z;

    /* lsm6dso accel */
    sensor_sample_fetch_chan(dev_sensor, SENSOR_CHAN_ACCEL_XYZ);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_ACCEL_X, &x);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_ACCEL_Y, &y);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_ACCEL_Z, &z);

    data.x_accel = out_ev(&x);
    data.y_accel = out_ev(&y);
    data.z_accel = out_ev(&z);

    /* lsm6dso gyro */
    sensor_sample_fetch_chan(dev_sensor, SENSOR_CHAN_GYRO_XYZ);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_GYRO_X, &x);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_GYRO_Y, &y);
    sensor_channel_get(dev_sensor, SENSOR_CHAN_GYRO_Z, &z);

    data.x_gyro = out_ev(&x);
    data.y_gyro = out_ev(&y);
    data.z_gyro = out_ev(&z);
}

void print_accelerometer_data(const accelerometer_data& data)
{
    printk("accel x:%f ms/2 y:%f ms/2 z:%f ms/2\n", data.x_accel, data.y_accel, data.z_accel);
    printk("gyro x:%f rad/s y:%f rad/s z:%f rad/s\n", data.x_gyro, data.y_gyro, data.z_gyro);
}
