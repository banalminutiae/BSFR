#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <Windows.h>

#define STB_DS_IMPLEMENTATION
#include "lib\stb_ds.h"
#include "obj_loader.h"

typedef Uint32 u32;

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
// g++ -std=c++17 main.cpp -IC:\SDL\include -LC:\SDL\lib\x86 -Werror -Wall -lSDL2main -lSDL2 -o main
// fitzcarraldo, molly aida? Ucayli, Iquitos

// separate engine and sdl stuff out into namespace
// read OBJ and display wireframe
// textures and lighting
int main(int argc, char* argv[]) {
    // hides background cmd instance
    HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle,SW_HIDE);
    
    bool quit = false;
    bool lmb_down = false;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialise SDL\n");
        return 0;
    }
    SDL_Window* window     = SDL_CreateWindow("paint clone",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SCREEN_WIDTH, SCREEN_HEIGHT,
                                              0);
    assert(window);
    
    SDL_Texture* texture   = SDL_CreateTexture(renderer,
                                               SDL_PIXELFORMAT_ARGB8888,
                                               SDL_TEXTUREACCESS_STATIC,
                                               SCREEN_WIDTH,
                                               SCREEN_HEIGHT); // pixles are 32 bit values, 8 bits for each channel
    assert(texture);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    assert(renderer);

    u32* pixels = (u32*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32));
    memset(pixels, 255, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u32)); // clear to white, also the swap buffer 
    
    while(!quit) {
        SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(u32));
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: {
                quit = true;
                break;
            }
                // fallthrough from here is filler content
            case SDL_MOUSEBUTTONUP: {
                if (event.button.button == SDL_BUTTON_LEFT) lmb_down = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) lmb_down = true;
                break;
            }
            case SDL_MOUSEMOTION: {
                if (lmb_down) {
                    int mouse_x = event.motion.x;
                    int mouse_y = event.motion.y;
                    pixels[mouse_y * SCREEN_WIDTH + mouse_x] = 0;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    free(pixels);
    SDL_Quit();
    return 0;
}
