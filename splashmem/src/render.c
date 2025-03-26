#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "actions.h"
#include "param.h"
#include "splash.h"
#include "world.h"

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_map()
{
    int      i = 0;
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    screenSurface = SDL_GetWindowSurface(window);

    for (i = 0; i < SPOT_NUM; i++)
    {
        rect.x = (i % MAP_SIZE) * SQUARE_SIZE;
        rect.y = (i / MAP_SIZE) * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[mapmem[i]]);
    }
    SDL_UpdateWindowSurface(window);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void render_player()
{
    int i         = 0;
    screenSurface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        rect.x = players[i]->x * SQUARE_SIZE;
        rect.y = players[i]->y * SQUARE_SIZE;
        SDL_FillRect(screenSurface, &rect, colors[i] - 0x00202020);
    }
    SDL_UpdateWindowSurface(window);
}

void render_credits()
{
    SDL_SetRenderDrawColor(credits_renderer, 0, 0, 0, 255);
    SDL_RenderClear(credits_renderer);

    TTF_Font* font = TTF_OpenFont("Arial.ttf", 24);
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Color color = {255, 255, 255, 255};

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        char text[50];
        snprintf(text, sizeof(text), "Joueur %d: %d credits", players[i]->id, players[i]->credits);

        SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(credits_renderer, surface);

        SDL_Rect dest = {10, i * 25, surface->w, surface->h};
        SDL_RenderCopy(credits_renderer, texture, NULL, &dest);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(credits_renderer);
    TTF_CloseFont(font);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void main_loop()
{
    while (!quitting)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)  
            {
                quitting = 1;
            }
            else if (event.type == SDL_WINDOWEVENT) 
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    SDL_Window* closed_window = SDL_GetWindowFromID(event.window.windowID);

                    if (closed_window == window)  
                    {
                        quitting = 1;
                    }
                    else if (closed_window == credits_window) 
                    {
                        SDL_DestroyWindow(credits_window);
                        credits_window = NULL;
                    }
                }
            }
        }

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            world_do_player_action(players[i]);
        }

        render_map();
        render_player();
        render_credits();
        world_update_bombe();
        SDL_Delay(100);

        // Vérifie si le jeu est terminé
        if (world_gameover())  
        {
            quitting = 1;  
            world_detruirefenetre();   // Appelle la fonction game_over
        }
    }

    // Détruire les fenêtres
    if (credits_window)
        SDL_DestroyWindow(credits_window);
    
    SDL_DestroyWindow(window);
}
