#include "stm32f4xx.h"
#include "stm32_bsp.h"

#include "lsm303dlhc.h"
#include "ssd1306.h"

I2C_HandleTypeDef hi2c1;
extern FontDef Font_8x8;

int stm32_i2c_init (void)
{
  //hi2c1.Instance = I2C1;
  //hi2c1.Init.ClockSpeed = 100000;
  //hi2c1.Init.DutyCycle = 0;
  //hi2c1.Init.OwnAddress1 = 0;
  //hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  //hi2c1.Init.DualAddressMode = 0;
  //hi2c1.Init.OwnAddress2 = 0;
  //hi2c1.Init.GeneralCallMode = 0;
  //hi2c1.Init.NoStretchMode = 0;
 
  return 0;
}

void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
  //GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
    //GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_9;
    //GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    //GPIO_InitStruct.Pull = GPIO_PULLUP;
    //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    //GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

 
  }
}

// Inicializa I2C (llama a stm32_i2c_init):
void COMPASSACCELERO_IO_Init (void)
{
}

// Inicializa interrupción de Acelerómetro (click, PE4 y PE5)
void COMPASSACCELERO_IO_ITConfig (void)
{
}

// Escribe en el acelerómetro byte a byte (configuración)
void COMPASSACCELERO_IO_Write (uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value)
{
}

// Lee del acelerómetro byte a byte (configuración)
uint8_t COMPASSACCELERO_IO_Read (uint16_t DeviceAddr, uint8_t RegisterAddr)
{
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
}

uint8_t ssd1306_WriteData(void *hi2c, uint8_t* data, uint16_t len)
{
}
