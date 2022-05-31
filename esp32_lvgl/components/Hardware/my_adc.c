#include "my_adc.h"
/**
 * @brief  ADC初始化程序
 * @param
 * @retval
 */
void adc_Init(adc_bits_width_t width_bit, adc_channel_t channel, adc_atten_t atten)
{
    adc1_config_width(width_bit); //设置通道6和1.1V参考电压
    adc1_config_channel_atten(channel, atten);
}

/**
 * @brief   读取特定ADC通道的ADC值程序，并返回滤波后的值
 * @param   channel: 通道选择参数有以下值:
 *          @arg ADC_CHANNEL_0
 *          @arg ADC_CHANNEL_1
 *          @arg ADC_CHANNEL_2
 *          @arg ADC_CHANNEL_3
 *          @arg ADC_CHANNEL_4
 *          @arg ADC_CHANNEL_5
 *          @arg ADC_CHANNEL_6
 *          @arg ADC_CHANNEL_7
 *          @arg ADC_CHANNEL_8
 *          @arg ADC_CHANNEL_9
 *          @arg ADC_CHANNEL_MAX
 * @retval  中值平均滤波后的结果
 */

int adc_read(adc_channel_t channel)
{
    int read_raw = adc1_get_raw(channel); //采集ADC
    //float adc_val = (read_raw * 3.3) / 4095;
    // printf("%d\n%.2f\n",read_raw,adc_val);
    return read_raw;
    // return read_raw;
}

/**
 * @brief  ADC键盘扫描程序，根据不同按键的adc值来区分按键
 * @param  None
 * @retval 返回按键标号
 *
 */
uint8_t key_up = 1;
uint16_t adc_val=0;
uint8_t keypad_scan(void)
{
    adc_val=adc_read(CHANNEL);
    printf("%d\n",adc_val);
    //adc_val >>= 2;
    if (key_up)
    {
        //key_up = 0;
        if (adc_val >= 145 && adc_val < 412)
            return ENTER; // enter
        else if (adc_val >= 2143 && adc_val < 2450)
            return LEFT; // left
        else if (adc_val >= 1327 && adc_val < 1539)
            return RIGHT; // right
        else if (adc_val >= 1090 && adc_val < 1327)
            return FORWARD; // forward
        else if (adc_val >= 1649 && adc_val < 2143)
            return BACKWARD; // backward
        else if (adc_val >= 412 && adc_val < 634)
            return DELETE; // delete
        else if (adc_val >= 861 && adc_val < 1090)
            return ESC; // esc
        else if (adc_val >= 634 && adc_val < 861)
            return RUN; // run
    }
    if (adc_val < 145)
        key_up = 1;
    else
        key_up = 0;

    return 0;
}

/**
 * @brief  用于ADC信号的平均中值滤波程序
 * @param  in_data: 传入ADC原始数据
 * @retval sum: 经过滤波后的结果
 */
#define N 11
int data[N];
int middleFilter(int in_data)
{
    int sum = 0;
    int temp[N];
    int change;
    int i, j;
    //记录数据
    for (i = 0; i < N - 1; i++)
    {
        data[i] = data[i + 1];
    }
    data[N - 1] = in_data;
    //复制数据
    for (i = 0; i < N; i++)
        temp[i] = data[i];
    //冒泡法排序
    for (i = 1; i < N; i++)
        for (j = 0; j < N - i; j++)
        {
            if (temp[i] > temp[i + 1])
            {
                change = temp[i];
                temp[i] = temp[i + 1];
                temp[i + 1] = change;
            }
        }
    return temp[N - 5];
    //求和
    for (i = 1; i < N - 1; i++)
        sum = sum + (temp[i] / (N - 2));
    //返回平均值
    return sum;
}
