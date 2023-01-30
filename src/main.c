#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "panic.h"

int main(void){
    int status = SDL_Init(SDL_INIT_VIDEO);
    PANIC_LTZ(status);

    SDL_Window *window = SDL_CreateWindow("", 0, 0, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    PANIC_NULL(window);

    SDL_ShowWindow(window);

    SDL_Event ev;
    while (true){
        SDL_WaitEvent(&ev);
        if(ev.type == SDL_QUIT){
            break;
        }
    }
    return 0;
}
