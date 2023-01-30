#ifndef GLUTIL_H_
#define GLUTIL_H_

#include <stdbool.h>

#include <GL/glew.h>

GLuint compile_shader(GLenum type, const char *src);
GLuint compile_shader_from_file(GLenum type, const char *src_file);

GLuint build_program(GLuint fragment, GLuint vertex);
GLuint build_program_from_files(const char *fragment_path, const char *vertex_path);

bool is_shader_ok(GLuint shader);
bool is_program_ok(GLuint program);

void get_program_info_log(GLuint program, char log[1024]);

#endif //GLUTIL_H_