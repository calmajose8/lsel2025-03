#include "snake_time.h"
#include "stm32_init.h"
#include "stm32f4xx_hal.h"

int snake_time_init (snake_game_t* p_game){
    int a=stm32_init();
    return a; // Llama a la función de inicialización STM32
}
void snake_time_close (snake_game_t* p_game){

}
void snake_time_delay_ms (uint32_t ms){
    HAL_Delay(ms);
}

