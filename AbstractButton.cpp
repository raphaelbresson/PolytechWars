#include "AbstractButton.h"

static Input *s_input = NULL;

AbstractButton::AbstractButton(Shader* shad, glm::vec2 position, Input *input) : 
    AbstractWidget(shad,position), m_stopThread(false), m_threadClickEvent(&AbstractButton::eventHandler,this),
    m_clicked((input->getConditionClick())), m_clickedLock(*input->getClickMutex()), m_dimensions(0.0f,0.0f)
{
  if(!s_input)
    s_input = input;
}

AbstractButton::~AbstractButton()
{
  m_stopThread = true;
  if(m_threadClickEvent.joinable())
    m_threadClickEvent.join();
}

bool predicateClick()
{
  return (s_input->getPredicateClick() == true);
}

void AbstractButton::eventHandler()
{
  while(!m_stopThread)
  {
    m_clicked->wait(m_clickedLock,predicateClick);
    if(s_input->getXAbs() >= m_position.x && s_input->getXAbs() <= m_position.x + m_dimensions.x)
    {
      if(s_input->getYAbs() >= m_position.x && s_input->getYAbs() <= m_position.y + m_dimensions.y)
      {
	onClickEvent();
      }
    }
  }
}

