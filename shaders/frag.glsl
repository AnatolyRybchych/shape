#version 110

uniform sampler2D f_shape1;
uniform sampler2D f_shape2;
uniform float f_shape_power;
uniform float f_time;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    vec2 shape1_nearest = texture2D(f_shape1, f_uvpos).rg;
    vec2 shape2_nearest = texture2D(f_shape2, f_uvpos).rg;

    vec2 shape_nearest = mix(shape1_nearest, shape2_nearest, abs(sin(f_time * 2.0)));

    float shape_mask = (0.1 - distance(shape_nearest, f_vpos)) * f_shape_power;

    gl_FragColor = vec4(1.0, 0.0, 0.0, shape_mask);
    //gl_FragColor = vec4(shape_nearest, 0.0, 1.0);
}