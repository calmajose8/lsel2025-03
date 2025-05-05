#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 16
#define MAX_Y 16

#define CHAR_APPLE '*'
#define CHAR_HEAD '@'
#define CHAR_BODY 'o'
#define CHAR_EMPTY ' '

struct fb_t {
  char pixel[MAX_X][MAX_Y];
};
static struct fb_t fb_s;
static struct fb_t* fb = &fb_s;

static void
clear_screen()
{
  printf("\e[1;1H\e[2J");
  fsync(1);
}

static void
print_hlimit(snake_game_t* p_game)
{
  // TODO: imprime + , - por cada columna , +
}


static void
print_row(snake_game_t* p_game, int x)
{
  // TODO: imprime | , el char que indique el buffer por cada columna , |
}

void 
snake_display_render(snake_game_t* p_game)
{
  /* Change: Each element is a char */
  /* - Apple is CHAR_APPLE */
  /* - Snake head is CHAR_HEAD */
  /* - Snake body CHAR_BODY */
  /* - Empty pixels are CHAR_EMPTY */
  struct segment_t *seg_i;

  /* Set Blank */
  memset(fb, CHAR_EMPTY, sizeof(struct fb_t));

  //TODO: cambia el valor del elemento del array fb->pixel para la manzana
  //TODO: cambia el valor del elemento del array fb->pixel para toda la serpiente, empezando por la cola
  //TODO: cambia el valor del elemento del array fb->pixel para la cabeza de la serpiente

  clear_screen();

  //TODO: imprime limite
  //TODO: imprime cada fila con limite antes y despues
  //TODO: imprime limite


  fflush(NULL);
}

int
snake_display_init(snake_game_t* p_game)
{
  /* Guarda limites en el juego */
  p_game->limits = (struct apple_t){ .x = MAX_X, .y = MAX_Y };

  return 1;
}

void
snake_display_close(__attribute__((unused)) snake_game_t* p_game)
{
  /* No hace nada */
}
