#include "trangram_create.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define COVER_COLOR lv_palette_main(LV_PALETTE_BROWN)

LV_FONT_DECLARE(big_triangle);
LV_FONT_DECLARE(big_triangle2);
LV_FONT_DECLARE(mid_triangle);
LV_FONT_DECLARE(small_triangle);
LV_FONT_DECLARE(small_triangle2);
LV_FONT_DECLARE(square);
LV_FONT_DECLARE(parallelogram);
LV_FONT_DECLARE(parallelogram2);
bool ALL_CONTROL = 1;
lv_obj_t *big_triangle_img;
lv_obj_t *big_triangle2_img;
lv_obj_t *mid_triangle_img;
lv_obj_t *small_triangle_img;
lv_obj_t *square_img;
lv_obj_t *small_triangle2_img;
lv_obj_t *parallelogram_img;
lv_opa_t OPA = LV_OPA_COVER;
static lv_style_t style;
int opa_val = 0;

/**
 * @brief  显示整个七巧板
 * @param  None
 * @retval None
 *
 */
void show_whole_trangram()
{
    opa_change_anim(big_triangle_img, 1, 255, 0, 0);
    opa_change_anim(big_triangle2_img, 1, 255, 0, 0);
    opa_change_anim(mid_triangle_img, 1, 255, 0, 0);
    opa_change_anim(small_triangle_img, 1, 255, 0, 0);
    opa_change_anim(square_img, 1, 255, 0, 0);
    opa_change_anim(small_triangle2_img, 1, 255, 0, 0);
    opa_change_anim(parallelogram_img, 1, 255, 0, 0);
}
void show_recover_trangram()
{
    opa_change_anim(big_triangle_img, 1, 0, 255, 0);
    opa_change_anim(big_triangle2_img, 1, 0, 255, 0);
    opa_change_anim(mid_triangle_img, 1, 0, 255, 0);
    opa_change_anim(small_triangle_img, 1, 0, 255, 0);
    opa_change_anim(square_img, 1, 0, 255, 0);
    opa_change_anim(small_triangle2_img, 1, 0, 255, 0);
    opa_change_anim(parallelogram_img, 1, 0, 255, 0);
}

/**
 * @brief  产生随机提示
 * @param  send_num：随机数种子
 * @retval None
 *
 */
void show_rand_tip(uint16_t send_num)
{
    srand(send_num);
    // opa_change_anim(small_triangle_img, 4);
    int rand_num = rand() % 8; // 0~7随机数
    // printf("rand_num:%d\n", rand_num);
    switch (rand_num)
    {
    case 0:
        opa_change_anim(big_triangle_img, 4, 255, 0, 1);
        break;
    case 1:
        opa_change_anim(big_triangle2_img, 4, 255, 0, 1);
        break;
    case 2:
        opa_change_anim(mid_triangle_img, 4, 255, 0, 1);
        break;
    case 3:
        opa_change_anim(small_triangle_img, 4, 255, 0, 1);
        break;
    case 4:
        opa_change_anim(square_img, 4, 255, 0, 1);
        break;
    case 5:
        opa_change_anim(small_triangle2_img, 4, 255, 0, 1);
        break;
    case 6:
        opa_change_anim(parallelogram_img, 4, 255, 0, 1);
        break;
    default:
        printf("error\n");
        break;
    }
}

/**
 * @brief  opa_change_anim的callback函数
 */
static void opa_change_cb(void *var, int32_t v)
{
    lv_obj_set_style_img_recolor_opa(var, v, 0);
}
/**
 * @brief  定义渐变动画
 * @param  obj:需要添加动画的对象
 * @param  re_cnt:动画重复次数
 * @param  start_val:动画开始值
 * @param  end_val:动画结束值
 * @param  en_playback:是否需要倒放
 * @retval None
 *
 */
void opa_change_anim(lv_obj_t *obj, uint16_t re_cnt, int32_t start_val, int32_t end_val, bool en_playback)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, start_val, end_val);

    if (en_playback)
    {
        lv_anim_set_time(&a, 300);           //正放时间
        lv_anim_set_playback_delay(&a, 500); //倒放等待时间
        lv_anim_set_playback_time(&a, 300);  //倒放时间
        lv_anim_set_repeat_delay(&a, 500);   //再放一遍的时间
    }
    else
    {
        lv_anim_set_time(&a, 1000); //正放时间
    }
    lv_anim_set_repeat_count(&a, re_cnt); //动画重复次数LV_ANIM_REPEAT_INFINITE
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    lv_anim_set_exec_cb(&a, opa_change_cb);
    lv_anim_start(&a);
}

/**
 * @brief  七巧板创建
 * @param  None
 * @retval None
 *
 */
void trangram_create(void)
{
    jigsaw puzzles[][7] = {
        {{BIG_TRIANGLE, 132, 144, 0}, {BIG_TRIANGLE_2, 132 + 16, 144 - 40, 3150}, {MID_TRIANGLE, 132 - 28, 144 + 12, 450}, {SMALL_TRIANGLE, 132 - 59, 144 - 9, 2250}, {SMALL_TRIANGLE_2, 132 - 51, 144 - 97, 2700}, {SQUARE, 132 - 31, 144 - 36, 450}, {PARALLELOGRAM, 132 - 39, 144 - 70, 900}},
        {{BIG_TRIANGLE, 0, 0, 45}, {BIG_TRIANGLE_2, 0, 0, 45}, {MID_TRIANGLE, 0, 0, 45}, {SMALL_TRIANGLE, 0, 0, 45}, {SMALL_TRIANGLE_2, 0, 0, 45}, {SQUARE, 0, 0, 45}, {PARALLELOGRAM, 0, 0, 45}}};

    /*------------set_style-----------*/
    lv_style_init(&style);
    lv_style_set_bg_opa(&style, LV_OPA_TRANSP);
    lv_style_set_img_recolor(&style, COVER_COLOR);
    lv_style_set_img_recolor_opa(&style, OPA);

    /*-------------set_img-----------*/
    if (puzzles[0][0].shape == BIG_TRIANGLE)
    {
        big_triangle_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(big_triangle_img, &style, 0);
        lv_img_set_src(big_triangle_img, &big_triangle);
        // lv_obj_align(big_triangle_img, LV_ALIGN_TOP_LEFT, 132, 144);
        // lv_img_set_angle(big_triangle_img, 0);
        lv_obj_align(big_triangle_img, LV_ALIGN_TOP_LEFT, puzzles[0][0].lefttop_x, puzzles[0][0].lefttop_y);
        lv_img_set_angle(big_triangle_img, puzzles[0][0].orientation);
    }
    if (puzzles[0][1].shape == BIG_TRIANGLE_2)
    {
        big_triangle2_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(big_triangle2_img, &style, 0);
        lv_img_set_src(big_triangle2_img, &big_triangle2);
        // lv_obj_align(big_triangle2_img, LV_ALIGN_TOP_LEFT, 132 + 16, 144 - 40);
        // lv_img_set_angle(big_triangle2_img, 3150);
        lv_obj_align(big_triangle2_img, LV_ALIGN_TOP_LEFT, puzzles[0][1].lefttop_x, puzzles[0][1].lefttop_y);
        lv_img_set_angle(big_triangle2_img, puzzles[0][1].orientation);
    }
    if (puzzles[0][2].shape == MID_TRIANGLE)
    {
        mid_triangle_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(mid_triangle_img, &style, 0);
        lv_img_set_src(mid_triangle_img, &mid_triangle);
        // lv_obj_align(mid_triangle_img, LV_ALIGN_TOP_LEFT, 132 - 28, 144 + 12);
        // lv_img_set_angle(mid_triangle_img, 450);
        lv_obj_align(mid_triangle_img, LV_ALIGN_TOP_LEFT, puzzles[0][2].lefttop_x, puzzles[0][2].lefttop_y);
        lv_img_set_angle(mid_triangle_img, puzzles[0][2].orientation);
    }
    if (puzzles[0][3].shape == SMALL_TRIANGLE)
    {
        small_triangle_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(small_triangle_img, &style, 0);
        lv_img_set_src(small_triangle_img, &small_triangle);
        // lv_obj_align(small_triangle_img, LV_ALIGN_TOP_LEFT, 132 - 59, 144 - 9);
        // lv_img_set_angle(small_triangle_img, 2250);
        lv_obj_align(small_triangle_img, LV_ALIGN_TOP_LEFT, puzzles[0][3].lefttop_x, puzzles[0][3].lefttop_y);
        lv_img_set_angle(small_triangle_img, puzzles[0][3].orientation);
    }
    if (puzzles[0][4].shape == SMALL_TRIANGLE_2)
    {
        small_triangle2_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(small_triangle2_img, &style, 0);
        lv_img_set_src(small_triangle2_img, &small_triangle2);
        // lv_img_set_angle(small_triangle2_img, 2700);
        // lv_obj_align(small_triangle2_img, LV_ALIGN_TOP_LEFT, 132 - 51, 144 - 97);
        lv_obj_align(small_triangle2_img, LV_ALIGN_TOP_LEFT, puzzles[0][4].lefttop_x, puzzles[0][4].lefttop_y);
        lv_img_set_angle(small_triangle2_img, puzzles[0][4].orientation);
    }
    if (puzzles[0][5].shape == SQUARE)
    {
        square_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(square_img, &style, 0);
        lv_img_set_src(square_img, &square);
        // lv_img_set_angle(square_img, 450);
        // lv_obj_align(square_img, LV_ALIGN_TOP_LEFT, 132 - 31, 144 - 36);
        lv_obj_align(square_img, LV_ALIGN_TOP_LEFT, puzzles[0][5].lefttop_x, puzzles[0][5].lefttop_y);
        lv_img_set_angle(square_img, puzzles[0][5].orientation);
    }
    if (puzzles[0][6].shape == PARALLELOGRAM)
    {
        parallelogram_img = lv_img_create(lv_scr_act());
        lv_obj_add_style(parallelogram_img, &style, 0);
        lv_img_set_src(parallelogram_img, &parallelogram);
        // lv_obj_align(parallelogram_img, LV_ALIGN_TOP_LEFT, 132 - 39, 144 - 70);
        // lv_img_set_angle(parallelogram_img, 900);
        lv_obj_align(parallelogram_img, LV_ALIGN_TOP_LEFT, puzzles[0][6].lefttop_x, puzzles[0][6].lefttop_y);
        lv_img_set_angle(parallelogram_img, puzzles[0][6].orientation);
    }
}

