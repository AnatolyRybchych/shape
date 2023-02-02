#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "glutil.h"
#include "panic.h"
#include "shape.h"

SDL_Window *window;
SDL_GLContext *glrc;
int width, height;

GLuint shape;

GLuint prog;
GLuint v_vpos_pos;
GLuint f_shape_pos;
GLuint f_shape_power_pos;

void render(void){
    static float vertices[] = {
        -1, -1, 1, 1, -1, 1,
        -1, -1, 1, 1, 1, -1,
    };

    glViewport(0, 0, width, height);

    glUseProgram(prog);
    glEnableVertexAttribArray(v_vpos_pos);
    glVertexAttribPointer(v_vpos_pos, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glUniform1f(f_shape_power_pos, height * 0.5);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shape);
    glUniform1i(f_shape_pos, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(v_vpos_pos);
    glUseProgram(0);
}

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
        width = ev->data1;glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        height = ev->data2;
    }break;
    case SDL_WINDOWEVENT_EXPOSED:{
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        SDL_GL_SwapWindow(window);
    }break;
    default: break;
    }
}

void init_shader_program(void){
    prog = build_program_from_files("shaders/frag.glsl", "shaders/vert.glsl");
    if(!is_program_ok(prog)){
        char log[1024];
        get_program_info_log(prog, log);
        PANIC("%s", log);
    }

    v_vpos_pos = glGetAttribLocation(prog, "v_vpos");
    f_shape_pos = glGetUniformLocation(prog, "f_shape");
    f_shape_power_pos = glGetUniformLocation(prog, "f_shape_power");
}

float pp_dst(float p1x, float p1y, float p2x, float p2y){
    float dx = p2x - p1x;
    float dy = p2y - p1y;
    
    return sqrtf(dx * dx + dy * dy);
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shape s;
    shape_init(&s, -0.5, 0.5);
    Bezier b = {
        .to = {0.5, -0.5},

        .c1 = {-0.5, -0.5},
        .c2 = {0.5, 0.5},
    };

    shape_bezier(&s, &b);
    shape = shape_create_contour_nearest_texture(&s, 64, 64);
    shape_free(&s);

    init_shader_program();

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
