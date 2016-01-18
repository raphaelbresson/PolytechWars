#include "Sphere.h" 
 
 
Sphere::Sphere(float radius, unsigned int nbLat,unsigned int nbLong,Shader *shad, Texture *tex): AbstractMesh(shad,tex),m_radius(radius),m_lats(nbLat), m_longs(nbLong), m_indexesID(0), m_vboCoordTextID(0)
{
}

Sphere::~Sphere()
{ 
}

void Sphere::load()
{
  initSphere(m_radius,m_lats,m_longs);
  //vbo vertices
  if(glIsBuffer(m_vboID) == GL_TRUE )
    glDeleteBuffers(1,&m_vboID);
  glGenBuffers(1,&m_vboID);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  //vbo coordTex
  if(glIsBuffer(m_vboCoordTextID) == GL_TRUE )
    glDeleteBuffers(1,&m_vboCoordTextID);
  glGenBuffers(1,&m_vboCoordTextID);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboCoordTextID);
    glBufferData(GL_ARRAY_BUFFER, m_coordTex.size() * sizeof(float), &m_coordTex[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  //indexes
  if(glIsBuffer(m_indexesID) == GL_TRUE )
    glDeleteBuffers(1,&m_indexesID);
  glGenBuffers(1,&m_indexesID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indexes.size() * sizeof(unsigned short) , &m_indexes[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  
  //vao
  if(glIsVertexArray(m_vaoID) == GL_TRUE)
        glDeleteVertexArrays(1, &m_vaoID);
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesID);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
          glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboCoordTextID);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::initSphere(double radius, unsigned int lats, unsigned int longs)
{
  for(unsigned int latNumber = 0; latNumber <= lats; latNumber++) 
  {
    float theta = latNumber * M_PI / lats;
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    for(unsigned int longNumber = 0; longNumber < longs; longNumber++) 
    {
      float phi = longNumber * 2 * M_PI / longs;
      float sinPhi = sin(phi);
      float cosPhi = cos(phi);
      float x = cosPhi * sinTheta;
      float y = cosTheta;
      float z = sinPhi * sinTheta;
      float u = 1.0 - ((float)longNumber / (float)longs);
      float v = 1.0 - ((float)latNumber / (float)lats);
      m_coordTex.push_back(u);
      m_coordTex.push_back(v);
      m_vertices.push_back(radius * x);
      m_vertices.push_back(radius * y);
      m_vertices.push_back(radius * z);
    }
  }
  computeIndexes(lats,longs);
}

void Sphere::computeIndexes(unsigned int lats, unsigned int longs)
{
  for (unsigned short latNumber = 0; latNumber < lats; latNumber++) 
  {
      for (unsigned short longNumber = 0; longNumber < longs; longNumber++) 
      {
        unsigned short first = (latNumber * (longs + 1)) + longNumber;
        unsigned short second = first + longs + 1;
        m_indexes.push_back(first);
        m_indexes.push_back(second);
        m_indexes.push_back(first + 1);
        m_indexes.push_back(second);
        m_indexes.push_back(second + 1);
        m_indexes.push_back(first + 1);
      }
    }
}

void Sphere::draw(glm::mat4 mvp)
{
    m_shader->begin();
      m_shader->envoyerMat4("mvp",mvp);
      glBindVertexArray(m_vaoID);
	m_texture->bind();
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesID);
	      glDrawElements(GL_TRIANGLES,m_indexes.size(), GL_UNSIGNED_SHORT ,0);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	m_texture->unbind();
      glBindVertexArray(0);
    m_shader->end();
}