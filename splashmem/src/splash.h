#ifndef __SPALSH__
#define __SPLASH__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window*  window;
extern SDL_Surface* screenSurface;
extern uint32_t     colors[];
extern int          quitting;

extern SDL_Window* credits_window;
extern SDL_Renderer* credits_renderer;

void show_splash_screen();
/**
 * @brief init the color palette
 *
 * @param format
 */
void init_colors(SDL_PixelFormat* format);

/**
 * @brief do some inits
 *
 * @param argc arg count
 * @param argv  string vector
 */
void inits(int argc, char* argv[]);

/**
 * @brief main loop of the program
 *
 */
void main_loop();

#endif