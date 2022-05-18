
/**
 * @file lv_port_indev.h
 *
 */

 /*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 0

#ifndef LV_PORT_INDEV_H
#define LV_PORT_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define Touchpad    0
#define Mouse       0
#define Keypad      1
#define Encoder     0
#define Button      0

extern lv_group_t * group;
extern lv_indev_t *indev_keypad;
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/
void My_lv_port_indev_init(void);
void keypad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
