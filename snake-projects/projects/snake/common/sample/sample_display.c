#include "stm32_bsp.h"
#include "ssd1306.h"
#include "snake_display.h"
#include "snake_time.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef SAMPLE_DISPLAY_DURATION
#define SAMPLE_DISPLAY_DURATION 5000
#endif

// Función para mostrar un ejemplo de juego en la pantalla
void sample_display_1()
{
    snake_game_t game;
    struct segment_t *new_tail;
    struct segment_t *last_tail;

    // Inicializar temporizador y pantalla
    snake_time_init(&game);
    snake_display_init(&game);

    // Configurar la cabeza de la serpiente
    game.snake.head.x = 0;
    game.snake.head.y = 0;
    game.snake.head.next = NULL;
    game.snake.tail = &(game.snake.head);

    // Crear la cola de la serpiente en la dirección horizontal
    for (int i = 1; i < game.limits.x / 2; i++) {
        new_tail = malloc(sizeof(struct segment_t));
        if (new_tail == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for new_tail.\n");
            exit(EXIT_FAILURE);
        }
        new_tail->x = game.snake.tail->x + 1;
        new_tail->y = game.snake.tail->y;
        new_tail->next = game.snake.tail;
        game.snake.tail = new_tail;
    }

    // Crear la cola de la serpiente en la dirección vertical
    for (int i = 1; i < game.limits.y / 2; i++) {
        new_tail = malloc(sizeof(struct segment_t));
        if (new_tail == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for new_tail.\n");
            exit(EXIT_FAILURE);
        }
        new_tail->x = game.snake.tail->x;
        new_tail->y = game.snake.tail->y + 1;
        new_tail->next = game.snake.tail;
        game.snake.tail = new_tail;
    }

    // Configurar la posición de la manzana
    game.apple.x = game.limits.x - 1;
    game.apple.y = game.limits.y - 1;

    // Renderizar el estado inicial del juego
    snake_display_render(&game);

    // Esperar durante un tiempo definido
    snake_time_delay_ms(SAMPLE_DISPLAY_DURATION);

    // Liberar la memoria asignada para la cola de la serpiente
    for (last_tail = game.snake.tail; ((last_tail != NULL) && (last_tail != &(game.snake.head)));) {
        new_tail = last_tail->next;
        free(last_tail);
        last_tail = new_tail;
    }

    // Cerrar la pantalla y el temporizador
    snake_display_close(&game);
    snake_time_close(&game);
}

// Función principal
int main()
{
    sample_display_1();
    return 0;
}