#include "GuiFactory.h"


GuiFactory::GuiFactory() : m_shaderTexture(NULL), m_shaderColor(NULL)
{ 
//   m_shaderTexture = new Shader(VERTEX_SHADER_GUI, FRAGMENT_SHADER_GUI_TEXTURE);
//   m_shaderTexture->load();
//   m_shaderColor = new Shader(VERTEX_SHADER_GUI, FRAGMENT_SHADER_GUI_COLOR);
//   m_shaderColor->load();
}
GuiFactory::~GuiFactory()
{
  if(m_shaderTexture)
    delete m_shaderTexture;
  if(m_shaderColor)
    delete m_shaderColor;
}
  
Label *GuiFactory::createLabel(glm::vec2 const& position,std::string const& font)
{
  if(!m_shaderTexture)
  {
    m_shaderTexture = new Shader(VERTEX_SHADER_GUI, FRAGMENT_SHADER_GUI_TEXTURE);
    m_shaderTexture->load();
  }
  Label *label = new Label(font,DEFAULT_FONT_SIZE,m_shaderTexture,position);
  return label;
}
