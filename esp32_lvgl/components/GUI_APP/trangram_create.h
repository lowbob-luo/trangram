#ifndef TRANGRAM_CREATE_H
#define TRANGRAM_CREATE_H
#include "lvgl.h"

typedef enum
{
    BIG_TRIANGLE = 0x01,
    BIG_TRIANGLE_2 = 0x02,
    MID_TRIANGLE = 0x03,
    SMALL_TRIANGLE = 0x04,
    SMALL_TRIANGLE_2 = 0x05,
    SQUARE = 0x06,
    PARALLELOGRAM = 0x07,
} element_shape;

typedef struct
{
    element_shape shape;
    uint16_t lefttop_x;
    uint16_t lefttop_y;
    uint16_t orientation;
}jigsaw;


extern int opa_val;
extern bool ALL_CONTROL;
extern lv_obj_t *big_triangle_img;
extern lv_obj_t *big_triangle2_img;
extern lv_obj_t *mid_triangle_img;
extern lv_obj_t *small_triangle_img;
extern lv_obj_t *square_img;
extern lv_obj_t *small_triangle2_img;
extern lv_obj_t *parallelogram_img;

void lv_example_anim_2(void);
void trangram_create(void);
void opa_change_anim(lv_obj_t *obj, uint16_t re_cnt, int32_t start_val, int32_t end_val,bool en_playback);
void show_rand_tip(uint16_t send_num);
void show_whole_trangram();
void show_recover_trangram();

#endif
