#version 110

attribute vec4 v_vpos;

varying vec2 f_vpos;
varying vec2 f_uvpos;

void main(){
    f_vpos = v_vpos.xy;
    f_uvpos = v_vpos.xy * vec2(0.5) + vec2(0.5);
    
    gl_Position = v_vpos;
}