#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart1;
TIM_HandleTypeDef htim2;

#define SAMPLE_COUNT      20
#define TRIM_COUNT        3
#define EDGE_TIMEOUT_US   100000


void SystemClock_Config(void);
void GPIO_Init(void);
void UART1_Init(void);
void TIM2_Init(void);

uint32_t Measure_555_Period_US(void);
void sort_u32(uint32_t *arr, int n);
float Get_TrimmedMean_Period(void);
float Get_Baseline_Period(uint8_t times);
float Period_us_To_Cap_pF(float T_us);
void Error_Handler(void);


int main(void)
{
    HAL_Init();
    SystemClock_Config();

    GPIO_Init();
    UART1_Init();
    TIM2_Init();

    HAL_TIM_Base_Start(&htim2);

    char msg[160];
    HAL_Delay(500);

    float T_base = Get_Baseline_Period(20);

    sprintf(msg, "Baseline T = %.2f us\r\n", T_base);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);

    while (1)
    {
        float T_trim = Get_TrimmedMean_Period();
        float f = 0.0f;
        float C = 0.0f;               

        if (T_trim > 0.1f)
        {
            f = 1000000.0f / T_trim;
        }

        C = Period_us_To_Cap_pF(T_trim);       
        

        sprintf(msg,
                "f = %.2f Hz | C = %.2f pF\r\n",
               f, C);

        HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);

        HAL_Delay(1000);
    }
}


uint32_t Measure_555_Period_US(void)
{
    uint32_t start, now;

    __HAL_TIM_SET_COUNTER(&htim2, 0);

    
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
    {
        if (__HAL_TIM_GET_COUNTER(&htim2) > EDGE_TIMEOUT_US)
            return EDGE_TIMEOUT_US;
    }

    
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
    {
        if (__HAL_TIM_GET_COUNTER(&htim2) > EDGE_TIMEOUT_US)
            return EDGE_TIMEOUT_US;
    }

   
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    start = __HAL_TIM_GET_COUNTER(&htim2);

    
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
    {
        now = __HAL_TIM_GET_COUNTER(&htim2);
        if ((now - start) > EDGE_TIMEOUT_US)
            return EDGE_TIMEOUT_US;
    }

   
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
    {
        now = __HAL_TIM_GET_COUNTER(&htim2);
        if ((now - start) > EDGE_TIMEOUT_US)
            return EDGE_TIMEOUT_US;
    }

    now = __HAL_TIM_GET_COUNTER(&htim2);
    return (now - start);
}


void sort_u32(uint32_t *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[i])
            {
                uint32_t temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


float Get_TrimmedMean_Period(void)
{
    uint32_t samples[SAMPLE_COUNT];
    uint32_t sum = 0;
    int valid_count = 0;

    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        samples[i] = Measure_555_Period_US();
        HAL_Delay(2);
    }

    sort_u32(samples, SAMPLE_COUNT);

    for (int i = TRIM_COUNT; i < SAMPLE_COUNT - TRIM_COUNT; i++)
    {
        sum += samples[i];
        valid_count++;
    }

    if (valid_count == 0)
        return 0.0f;

    return (float)sum / (float)valid_count;
}


float Get_Baseline_Period(uint8_t times)
{
    float sum = 0.0f;

    for (uint8_t i = 0; i < times; i++)
    {
        sum += Get_TrimmedMean_Period();
        HAL_Delay(10);
    }

    return sum / (float)times;
}


float Period_us_To_Cap_pF(float T_us)
{
    
    const float RA = 1000000.0f;   
    const float RB = 1000000.0f;   

    float T_s = T_us / 1000000.0f;
    float C_F = T_s / (0.693f * (RA + 2.0f * RB));
    float C_pF = C_F * 1e12f;

    return C_pF;
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        Error_Handler();

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();
}


void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

   
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void UART1_Init(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
        Error_Handler();
}


void TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 72 - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 0xFFFFFFFF;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
        Error_Handler();
}


void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}