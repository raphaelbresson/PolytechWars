
/*
 * PROGRAMME DE GENERATION DU FICHIER D'ERREURS :
 * AFFICHE 2 TRIANGLES BLANCS ET QUITTE IMMEDIATEMENT
 */


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

int main()
{
  //INITIALISATION DES BIBLIOTHEQUES SDL
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  TTF_Init();
  
  //PARAMETRES ET CREATION DE LA FENETRE ET DU CONTEXTE OPENGL
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  
  //SHADER MINIMAL
  GLuint progID = glCreateProgram();
  GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
  char *sourceVert = "#version 150 core \n in vec2 vertex; \n void main { glPosition = vec4(vertex, 0, 1);}"; 
  glShaderSource(vertID, 1, (const GLchar**) &sourceVert, NULL);
  glCompileShader(vertID);
  GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
  char *sourceFrag = "#version 150 core out color \n void main { color = vec4(255,255,255,255); }";
  glShaderSource(fragID, 1, (const GLchar**) &sourceFrag, NULL);
  glCompileShader(fragID);
  glAttachShader(progID, vertID);
  glAttachShader(progID, fragID);
  glBindAttribLocation(progID, 0, "vertex");
  glLinkProgram(progID);
  
  //CREATION DES TRIANGLES
  float vert [12] = { 0.0,0.0,  1.0,0.0,   1.0,1.0,
		      0.0,0.0,  0.0,1.0,   1.0,1.0};
  GLuint vboID=0,vaoID=0;
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER,vboID);
    glBufferData(GL_ARRAY_BUFFER,12*sizeof(float), vert, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
      glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);
  
  //AFFICHAGE
  glUseProgram(progID);
    glBindVertexArray(vaoID);
      glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  glUseProgram(0);
  
  SDL_GL_SwapWindow(window);
  
  //LIBERATION DES BUFFERS
  glDeleteBuffers(1,&vboID);
  glDeleteVertexArrays(1,&vaoID);
  
  //DESTRUCTION DES SHADERS
  glDeleteShader(vertID);
  glDeleteShader(progID);
  glDeleteProgram(progID);
  
  //DESTRUCTION DE LA FENETRE
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  //FERMETURE DES BIBLIOTHEQUES SDL
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}