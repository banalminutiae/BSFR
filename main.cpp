#include <stdio.h>
#include <SDL.h>

static const int width = 640;
static const int height = 480;

int main(int argc, char** argv) {
    bool quit = false;
    bool lmb_down = false;
    SDL_Event event;

    SDL_Init(SDL_Init_Video);
    SDL_Window* window     = SDL_CreateWindow("Blank canvas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture   = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height); // pixles are 32 bit values, 8 bits for each channel

    Uint32* pixels = (UInt32*)malloc(width * height * sizeof(Uint32*));
    memset(pixels, 255, width * height * sizeof(UInt32)); // clear to white
    
    while(!quit) {
        SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_Quit: {
                quit = true;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                if (event.button.button == SDL_BUTTON_LEFT) lmb_down = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.button == SDL_BUTTON_LEFT) lmb_down = true;
                break:
            }
            case SDL_MOUSEMOTION: {
                if (lmb_down) {
                    int mouse_x = event.motion.x;
                    int mouse_y = event.motion.y;
                    pixels[mouse_y * height + mouse_x] = 0;
                }
                break; 
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Destroy_Renderer(renderer);
    SDL_DestroyTexture(texture);
    free(pixels);
    SDL_Quit();
    return 0;
}
