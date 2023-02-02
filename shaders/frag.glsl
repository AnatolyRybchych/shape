#version 110

uniform sampler2D f_shape;
uniform float f_shape_power;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    vec2 shape_nearest = texture2D(f_shape, f_uvpos).rg;

    float shape_mask = (0.1 - distance(shape_nearest, f_vpos)) * f_shape_power;

    gl_FragColor = vec4(1.0, 0.0, 0.0, shape_mask);
    //gl_FragColor = vec4(shape_nearest, 0.0, 1.0);
}