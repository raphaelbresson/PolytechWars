#version 150 core

in vec2 texcoord;

uniform vec4 color;

out vec4 out_color;

void main(void) 
{
  out_color = color;
} 
