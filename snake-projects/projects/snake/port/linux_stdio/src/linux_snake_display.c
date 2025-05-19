 ..#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 16
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

static void
clear_screen()
{
  printf("\e[1;1H\e[2J");
  fsync(1);
}

static void
print_hlimit(snake_game_t* p_game)
{
  printf("+");
  for (int i = 0; i < p_game->limits.y; i++) {
    printf("_");
  }
  printf("+\n");
}

static void
print_row(snake_game_t* p_game, int x)
{
  printf("|");
  for (int y = 0; y < p_game->limits.y; y++) {
    printf("%c", fb->pixel[x][y]);
  }
  printf("|\n");
}

void 
snake_display_render(snake_game_t* p_game)
{
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

  clear_screen();

  // Print the top boundary
  print_hlimit(p_game);

  // Print each row
  for (int x = 0; x < p_game->limits.x; x++) {
    print_row(p_game, x);
  }

  // Print the bottom boundary
  print_hlimit(p_game);

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