#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

typedef Uint32 u32;

static const int width = 640;
static const int height = 480;
// g++ -std=c++17 main.cpp -IC:\SDL\include -LC:\SDL\lib\x86 -Werror -Wall -lSDL2main -lSDL2 -o main
int main(int argc, char* argv[]) {
    bool quit = false;
    bool lmb_down = false;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Failed to initialise SDL\n");
        return 0;
    }
    SDL_Window* window     = SDL_CreateWindow("Blank canvas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture   = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height); // pixles are 32 bit values, 8 bits for each channel

    u32* pixels = (u32*)malloc(width * height * sizeof(u32));
    memset(pixels, 255, width * height * sizeof(u32)); // clear to white
    
    while(!quit) {
        SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(u32));
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT: {
                quit = true;
                break;
            }
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
                    pixels[mouse_y * width + mouse_x] = 0;
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
