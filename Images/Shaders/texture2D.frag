// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;

// Uniform

uniform sampler2D tex;


// Sortie 

out vec4 out_Color;



// Fonction main

void main()
{
    out_Color = texture2D(tex, coordTexture);
}
