#include "FreeRTOS.h"
#include "task.h"

extern "C"
{
    void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer,
                                       StackType_t** ppxIdleTaskStackBuffer,
                                       uint32_t* pulIdleTaskStackSize)
    {
        static StaticTask_t xIdleTaskTCB;
        static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

        *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
        *ppxIdleTaskStackBuffer = uxIdleTaskStack;

        *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    }

    void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer,
                                        StackType_t** ppxTimerTaskStackBuffer,
                                        uint32_t* pulTimerTaskStackSize)
    {
        static StaticTask_t xTimerTaskTCB;
        static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

        *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
        *ppxTimerTaskStackBuffer = uxTimerTaskStack;

        *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
    }

    void configure_timer_for_runtime_stats()
    {
    }

    unsigned long get_runtime_counter_value()
    {
        return 0;
    }

    void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName)
    {
        /* Check pcTaskName for the name of the offending task,
         * or pxCurrentTCB if pcTaskName has itself been corrupted. */
        (void)xTask;
        (void)pcTaskName;
    }

    void vApplicationTickHook(void)
    {
    }
}
