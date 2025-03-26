#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "param.h"
#include "splash.h"
#include "world.h"
#include "splash.h"

int          quitting      = 0;
SDL_Window*  window        = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Window* credits_window = NULL;
SDL_Renderer* credits_renderer = NULL;

int global_credits = 9000;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
int SDLCALL watch(void* userdata, SDL_Event* event)
{
    if (event->type == SDL_APP_WILLENTERBACKGROUND)
    {
        quitting = 1;
    }

    return 1;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        SDL_Log("Erreur d'initialisation de SDL: %s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) // Initialiser SDL2_image pour charger l'image
    {
        SDL_Log("Erreur d'initialisation de SDL2_image: %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() == -1)
    {
        SDL_Log("Erreur d'initialisation de SDL_ttf: %s", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    show_splash_screen();

    int screen_width = 800;
    window = SDL_CreateWindow("SplashMem", screen_width / 2, 50, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log("Erreur de creation fenêtre splashmem: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    credits_window = SDL_CreateWindow("Credits", 50, 50, WIN_SIZE / 2, WIN_SIZE, SDL_WINDOW_SHOWN);
    if (!credits_window)
    {
        SDL_Log("Erreur de creation fenêtre credits: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    credits_renderer = SDL_CreateRenderer(credits_window, -1, SDL_RENDERER_ACCELERATED);
    if (!credits_renderer)
    {
        SDL_Log("Failed to create credits renderer: %s", SDL_GetError());
        SDL_DestroyWindow(credits_window);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_AddEventWatch(watch, NULL);
    if (argc != 5)
    {
        printf("Wrong argument number\n");
        return 1;
    }

    inits(argc, argv);
    main_loop();
    world_get_winner();
    SDL_DestroyRenderer(credits_renderer);
    SDL_DestroyWindow(credits_window);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(0);
}
