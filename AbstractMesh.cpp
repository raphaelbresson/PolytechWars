#include "AbstractMesh.h"
#include <vector>

AbstractMesh::AbstractMesh(Shader *shader, Texture* texture) :
    AbstractGraphicObject(shader), m_texture(texture)
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