#include "MeshNode.h"
MeshNode::MeshNode(AbstractMesh* mesh, glm::vec3 position, glm::vec3 orientation) 
  : m_position(position) ,m_orientation(orientation),m_rotationMatrix(1.0f)
{
  m_mesh = mesh;
}

MeshNode::~MeshNode() 
{
  delete m_mesh;
}

void MeshNode::setPosition(glm::vec3 const& position) 
{ 
  m_position = position; 
}
  
void MeshNode::setOrientation(glm::vec3 const& orientation) 
{ 
  m_orientation = orientation; 
}
  
void MeshNode::setRotationMatrix(glm::mat4 const& rotMat)
{
  m_rotationMatrix = rotMat;
}

void MeshNode::draw(glm::mat4 const& projection, glm::mat4 const& modelview) 
{
  
  glm::mat4 modelviewTemp(modelview);
  modelviewTemp= glm::translate(modelviewTemp, m_position);
  modelviewTemp *= m_rotationMatrix;
  modelviewTemp = glm::rotate(modelviewTemp,m_orientation.y,glm::vec3(0,1,0));
  modelviewTemp = glm::rotate(modelviewTemp,m_orientation.z,glm::vec3(0,0,1));
  modelviewTemp = glm::rotate(modelviewTemp,m_orientation.x,glm::vec3(1,0,0));
  
  m_mesh->draw(projection*modelviewTemp);
}
