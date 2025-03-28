#ifndef __ACTIONS__
#define __ACTIONS__

#include "player.h"

enum action
{
    ACTION_STILL,
    ACTION_MOVE_L,
    ACTION_MOVE_R,
    ACTION_MOVE_U,
    ACTION_MOVE_D,
    ACTION_DASH_L,
    ACTION_DASH_R,
    ACTION_DASH_U,
    ACTION_DASH_D,
    ACTION_TELEPORT_L,
    ACTION_TELEPORT_R,
    ACTION_TELEPORT_U,
    ACTION_TELEPORT_D,
    ACTION_SPLASH,
    ACTION_BOMB,
    ACTION_NUMBER
};

typedef struct {
    int x, y;       // Position de la bombe
    int minuteurbombe;  // Nombre de tours avant explosion
    int bombeactive;     // 1 si la bombe est active, 0 sinon
    int IDbombe;
} bombe;

void actions_do(t_player *p_player, enum action act_id);
void actions_init();
#endif
