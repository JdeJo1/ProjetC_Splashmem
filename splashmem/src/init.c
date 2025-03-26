#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "actions.h"
#include "param.h"
#include "splash.h"
#include "world.h"

uint32_t colors[MAX_PLAYERS + 1] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
    colors[1] = SDL_MapRGB(format, 0xFF, 0, 0);
    colors[2] = SDL_MapRGB(format, 0, 0xFF, 0);
    colors[3] = SDL_MapRGB(format, 0, 0x0, 0xFF);
    colors[4] = SDL_MapRGB(format, 0xFF, 0, 0xFF);
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */

void inits(int argc, char* argv[]) {
    // Récupération des bibliothèques passées en argument
    char *biblio_P[4];
    for (int i = 0; i < 4; i++) {
        biblio_P[i] = argv[i + 1];
    }

    // Récupération de la surface de la fenêtre
    screenSurface = SDL_GetWindowSurface(window);
    SDL_PixelFormat* format = screenSurface->format;
    init_colors(format);

    // Chargement des bibliothèques dynamiques
    void *p_open[4];
    for (int i = 0; i < 4; i++) {
        p_open[i] = dlopen(biblio_P[i], RTLD_LAZY);
        if (!p_open[i]) {
            fputs(dlerror(), stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    actions_init();
    world_create_players();

    // Liaison des fonctions get_action des joueurs
    char *error;
    for (int i = 0; i < 4; i++) {
        players[i]->get_action = dlsym(p_open[i], "get_action");
        if ((error = dlerror()) != NULL) {
            fputs(error, stderr);
            exit(EXIT_FAILURE);
        }
    }

    printf("Initialisation terminée\n");
}