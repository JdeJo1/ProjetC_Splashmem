#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "splash.h"

void show_splash_screen()
{
    if (TTF_Init() == -1) {
        SDL_Log("Erreur d'initialisation de SDL_ttf : %s", TTF_GetError());
        return;
    }

    SDL_Window* splash_window = SDL_CreateWindow("Splash Screen",
                                                 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                 800, 600, SDL_WINDOW_SHOWN);
    if (!splash_window)
    {
        SDL_Log("Erreur de création de la fenêtre du splash screen : %s", SDL_GetError());
        return;
    }

    SDL_Renderer* splash_renderer = SDL_CreateRenderer(splash_window, -1, SDL_RENDERER_ACCELERATED);
    if (!splash_renderer)
    {
        SDL_Log("Erreur de création du renderer du splash screen : %s", SDL_GetError());
        SDL_DestroyWindow(splash_window);
        return;
    }

    // Charger l'image du splash screen
    SDL_Surface* splash_surface = IMG_Load("splash.png");
    if (!splash_surface)
    {
        SDL_Log("Erreur de chargement de l'image : %s", IMG_GetError());
        SDL_DestroyRenderer(splash_renderer);
        SDL_DestroyWindow(splash_window);
        return;
    }

    SDL_Texture* splash_texture = SDL_CreateTextureFromSurface(splash_renderer, splash_surface);
    SDL_FreeSurface(splash_surface);

    if (!splash_texture)
    {
        SDL_Log("Erreur de création de la texture : %s", SDL_GetError());
        SDL_DestroyRenderer(splash_renderer);
        SDL_DestroyWindow(splash_window);
        return;
    }

    // Charger la police et créer le texte
    TTF_Font* font = TTF_OpenFont("Arial.ttf", 24);
    if (!font)
    {
        SDL_Log("Erreur chargement police : %s", TTF_GetError());
        SDL_DestroyTexture(splash_texture);
        SDL_DestroyRenderer(splash_renderer);
        SDL_DestroyWindow(splash_window);
        return;
    }

    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, "Lancez le jeu avec la touche ENTREE", color);
    if (!text_surface)
    {
        SDL_Log("Erreur création surface texte : %s", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyTexture(splash_texture);
        SDL_DestroyRenderer(splash_renderer);
        SDL_DestroyWindow(splash_window);
        return;
    }

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(splash_renderer, text_surface);
SDL_Rect text_rect = { 
    800 - text_surface->w - 20,  // Aligné à droite avec un petit décalage
    20,                          // Position en haut avec un décalage de 20px
    text_surface->w, 
    text_surface->h };
    SDL_FreeSurface(text_surface);

    if (!text_texture)
    {
        SDL_Log("Erreur création texture texte : %s", SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyTexture(splash_texture);
        SDL_DestroyRenderer(splash_renderer);
        SDL_DestroyWindow(splash_window);
        return;
    }

    // Affichage de l'image et du texte
    SDL_RenderClear(splash_renderer);
    SDL_RenderCopy(splash_renderer, splash_texture, NULL, NULL);
    SDL_RenderCopy(splash_renderer, text_texture, NULL, &text_rect);
    SDL_RenderPresent(splash_renderer);

    // Attente jusqu'à une touche Entrée
    SDL_Event event;
    int running = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    running = 0;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                running = 0;
            }
        }
        SDL_Delay(100);
    }

    // Nettoyage
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
    SDL_DestroyTexture(splash_texture);
    SDL_DestroyRenderer(splash_renderer);
    SDL_DestroyWindow(splash_window);
    TTF_Quit();
}