#include "MeshFactory.h"

MeshFactory::MeshFactory() : m_shaderTexture2D(NULL)
{
}


MeshFactory::~MeshFactory()
{
  if(m_shaderTexture2D)
    delete m_shaderTexture2D;
  std::map<std::string,Texture*>::iterator it;
  for (it=m_textures.begin(); it!=m_textures.end(); ++it)
    delete it->second;
  m_textures.clear();
}

Model3DS* MeshFactory::create3DSModel(std::string const& modelName)
{
  if(!m_shaderTexture2D)
  {
    m_shaderTexture2D = new Shader(VERTEX_SHADER_3D, FRAGMENT_SHADER_3D_TEXTURE_2D);
    m_shaderTexture2D->load();
  }
  Model3DS *model = new Model3DS(modelName,m_shaderTexture2D);
  model->load();
  return model;
}

Skybox* MeshFactory::createSkybox(std::string const& image)
{
  if(!m_shaderTexture2D)
  {
    m_shaderTexture2D = new Shader(VERTEX_SHADER_3D, FRAGMENT_SHADER_3D_TEXTURE_2D);
    m_shaderTexture2D->load();
  }
  Skybox *sky=new Skybox(50000.0f,m_shaderTexture2D,getTexture(image));
  sky->load();
  return sky;
}

Sphere* MeshFactory::createPlanet(float radius,std::string const& texture)
{
  if(!m_shaderTexture2D)
  {
    m_shaderTexture2D = new Shader(VERTEX_SHADER_3D, FRAGMENT_SHADER_3D_TEXTURE_2D);
    m_shaderTexture2D->load();
  }
  Sphere* s = new Sphere(radius,radius*2, radius,m_shaderTexture2D,getTexture(texture));
  s->load();
  return s;
}

Texture *MeshFactory::getTexture(std::string const& name)
{
  if(m_textures.find(name) != m_textures.end())//si la texture existe déja on la retourne directement
    return m_textures[name];
  Texture *texture = new Texture(name);
  texture->load();
  m_textures.insert(std::pair<std::string,Texture*>(name,texture));
  return texture;
}