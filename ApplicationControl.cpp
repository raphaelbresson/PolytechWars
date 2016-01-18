#include "ApplicationControl.h"
#include <iostream>
/*
 * Initialisation des bibliotheques SDL 2.0, SDL_Image 2.0 et SDL_TTF 2.0
 */
bool ApplicationControl::initSDL()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    return false;
  if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) < 0)
    return false;
  if(TTF_Init() ==-1)
    return false;
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) 
    return false;
  return true;  
}

/*
 * Initialisation de OpenGL 3.3 et création de la fenetre et du contexte openGL
 */
bool ApplicationControl::initGL()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  
  m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);
  if(!m_window)
    return false;
  m_context = SDL_GL_CreateContext(m_window);
  if(m_context == 0)
    return false;
  glEnable(GL_DEPTH_TEST);
  SDL_ShowCursor(SDL_DISABLE);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  return true;
}

/*
 * Constructeur
 */
ApplicationControl::ApplicationControl(unsigned int windowWidth, unsigned int windowHeight) : 
  m_windowWidth(windowWidth) , m_windowHeight(windowHeight), m_sceneMgr(), m_window(NULL), m_context(0)
{
}


/*
 * Destructeur
 */
ApplicationControl::~ApplicationControl()
{
  SDL_GL_DeleteContext(m_context);
  SDL_DestroyWindow(m_window);
  Mix_CloseAudio();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

/*
 * initialisation de l'application
 */
bool ApplicationControl::init()
{
  if(!initSDL())
    return false;
  if(!initGL())
    return false;
  return true;
}


bool ApplicationControl::execute()
{
  return m_sceneMgr.execute(m_window,m_windowWidth, m_windowHeight);
}