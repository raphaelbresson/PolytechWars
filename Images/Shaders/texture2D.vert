// Version du GLSL

#version 330 core


// Entrées

in vec3 in_Vertex;
in vec2 in_TexCoord0;

// Uniform

uniform mat4 mvp;


// Sortie

out vec2 coordTexture;

// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = mvp * vec4(in_Vertex, 1.0);
    coordTexture = in_TexCoord0;
}
