/*
 * @Descripttion :
 * @version      :
 * @Author       : Kevincoooool
 * @Date         : 2021-09-04 16:11:59
 * @LastEditors: Marktlen
 * @LastEditTime: 2022-03-29 10:07:21
 * @FilePath: \lvgl_v8_esp32\main\main.c
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "lvgl_helpers.h"
#include "esp_freertos_hooks.h"
#include "esp_heap_caps.h"
#include "trangram_create.h"
#include "Hardware/my_adc.h"
bool en = 1;


static void lv_tick_task(void *arg)
{
   (void)arg;
   lv_tick_inc(portTICK_PERIOD_MS);
}
SemaphoreHandle_t xGuiSemaphore;
u_int8_t key;
static void gui_task(void *arg)
{
   xGuiSemaphore = xSemaphoreCreateMutex();
   lv_init();          // lvgl内核初始化
   lvgl_driver_init(); // lvgl显示接口初始化

   /*--------- lv_port_display ------------ */
   static lv_disp_draw_buf_t draw_buf;
   lv_color_t *buf1 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);
   lv_color_t *buf2 = heap_caps_malloc(DLV_HOR_RES_MAX * DLV_VER_RES_MAX * sizeof(lv_color_t), MALLOC_CAP_DMA);

   lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DLV_HOR_RES_MAX * DLV_VER_RES_MAX); /*Initialize the display buffer*/

   static lv_disp_drv_t disp_drv;         /*A variable to hold the drivers. Must be static or global.*/
   lv_disp_drv_init(&disp_drv);           /*Basic initialization*/
   disp_drv.draw_buf = &draw_buf;         /*Set an initialized buffer*/
   disp_drv.flush_cb = disp_driver_flush; /*Set a flush callback to draw to the display*/
   disp_drv.hor_res = 320;                /*Set the horizontal resolution in pixels*/
   disp_drv.ver_res = 240;                /*Set the vertical resolution in pixels*/
   lv_disp_drv_register(&disp_drv);       /*Register the driver and save the created display objects*/

   esp_register_freertos_tick_hook(lv_tick_task);
   adc_Init(WIDTH, CHANNEL, ATTEN);
   trangram_create();

   while (1)
   {
      int adc_val = adc_read(CHANNEL);
      // printf("%d\n", adc_val);
      if (adc_val <= 1317 && adc_val >= 1000 && lv_anim_count_running() == 0)
      {
         show_rand_tip(adc_read(CHANNEL));
      }
      else if (adc_val <= 2060 && adc_val >= 1640 && lv_anim_count_running() == 0)
      {
         show_whole_trangram();
      }
      else if(adc_val <= 2875 && adc_val >= 2850 && lv_anim_count_running() == 0)
      {
         show_recover_trangram();
      }

      vTaskDelay(pdMS_TO_TICKS(10));
      /* Try to take the semaphore, call lvgl related function on success */
      if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
      {
         lv_timer_handler();
         xSemaphoreGive(xGuiSemaphore);
      }
   }
}

void mytimerCallback(TimerHandle_t xTimer)
{
   if (opa_val <= 255)
   {
      opa_val++;
   }
   // printf("%d\n", opa_val);
}
void app_main(void)
{
   TimerHandle_t myTimer1;
   myTimer1 = xTimerCreate("myTimer1", pdMS_TO_TICKS(100), pdTRUE, 0, mytimerCallback);

   xTaskCreatePinnedToCore(gui_task, "gui task", 1024 * 4, NULL, 1, NULL, 0);
   xTimerStart(myTimer1, 10);
}
