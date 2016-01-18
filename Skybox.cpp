#include "Skybox.h"

Skybox::Skybox(float taille,Shader* shad, Texture* texture) : AbstractMesh(shad,texture)
{
  m_vertices=
	      { 											
	-taille,-taille,-taille,    taille,-taille,-taille,    taille, taille,-taille,     	
	-taille,-taille,-taille,   -taille, taille,-taille,    taille, taille,-taille,     	
	taille,-taille, taille,    taille,-taille,-taille,    taille, taille,-taille,     	
	taille,-taille, taille,    taille, taille, taille,    taille, taille,-taille,   	
	-taille,-taille, taille,    taille,-taille, taille,    taille,-taille,-taille,     	
	-taille,-taille, taille,   -taille,-taille,-taille,    taille,-taille,-taille,  	
	-taille,-taille, taille,    taille,-taille, taille,    taille, taille, taille,     	
	-taille,-taille, taille,   -taille, taille, taille,    taille, taille, taille,  	
	-taille,-taille,-taille,   -taille,-taille, taille,   -taille, taille, taille,  	
	-taille,-taille,-taille,   -taille, taille,-taille,   -taille, taille, taille,  	
	-taille, taille, taille,    taille, taille, taille,    taille, taille,-taille,     	
	-taille, taille, taille,   -taille, taille,-taille,    taille, taille,-taille      	
      };
    
    
   m_coordTex =
      {						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0,     	
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0,     	
						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0,     	
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0,     	
						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0,     	
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0,     	
						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0,     	
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0,     	
						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0,     	
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0,     	
						
	0.0, 0.0,   1.0, 0.0,   1.0, 1.0, 
	0.0, 0.0,   0.0, 1.0,   1.0, 1.0
    };
}

Skybox::~Skybox()
{
}

void Skybox::draw(glm::mat4 mvp)
{
  glDepthMask(GL_FALSE);
    m_shader->begin();
      m_shader->envoyerMat4("mvp",mvp);
      glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	    m_texture->bind();
	      glDrawArrays(GL_TRIANGLES,0, 36);
	    m_texture->unbind();
	glBindBuffer(GL_ARRAY_BUFFER,0);
      glBindVertexArray(0);
    m_shader->end();
    glDepthMask(GL_TRUE);
}