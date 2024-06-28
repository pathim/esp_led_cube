/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "renderer/moving_dots.h"
#include "renderer/chars.h"
#include "led_cube.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static LedCube configure_led(void)
{
    led_strip_handle_t led_strip;
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 64*5, // at least one LED on board
    };
#if CONFIG_BLINK_LED_STRIP_BACKEND_RMT
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags={.with_dma = false},
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
#elif CONFIG_BLINK_LED_STRIP_BACKEND_SPI
    led_strip_spi_config_t spi_config = {
        .spi_bus = SPI2_HOST,
        .flags.with_dma = true,
    };
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
#else
#error "unsupported LED strip backend"
#endif
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
    return LedCube{led_strip, 8};
}

#define DOT_COUNT 0

extern "C"{
void app_main(void)
{
    /* Configure the peripheral according to the LED type */
    LedCube led_cube{configure_led()};


    DotManager dot_manager{led_cube};

    char num=0;
    int pos=0;
    for(int i=0;i<DotManager::MAX_DOTS;i++){
       dot_manager.add_dot();
    }
    
    TickType_t last_tick=xTaskGetTickCount();
    while (1) {
        //ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");

        // for (int x=0;x<32;x+=2){
        //     led_strip_set_pixel(led_strip, transform_side(x,pos%8), 0, 0, 0);
        // }
        // pos++;
        // for (int x=0;x<32;x+=2){
        //     led_strip_set_pixel(led_strip, transform_side(x,pos%8), 100, 0, 0);
        //     led_strip_set_pixel(led_strip, transform_side(x+1,(pos+4)%8), 0, 100, 0);
        // }

        for(int32_t y=3;y>-13;y--){
           // led_cube.set_pixel(Pos{8+16,y}, 0, 100, 0);
           // led_cube.set_pixel(Pos{12+16,y}, 100, 0, 0);
        }

        char word[]="Hallo";
        // show_char(' '+num,0x100000,0x000010,0*64);
        for(int i=0;i<5;i++){
             //show_char(led_cube,'0'+i,0x100000,0x000010,i);
        //     show_char(word[(pos+i)%sizeof(word)],0x100000,0x000010,i*64);
         }
         //show_char(led_cube,'2',0x100000,0x000010,1);
         //show_char(led_cube,'3',0x100000,0x000010,2);
         //show_char(led_cube,'4',0x100000,0x000010,4);
        TickType_t current_tick=xTaskGetTickCount();
        dot_manager.update(current_tick-last_tick);
        last_tick=current_tick;
        led_cube.refresh();
        
        //vTaskDelay(100 / portTICK_PERIOD_MS);
        
    }
}
}