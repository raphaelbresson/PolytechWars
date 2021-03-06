#version 150 core

in vec2 texcoord;

uniform sampler2D tex;

out vec4 out_color;

void main(void) 
{
  out_color = texture2D(tex, texcoord);
}