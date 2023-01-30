#version 110

uniform sampler2D f_shape;
uniform float f_shape_power;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    float shape_mask = texture2D(f_shape, f_uvpos).r * f_shape_power;

    gl_FragColor = vec4(vec3(shape_mask), 1.0);
}