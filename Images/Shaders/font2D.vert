#version 330 core

uniform mat4 mvp;

in vec2 in_Vertex;
in vec2 in_CoordTex;

out vec2 coordTex;

void main()
{
  gl_Position = mvp*vec4(in_Vertex,0.0,0.0);
  coordTex = in_CoordTex;
}