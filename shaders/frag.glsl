#version 110

uniform sampler2D f_shape1;
uniform sampler2D f_shape2;
uniform float f_shape_power;
uniform float f_time;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    float shape1 = texture2D(f_shape1, f_uvpos).r;
    float shape2 = texture2D(f_shape2, f_uvpos).r;

    float shape = mix(shape1, shape2, sin(f_time) * 0.5 + 0.5);

    float shape_mask = shape * f_shape_power;

    gl_FragColor = vec4(shape_mask, 0.0, 0.0, 1.0);
}