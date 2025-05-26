#include "stm32f4xx.h"
#include "stm32_bsp.h"
#include "stm32_init.h"
#include "stm32f4xx_hal.h"
#include "lsm303dlhc.h"
#include "ssd1306.h"

I2C_HandleTypeDef hi2c1;
extern FontDef Font_8x8;

static int SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    return 0;
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    return 0;
  }

  return 1;
}

int stm32_i2c_init (void)
{
  static int result = 0;

  if (!result) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = 0;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = 0;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = 0;
    hi2c1.Init.NoStretchMode = 0;

    if(HAL_Init() != HAL_OK) {
      result = 0;
    } else {
      result = SystemClock_Config();
    }
  }

  
 
  
  return result;
}

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}


void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (i2cHandle->Instance == I2C1)
    {
        // Habilitar el reloj para GPIOB e I2C1
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_I2C1_CLK_ENABLE();

        // Configurar los pines PB6 (SCL) y PB9 (SDA)
        GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD; // Modo alternativo Open-Drain
        GPIO_InitStruct.Pull = GPIO_PULLUP;    // Pull-up habilitado
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Alta velocidad
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1; // Función alternativa para I2C1
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{
    if (i2cHandle->Instance == I2C1)
    {
        // Deshabilitar el reloj para I2C1
        __HAL_RCC_I2C1_CLK_DISABLE();

        // Desinicializar los pines PB6 (SCL) y PB9 (SDA)
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_9);
    }
}

// Inicializa I2C (llama a stm32_i2c_init):
void COMPASSACCELERO_IO_Init (void)
{
  stm32_i2c_init();
}

// Inicializa interrupción de Acelerómetro (click, PE4 y PE5)
void COMPASSACCELERO_IO_ITConfig (void)
{
}

// Escribe en el acelerómetro byte a byte (configuración)
void COMPASSACCELERO_IO_Write (uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value)
{
  HAL_I2C_Mem_Write(&hi2c1, DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &Value, 1, HAL_MAX_DELAY);
}

// Lee del acelerómetro byte a byte (configuración)
uint8_t COMPASSACCELERO_IO_Read (uint16_t DeviceAddr, uint8_t RegisterAddr)
{
  uint8_t Value = 0;
  HAL_I2C_Mem_Read(&hi2c1, DeviceAddr, RegisterAddr, I2C_MEMADD_SIZE_8BIT, &Value, 1, HAL_MAX_DELAY);
  return Value;
}

ACCELERO_DrvTypeDef* bsp_get_accelero(void) {
  return &Lsm303dlhcDrv;
}

uint16_t bsp_get_accelero_config(void) {
  ACCELERO_InitTypeDef acc_init_config;
  uint16_t ctrl =	0x0000;;
  acc_init_config.Power_Mode = LSM303DLHC_NORMAL_MODE;
  acc_init_config.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
  acc_init_config.Axes_Enable = LSM303DLHC_AXES_ENABLE;
  acc_init_config.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
  acc_init_config.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
  acc_init_config.Endianness = LSM303DLHC_BLE_LSB;
  acc_init_config.High_Resolution = LSM303DLHC_HR_ENABLE;
  ctrl |= (acc_init_config.Power_Mode | \
           acc_init_config.AccOutput_DataRate | \
           acc_init_config.Axes_Enable);
  ctrl |= ((acc_init_config.BlockData_Update | acc_init_config.Endianness | \
            acc_init_config.AccFull_Scale | acc_init_config.High_Resolution) << 8);
  return ctrl;
}

int lcd_init(void)
{
  return 0;
}

void 
lcd_reset(void) 
{
}

void 
lcd_update_screen(void) 
{
}

void lcd_set_cursor(uint8_t x, uint8_t y)
{
}

void lcd_write_char(char ch)
{
}

void ssd1306_Delay(uint32_t ms) {
}

uint8_t ssd1306_WriteCommand(void *hi2c, uint8_t command)
{
  return 0;
}

uint8_t ssd1306_WriteData(void *hi2c, uint8_t* data, uint16_t len)
{
  return 0;
}
