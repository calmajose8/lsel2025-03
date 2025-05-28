#include "snake_display.h"
#include "stm32f4xx.h"
#include "stm32_bsp.h"
#include "stm32_init.h"
#include "stm32f4xx_hal.h"
#include "lsm303dlhc.h"
#include "ssd1306.h"
#include <string.h>


#define MAX_X 8
#define MAX_Y 16

#define CHAR_APPLE 'o'
#define CHAR_HEAD '%'
#define CHAR_BODY '~'
#define CHAR_EMPTY ' '

struct fb_t {
  char pixel[MAX_X][MAX_Y];
};
static struct fb_t fb_s;
static struct fb_t* fb = &fb_s;





void snake_display_render(snake_game_t* p_game) {
    struct segment_t *seg_i;

    /* Set Blank */
    memset(fb, CHAR_EMPTY, sizeof(struct fb_t));

    // Set the apple
    fb->pixel[p_game->apple.x][p_game->apple.y] = CHAR_APPLE;

    // Set the snake body
    for (seg_i = p_game->snake.tail; seg_i->next; seg_i = seg_i->next) {
    fb->pixel[seg_i->x][seg_i->y] = CHAR_BODY;
    }

    // Set the snake head
    fb->pixel[p_game->snake.head.x][p_game->snake.head.y] = CHAR_HEAD;

    lcd_reset();

    for (int x = 0; x < p_game->limits.x; x++) {
        lcd_set_cursor(0, x*8);
        for (int y = 0; y < p_game->limits.y; y++) {
        
            lcd_write_char(fb->pixel[x][y]);
        }
    }
    lcd_update_screen();
}


int snake_display_init(snake_game_t* p_game) {
    // Inicializa STM32
    if (stm32_init() != 1) {
        return -1; // Error en la inicialización de STM32
    }

    // Inicializa el LCD
    if (lcd_init() != 1) {
        return -1; // Error en la inicialización del LCD
    }

    //limites

    p_game->limits.x = MAX_X; //puede estar cambiado x por y
    p_game->limits.y = MAX_Y;

    return 0; // Inicialización exitosa
}
void snake_display_close(snake_game_t* p_game){
    lcd_reset(); // Resetea la pantalla al estado inicial
}