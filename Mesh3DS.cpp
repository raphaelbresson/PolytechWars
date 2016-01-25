#include "Mesh3DS.h"

Mesh3DS::Mesh3DS() : AbstractMesh(NULL,NULL)
{
}

Mesh3DS::~Mesh3DS()
{
  delete m_texture;
}

bool Mesh3DS::extract(Lib3dsFile *file3DS,Lib3dsMesh *mesh)
{
  for(unsigned int i = 0 ; i < mesh->faces ; i++)
  {
    Lib3dsFace *face = &mesh->faceL[i];
    if(mesh->texels)
    {
      if(!face->material[0])
	continue;
      Lib3dsMaterial *mat = lib3ds_file_material_by_name(file3DS, face->material);
      std::string path("Images/");
      path += mat->texture1_map.name;
      if(path != "Images/" && !m_texture) // Pour simplifier les choses on choisi de ne gérer qu'une seule texture
      {
	m_texture = new Texture(path);
	m_texture->load();
      }
    }
    extractPoints(mesh,face);
  }
  load();
  return true;
}

void Mesh3DS::extractPoints(Lib3dsMesh* mesh, Lib3dsFace* face)
{
  for(unsigned j=0; j < 3 ; j++ )
  {
    m_vertices.push_back(mesh->pointL[face->points[j]].pos[0]);
    m_vertices.push_back(mesh->pointL[face->points[j]].pos[1]);
    m_vertices.push_back(mesh->pointL[face->points[j]].pos[2]);
    updateBoundingBox(mesh->pointL[face->points[j]].pos[0], mesh->pointL[face->points[j]].pos[1], mesh->pointL[face->points[j]].pos[2]);
    if(mesh->texels)
    {
      m_coordTex.push_back(mesh->texelL[face->points[j]][0]);
      m_coordTex.push_back(mesh->texelL[face->points[j]][1]);
    }
  }
}

void Mesh3DS::load()
{
  //Création du vbo
  if(glIsBuffer(m_vboID) == GL_TRUE )
    glDeleteBuffers(1,&m_vboID);
  glGenBuffers(1,&m_vboID);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    unsigned long tailleVert = m_vertices.size() * sizeof(float);
    m_nbVertices = m_vertices.size() / 3;
    unsigned long tailleTexCoord = m_coordTex.size() * sizeof(float);
    unsigned long tailleVBO = tailleVert + tailleTexCoord;
    glBufferData(GL_ARRAY_BUFFER,tailleVBO, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,tailleVert,&m_vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER,tailleVert,tailleTexCoord,&m_coordTex[0]);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  //Création du vao
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


void Mesh3DS::draw()
{
 glBindVertexArray(m_vaoID);
    if(m_texture)
      m_texture->bind();
    if(m_nbVertices > 0)
      glDrawArrays(GL_TRIANGLES,0, m_nbVertices);
   glBindVertexArray(0);
}

