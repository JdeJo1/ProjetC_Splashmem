#ifndef __WORLD__
#define __WORLD__

#include "param.h"
#include "player.h"

extern uint8_t   mapmem[];
extern t_player* players[];
extern bombe bombs[MAX_BOMBS];

void world_paint_spot(uint32_t x, uint32_t y, uint32_t num);
void world_do_player_action(t_player* p_player);
void world_set_players();
void world_create_players();
void world_get_winner();
void world_update_bombe();
int world_gameover();
void world_detruirefenetre();

#endif