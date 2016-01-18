#version 150 core

in vec2 in_Vertex;
in vec2 in_TexCoord0;
uniform mat4 mvp;

out vec2 texcoord;

void main(void) {
  gl_Position = mvp*vec4(in_Vertex, 0.0, 1.0);
  texcoord = in_TexCoord0;
}