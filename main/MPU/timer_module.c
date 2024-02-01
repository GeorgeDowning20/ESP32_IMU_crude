// timer_module.c

#include "timer_module.h"
#include "freertos/FreeRTOS.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "MPU/timer_module.h" // Include the header for the timer module
#include "MPU/MPU6500.h"
#include "MPU/i2c.h"
#include "MPU/registers.h"
#include "MPU/i2c_config.h"

static const char *TAG = "timer_module";

volatile uint64_t counter = 0;  // Global counter variable

static bool IRAM_ATTR timer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data) {
   
    readMPU();
    counter++;  // Increment the counter on each timer interrupt
    return true;  // Return true to auto-reload timer
}

void timer_setup(void) {
    ESP_LOGI(TAG, "Setting up timer");
    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1 MHz (1 tick = 1 µs)
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_callback,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    ESP_ERROR_CHECK(gptimer_enable(gptimer));

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = 1000000, // 10,000 µs = 10 ms for 100 Hz
        .flags.auto_reload_on_alarm = true,
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    ESP_ERROR_CHECK(gptimer_start(gptimer));
}
