#include "nrf_delay.h"
#include "nrf_gpio.h"

int main()
{
    while (1)
    {
        nrf_gpio_pin_toggle(0);

        nrf_delay_ms(500);
    }

    return 0;
}
