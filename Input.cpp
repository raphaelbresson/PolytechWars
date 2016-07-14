#include "Input.h"

#define NB_MOUSE_BUTTON 8

Input::Input(int maxY) : 
  m_maxY(maxY),m_x(0), m_y(0), m_xRel(0), m_yRel(0), m_terminer(false), m_clickCond(), m_clickMutex()
{
  m_predicateClick = ATOMIC_VAR_INIT(false);
  for(unsigned int i = 0 ; i < SDL_NUM_SCANCODES ; i++)
  {
    m_keys[i] = false;
    m_keysRelease[i] = false;
  }
  for(unsigned int i = 0 ; i < NB_MOUSE_BUTTON ; i++)
  {
    m_mouseButtons[i] = false;
    m_mouseButtonsRelease[i] = false;
  }
}


Input::~Input()
{
}

void Input::update()
{
  for(unsigned int i = 0 ; i < SDL_NUM_SCANCODES ; i++)
    m_keysRelease[i] = false;
  for(unsigned int i = 0 ; i < NB_MOUSE_BUTTON ; i++)
    m_mouseButtonsRelease[i] = false;
  m_xRel = 0;
  m_yRel = 0;
  while(SDL_PollEvent(&m_evenements))
  {
    switch(m_evenements.type)
    {
      case SDL_KEYDOWN:
	m_keys[m_evenements.key.keysym.scancode] = true;
	m_keysRelease[m_evenements.key.keysym.scancode] = false;
	break;
      case SDL_KEYUP:
	m_keys[m_evenements.key.keysym.scancode] = false;
	m_keysRelease[m_evenements.key.keysym.scancode] = true;
	break;
      case SDL_MOUSEBUTTONDOWN:
	m_mouseButtons[m_evenements.button.button] = true;
	m_mouseButtonsRelease[m_evenements.button.button] = false;
	break;    
      case SDL_MOUSEBUTTONUP:
	m_mouseButtons[m_evenements.button.button] = false;
	m_mouseButtonsRelease[m_evenements.button.button] = true;
	break;
      case SDL_MOUSEMOTION:
	m_x = m_evenements.motion.x;
	m_y = m_evenements.motion.y;
	m_xRel = m_evenements.motion.xrel;
	m_yRel = m_evenements.motion.yrel;
	break;
      case SDL_WINDOWEVENT:
	if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
	  m_terminer = true;
	break;
      default:
	break;
    }
  }
}

bool Input::getKey(const SDL_Scancode i) const
{
  return m_keys[i];
}

bool Input::getKeyRelease(const SDL_Scancode i) const
{
  return m_keysRelease[i];
}

bool Input::mouseMove() const
{
  if(m_xRel != 0 || m_yRel != 0)
    return true;
  return false;
}

bool Input::getMouseButton(Uint8 i) const 
{
  return m_mouseButtons[i];
}

bool Input::getMouseButtonRelease(Uint8 i) const
{
  return m_mouseButtonsRelease[i];
}

int Input::getXRel() const
{
  return m_xRel;
}

int Input::getYRel() const
{
  return m_yRel;
}

int Input::getXAbs() const
{
  return m_x;
}

int Input::getYAbs() const
{
  return m_maxY - m_y;
}

std::condition_variable *Input::getConditionClick()
{
  return &m_clickCond;
}

std::mutex *Input::getClickMutex()
{
  return &m_clickMutex;
}

bool Input::getPredicateClick()
{
  return m_predicateClick;
}