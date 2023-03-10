#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "glutil.h"
#include "panic.h"
#include "shape.h"

SDL_Window *window;
SDL_GLContext *glrc;
int width, height;

GLuint shape1;
GLuint shape2;

GLuint prog;
GLuint v_vpos_pos;
GLuint f_shape1_pos;
GLuint f_shape2_pos;
GLuint f_time_pos;
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
    glUniform1f(f_time_pos, SDL_GetTicks() * 0.001);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shape1);
    glUniform1i(f_shape1_pos, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shape2);
    glUniform1i(f_shape1_pos, 1);

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
    f_shape1_pos = glGetUniformLocation(prog, "f_shape1");
    f_shape2_pos = glGetUniformLocation(prog, "f_shape2");
    f_time_pos = glGetUniformLocation(prog, "f_time");
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

    //disable v-sync
    SDL_GL_SetSwapInterval(0);

    GLenum glew_init_status = glewInit();
    PANIC_FALSE(glew_init_status != GLEW_OK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shape s;
    shape_init(&s, -0.5, 0.5);
    shape_bezier(&s, &(Bezier){
        .to = {0.5, -0.5},

        .c1 = {-0.5, -0.5},
        .c2 = {0.5, 0.5},
    });
    shape1 = shape_create_contour_nearest_texture(&s, 64, 64);
    shape_free(&s);

    shape_init(&s, -0.8, 0.8);
    shape_bezier(&s, &(Bezier){
        .to = {0.8, -0.8},

        .c1 = {-0.8, 0.8},
        .c2 = {0.8, -0.8},
    });
    shape2 = shape_create_contour_nearest_texture(&s, 64, 64);
    shape_free(&s);

    init_shader_program();

    SDL_ShowWindow(window);

    SDL_Event ev;

    //avarage for last 100 frames
    Uint64 mstime = 0;
    Uint64 frames = 0;
    while (true){
        if(SDL_PollEvent(&ev)){
            if(ev.type == SDL_WINDOWEVENT){
                on_winevent(&ev.window);
            }
            else{
                on_event(&ev);
            }
        }
        else{
            Uint32 msframetime = SDL_GetTicks();

            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            render();
            SDL_GL_SwapWindow(window);

            msframetime = SDL_GetTicks() - msframetime;
            mstime += msframetime;
            frames++;

            //40_000 fps on GTX 1650 1920x1080 window, LOL
            if(frames == 1000){
                system("clear");
                printf("fps:%f\n", 1000 / (mstime / (float)frames));

                frames = 0;
                mstime = 0;
            }
        }
    }
    return 1;
}
