#include <stdio.h>
#include <stdlib.h>
#include "actions.h"
#include "param.h"
#include "player.h"
#include "world.h"
#include "splash.h"

/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player *players[MAX_PLAYERS] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players()
{
    int i = 0;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        players[i] = (t_player *)malloc(sizeof(t_player));
        player_init(players[i], i);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
    actions_do(p_player, p_player->get_action());
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos]  = num;
}


/*Bombe*/
bombe bombs[MAX_BOMBS];

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_update_bombe()
{
    for (int i = 0; i < MAX_BOMBS; i++)
    {
        if (bombs[i].bombeactive)
        {
            if (bombs[i].minuteurbombe > 0)  
            {
                bombs[i].minuteurbombe--;
            }

            if (bombs[i].minuteurbombe == 0) // Explosion après 5 tours
            {
                int player_id = bombs[i].IDbombe; 

                // Marquer une zone de 3x3 autour de la bombe
                for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        int bx = (bombs[i].x + dx + MAP_SIZE) % MAP_SIZE;
                        int by = (bombs[i].y + dy + MAP_SIZE) % MAP_SIZE;

                        world_paint_spot(bx, by, player_id); 
                    }
                }

                bombs[i].bombeactive = 0; // Désactiver la bombe après explosion
            }
        }
    }
}

int world_gameover()
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (players[i]->credits > 0)  // Si au moins un joueur a encore des crédits, la partie continue
        {
            return 0;
        }
    }
    return 1;  // Si tous les joueurs ont 0 crédits, la partie est terminée
}

void world_detruirefenetre()
{
    printf("Gameover ! Tous les joueurs ont épuisé leurs crédits.\n");

    quitting = 1;

    if (credits_renderer)
    {
        SDL_DestroyRenderer(credits_renderer);
        credits_renderer = NULL;
    }

    if (credits_window)
    {
        SDL_DestroyWindow(credits_window);
        credits_window = NULL;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }

    TTF_Quit();
    SDL_Quit();

}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner() {
    //gestion des scores
    int score[MAX_PLAYERS] = {0};

    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++) {
        if (mapmem[i] > 0 && mapmem[i] <= MAX_PLAYERS) {
            score[mapmem[i] - 1]++;
        }
    }

    int max = score[0];
    int gagnant = 1;

    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (score[i] > max) {
            max = score[i];
            gagnant = i + 1;
        }
    }
    printf("Scores des joueurs :\n");
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        printf("Joueur %d : %d cases coloriées\n", i + 1, score[i]);
    }
    printf("Le gagnant est joueur %d, %d cases coloriées\n", gagnant, max);
    
    exit(0);
}
