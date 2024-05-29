#include <stdio.h>
#include <zephyr/kernel.h>

#include "accelerometer.h"
#include "sd.h"

int main()
{
    init_sd_card();
    init_accelerometer();

    accelerometer_data data;
    while (1)
    {
        k_sleep(K_MSEC(1000));
        get_accelerometer_data(data);
        print_accelerometer_data(data);
    }
    return 0;
}
