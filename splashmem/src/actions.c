#include "actions.h"
#include "world.h"

void actions_init()
{
    //je sais pas quoi init 
}

void actions_do(t_player *p_player, enum action act_id)
{
    switch (act_id)
    {
    case ACTION_MOVE_L:
        if (p_player->credits >= 1)
        {
            p_player->x = (p_player->x - 1 + 100) % 100;
            p_player->credits -= 1;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_MOVE_R:
        if (p_player->credits >= 1)
        {
            p_player->x = (p_player->x + 1) % 100;
            p_player->credits -= 1;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_MOVE_U:
        if (p_player->credits >= 1)
        {
            p_player->y = (p_player->y - 1 + 100) % 100;
            p_player->credits -= 1;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_MOVE_D:
        if (p_player->credits >= 1)
        {
            p_player->y = (p_player->y + 1) % 100;
            p_player->credits -= 1;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_DASH_L:
        if (p_player->credits >= 10)
        {
            p_player->x = (p_player->x - 8 + 100) % 100;
            p_player->credits -= 10;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_DASH_R:
        if (p_player->credits >= 10)
        {
            p_player->x = (p_player->x + 8) % 100;
            p_player->credits -= 10;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_DASH_U:
        if (p_player->credits >= 10)
        {
            p_player->y = (p_player->y - 8 + 100) % 100;
            p_player->credits -= 10;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_DASH_D:
        if (p_player->credits >= 10)
        {
            p_player->y = (p_player->y + 8) % 100;
            p_player->credits -= 10;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_TELEPORT_L:
        if (p_player->credits >= 2)
        {
            p_player->x = (p_player->x - 8 + 100) % 100;
            p_player->credits -= 2;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_TELEPORT_R:
        if (p_player->credits >= 2)
        {
            p_player->x = (p_player->x + 8) % 100;
            p_player->credits -= 2;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_TELEPORT_U:
        if (p_player->credits >= 2)
        {
            p_player->y = (p_player->y - 8 + 100) % 100;
            p_player->credits -= 2;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_TELEPORT_D:
        if (p_player->credits >= 2)
        {
            p_player->y = (p_player->y + 8) % 100;
            p_player->credits -= 2;
            world_paint_spot(p_player->x, p_player->y, p_player->id);
        }
        break;
    case ACTION_SPLASH:
        if (p_player->credits >= 8)
        {
            world_paint_spot((p_player->x - 1 + 100) % 100, p_player->y, p_player->id);                   // Gauche
            world_paint_spot((p_player->x + 1) % 100, p_player->y, p_player->id);                         // Droite
            world_paint_spot(p_player->x, (p_player->y - 1 + 100) % 100, p_player->id);                   // Haut
            world_paint_spot(p_player->x, (p_player->y + 1) % 100, p_player->id);                         // Bas
            world_paint_spot((p_player->x - 1 + 100) % 100, (p_player->y - 1 + 100) % 100, p_player->id); // Haut-Gauche
            world_paint_spot((p_player->x + 1) % 100, (p_player->y - 1 + 100) % 100, p_player->id);       // Haut-Droite
            world_paint_spot((p_player->x - 1 + 100) % 100, (p_player->y + 1) % 100, p_player->id);       // Bas-Gauche
            world_paint_spot((p_player->x + 1) % 100, (p_player->y + 1) % 100, p_player->id);             // Bas-Droite
            p_player->credits -= 8;
        }
        break;
    case ACTION_BOMB:
        if (p_player->credits >= 8)
        {
            for (int i = 0; i < MAX_BOMBS; i++)
            {
                if (!bombs[i].bombeactive) // Trouver un emplacement libre
                {
                    bombs[i].x = p_player->x;
                    bombs[i].y = p_player->y;
                    bombs[i].minuteurbombe = BOMBE_MINUTEUR;
                    bombs[i].bombeactive = 1;
                    bombs[i].IDbombe = p_player->id;
                    p_player->credits -= 9;
                    break;
                }
            }
        }
        break;

    case ACTION_STILL:
        if (p_player->credits >= 1)
        {
            p_player->credits -= 1;
        }
        break;
    case ACTION_NUMBER:
        break;
    }
    // }
}
