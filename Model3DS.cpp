#include "Model3DS.h"

//CREATION D'UN MODELE 3DS
Model3DS::Model3DS(std::string const& file_3ds, Shader* shader) : 
  AbstractMesh(shader,NULL) ,m_fileName(file_3ds)
{
}

//DESTRUCTION D'UN MODELE 3DS
Model3DS::~Model3DS()
{
  for(unsigned int i=0;i<m_meshes.size();i++)
    delete m_meshes[i];
  m_meshes.clear();
}

// CHARGEMENT DES MESHS
void Model3DS::load()
{
  //lECTURE DU FICHIER 3DS
  Lib3dsFile *file3DS = lib3ds_file_load(m_fileName.c_str());
  if(!file3DS)
  {
    std::cerr << "Erreur lors de l'ouverture d'un fichier 3DS" << std::endl;
    exit(EXIT_FAILURE);
  }
  lib3ds_file_eval(file3DS, 0);//LECTURE DE LA PREMIERE FRAME UNQUEMENT (PAS DE GESTION DES ANIMATIONS)
  Lib3dsMesh *mesh;
  for(mesh = file3DS->meshes ; mesh != NULL; mesh = mesh->next ) // BOUCLES SUR LES MESHS QUE CONTIENT CE MODELE
  {
    Mesh3DS *mesh3ds = new Mesh3DS();
    if(!mesh3ds->extract(file3DS,mesh))
      delete mesh3ds;
    else
    {
      m_meshes.push_back(mesh3ds);
      updateBoundingBox(mesh3ds->getMaxVert().x,mesh3ds->getMaxVert().y,mesh3ds->getMaxVert().z);
      updateBoundingBox(mesh3ds->getMinVert().x,mesh3ds->getMinVert().y,mesh3ds->getMinVert().z);
    }
  }
  lib3ds_file_free(file3DS); //LIBERATION DES RESSOURCES ALLOUÉES POUR ACCEDER AU FICHIER 3DS.
}

//AFFICHAGE DU MODELE (RENDU DE TOUS LES MESHS LE COMPOSANT)
void Model3DS::draw(glm::mat4 mvp)
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  m_shader->begin();
    for(unsigned int i=0; i<m_meshes.size() ; i++)
    {
      m_shader->envoyerMat4("mvp",mvp);  
      m_meshes[i]->draw();
    }
  glBindTexture(GL_TEXTURE_2D,0);
  m_shader->end();
  glDisable(GL_CULL_FACE);
}
