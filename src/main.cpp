#include "FreeRTOS.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "task.h"

StaticTask_t s_main_task_buffer;
static constexpr StackType_t kMainStackSize = 2048 / sizeof(StackType_t);
StackType_t s_main_stack_buffer[kMainStackSize];

void main_thread(void* params)
{
    while (1)
    {
        nrf_gpio_pin_toggle(0);

        nrf_delay_ms(500);
    }
}

int main()
{
    TaskHandle_t main_task_handle = NULL;
    main_task_handle = xTaskCreateStatic(main_thread, "Main", kMainStackSize, (void*)1, tskIDLE_PRIORITY,
                                         s_main_stack_buffer, &s_main_task_buffer);

    vTaskStartScheduler();

    return 0;
}
