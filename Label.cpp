#include "Label.h" 

Label::Label(std::string const&  font, unsigned int tailleFont, Shader* shad, glm::vec2 const& position):
	 AbstractWidget(shad,position),m_font(font,tailleFont), m_tailleFont(tailleFont)
{
}
  
Label::~Label()
{
}

void Label::load(GLenum drawingMethod)
{
    if(glIsBuffer(m_vboID) == GL_TRUE)
      glDeleteBuffers(1,&m_vboID);
    glGenBuffers(1,&m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER,m_vboID);
      glBufferData(GL_ARRAY_BUFFER,m_vertices.size() * 2 * sizeof(float), 0, drawingMethod);
      glBufferSubData(GL_ARRAY_BUFFER,                  0              ,m_vertices.size() * sizeof(float), &m_vertices[0]);
      glBufferSubData(GL_ARRAY_BUFFER,m_vertices.size() * sizeof(float),m_coordTex.size() * sizeof(float), &m_coordTex[0]);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
      glDeleteVertexArrays(1,&m_vaoID);
    glGenVertexArrays(1,&m_vaoID);
    glBindVertexArray(m_vaoID);
      glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_vertices.size() * sizeof(float)));
	glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
  
void Label::draw(glm::mat4 ortho)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glm::mat4 mvp = glm::translate(ortho,glm::vec3(m_position,0.0f));
    m_shader->begin();
      m_shader->envoyerMat4("mvp",mvp);
      glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	  m_font.bind();
	    glDrawArrays(GL_TRIANGLES,0, 6);
	  m_font.unbind();
	glBindBuffer(GL_ARRAY_BUFFER,0);
      glBindVertexArray(0);
    m_shader->end();
  glDisable(GL_BLEND);
}

void Label::cleanUp()
{
  m_coordTex.clear();
  AbstractWidget::cleanUp();
}
  
void Label::setText(std::string const& text,SDL_Color const& color,float taille, GLenum drawingMethod)
{
    m_font.createText(text,color);
    float ratio = float(m_font.getHeight()) / float(m_font.getWidth());
    m_vertices = { 0.0,0.0,      taille/ratio, 0.0,      taille/ratio, taille,
		   0.0,0.0,      0.0, taille,      taille/ratio, taille };
    m_coordTex = { 0.0,0.0,      1.0, 0.0,      1.0, 1.0,
		   0.0,0.0,      0.0, 1.0,      1.0, 1.0 };
    load(drawingMethod);
}
