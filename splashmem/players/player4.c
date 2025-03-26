#include "actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION 4

char play_actions[] = {
    ACTION_TELEPORT_L, ACTION_TELEPORT_U, ACTION_SPLASH, ACTION_TELEPORT_L,
};

char get_action()
{
    static int i       = 0;
    char       ret_val = 0;

    ret_val = play_actions[i];
    i++;
    if (i >= MAX_PLAY_ACTION)
    {
        i = 0;
    }
    return (ret_val);
}