#include "AbstractMesh.h"
#include <vector>

AbstractMesh::AbstractMesh(Shader *shader, Texture* texture) :
    AbstractGraphicObject(shader), m_texture(texture), m_minVert(0), m_maxVert(0)
{
}

AbstractMesh::AbstractMesh(AbstractMesh * mesh) : AbstractMesh(mesh->m_shader,mesh->m_texture) 
{ 
}

AbstractMesh::~AbstractMesh() 
{
}

void AbstractMesh::load()
{
  //Création du vbo
  if(glIsBuffer(m_vboID) == GL_TRUE )
    glDeleteBuffers(1,&m_vboID);
  glGenBuffers(1,&m_vboID);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    unsigned long tailleVert = m_vertices.size() * sizeof(float);
    unsigned long tailleTexCoord = m_coordTex.size() * sizeof(float);
    unsigned long tailleVBO = tailleVert + tailleTexCoord;
    m_nbVertices = m_vertices.size() / 3;
    glBufferData(GL_ARRAY_BUFFER, tailleVBO, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,tailleVert,&m_vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER,tailleVert,tailleTexCoord,&m_coordTex[0]);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  // Création du vao
  if(glIsVertexArray(m_vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &m_vaoID);
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);	    
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(tailleVert));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AbstractMesh::cleanUp()
{
  m_coordTex.clear();
  AbstractGraphicObject::cleanUp();
}

void AbstractMesh::updateBoundingBox(float x, float y, float z)
{
  if(x > m_maxVert.x)
    m_maxVert.x = x;
  else if(x < m_minVert.x)
    m_minVert.x = x;
  
  if(y > m_maxVert.y)
    m_maxVert.y = y;
  else if(y < m_minVert.y)
    m_minVert.y = y;
  
  if(z > m_maxVert.z)
    m_maxVert.z = z;
  else if(z < m_minVert.z)
    m_minVert.z = z;
}