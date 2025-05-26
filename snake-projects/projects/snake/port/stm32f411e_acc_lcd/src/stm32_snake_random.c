#include "snake_random.h"
#include "stm32_init.h"
#include <stdlib.h>


int snake_random_init(snake_game_t* p_game){
    return stm32_init();
}
int snake_random_get(int limit){
    if (limit <= 0) {
        return 0; // Si el límite es menor o igual a 0, devuelve 0
    }
    return rand() % limit; // Genera un número aleatorio entre 0 y limit - 1
}
void snake_random_close(snake_game_t* p_game){
    
}