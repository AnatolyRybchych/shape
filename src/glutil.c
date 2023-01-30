#include <stdlib.h>

#include "futil.h"
#include "glutil.h"

GLuint compile_shader(GLenum type, const char *src){
    GLuint shader = glCreateShader(type);
    if(shader == 0){
        return 0;
    }

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

GLuint compile_shader_from_file(GLenum type, const char *src_file){
    char *fdata = alloc_from_file(src_file);
    GLuint result = compile_shader(type, fdata);
    free(fdata);

    return result;
}

GLuint build_program(GLuint fragment, GLuint vertex){
    GLuint prog = glCreateProgram();
    if(prog == 0){
        return 0;
    }
    
    glAttachShader(prog, fragment);
    glAttachShader(prog, vertex);

    glLinkProgram(prog);

    return prog;
}

GLuint build_program_from_files(const char *fragment_path, const char *vertex_path){
    GLuint frag = compile_shader_from_file(GL_FRAGMENT_SHADER, fragment_path);
    GLuint vert = compile_shader_from_file(GL_VERTEX_SHADER, vertex_path);

    GLuint result = build_program(vert, frag);

    glDeleteShader(frag);
    glDeleteShader(vert);

    return result;
}

bool is_shader_ok(GLuint shader){
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    return status == 0;
}

bool is_program_ok(GLuint program){
    GLint status;
    glGetShaderiv(program, GL_LINK_STATUS, &status);

    return status == 0;
}
