#version 110

uniform sampler2D f_shape;
uniform float f_shape_power;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    float shape_dst = texture2D(f_shape, f_uvpos).r;

    //contour with width of 5px
    float shape_mask = (1.0 / 10.0 - shape_dst) * 100.0;

    gl_FragColor = vec4(1.0, 0.0, 0.0, shape_mask);
    //gl_FragColor = vec4(shape_nearest, 0.0, 1.0);
}