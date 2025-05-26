#include "snake_input.h"
#include "stm32_bsp.h"
#include "stm32f4xx_hal.h"
#include "stm32_init.h"
#include <stdlib.h>



int snake_input_init(snake_game_t* p_game){
    int result;

    // Inicializa STM32
    result = stm32_init();
    if (result != 0) {
        return -1; // Error en la inicialización
    }

    // Obtiene el driver del acelerómetro
    ACCELERO_DrvTypeDef* acc;
    acc = bsp_get_accelero();
    if (acc == 0) {
        return -1; // Error al obtener el driver
    }

    // Obtiene la configuración del acelerómetro
    uint16_t acc_config;
    acc_config = bsp_get_accelero_config();

    // Inicializa el acelerómetro con la configuración obtenida
    if (acc->Init != 0) {
        acc->Init(acc_config);
    }

    return 0; // Inicialización exitosa
}
void snake_input_update_new_heading (snake_game_t* p_game){
    // Obtiene el driver del acelerómetro
    ACCELERO_DrvTypeDef* acc = bsp_get_accelero();
    if (acc == 0 || acc->GetXYZ == 0) {
        return; // Error al obtener el driver o la función GetXYZ
    }

    // Lee los datos del acelerómetro
    int16_t xyz[3] = {0};
    acc->GetXYZ(xyz);

    // Determina el eje con el valor absoluto más alto
    int16_t abs_x = abs(xyz[0]);
    int16_t abs_y = abs(xyz[1]);
    int16_t abs_z = abs(xyz[2]);

    // Asigna el nuevo valor de dirección basado en el eje dominante
    if (abs_x > abs_y && abs_x > abs_z) {
        // Eje X domina
        if (xyz[0] > 0) {
            p_game->new_heading = UP; // Según la colocación del LCD
        } else {
            p_game->new_heading = DOWN;
        }
    } else if (abs_y > abs_x && abs_y > abs_z) {
        // Eje Y domina
        if (xyz[1] > 0) {
            p_game->new_heading = LEFT; // Según la colocación del LCD
        } else {
            p_game->new_heading = RIGHT;
        }
    } else {
        // Eje Z domina
        p_game->new_heading = NONE;
    }
}
void snake_input_close(snake_game_t* p_game){

}




