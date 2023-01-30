#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "glutil.h"
#include "panic.h"

SDL_Window *window;
SDL_GLContext *glrc;

GLuint prog;
GLuint v_vpos_pos;
GLuint f_shape_pos;
GLuint f_shape_power_pos;

void on_event(const SDL_Event *ev){
    switch (ev->type){
    case SDL_QUIT:
        exit(0);
        break;
    }
}

void on_winevent(const SDL_WindowEvent *ev){
    switch (ev->event){
    case SDL_WINDOWEVENT_RESIZED:{
        glViewport(0, 0, ev->data1, ev->data2);
    }break;
    case SDL_WINDOWEVENT_EXPOSED:{
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }break;
    default: break;
    }
}

GLuint init_shader_program(void){
    GLuint result = build_program_from_files("shaders/frag.glsl", "shaders/vert.glsl");
    if(!is_program_ok(result)){
        char log[1024];
        get_program_info_log(result, log);
        PANIC("%s", log);
    }
    return result;
}

int main(void){
    int status = SDL_Init(SDL_INIT_VIDEO);
    PANIC_LTZ(status);

    window = SDL_CreateWindow("", 0, 0, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
    PANIC_NULL(window);

    glrc = SDL_GL_CreateContext(window);
    PANIC_NULL(glrc);

    SDL_GL_MakeCurrent(window, glrc);

    GLenum glew_init_status = glewInit();
    PANIC_FALSE(glew_init_status != GLEW_OK);

    prog = init_shader_program();

    SDL_ShowWindow(window);

    SDL_Event ev;
    while (true){
        SDL_WaitEvent(&ev);
        if(ev.type == SDL_WINDOWEVENT){
            on_winevent(&ev.window);
        }
        else{
            on_event(&ev);
        }
    }
    return 1;
}
