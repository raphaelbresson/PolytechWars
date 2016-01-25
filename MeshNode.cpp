#include "MeshNode.h"
MeshNode::MeshNode(NodeType type,AbstractMesh* mesh, glm::vec3 position, glm::vec3 orientation) 
  : m_type(type),m_position(position) ,m_orientation(orientation),m_rotationMatrix(1.0f)
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
  if(m_type == NODE_BB)
    updateBoundingBox();
  
}
  
void MeshNode::setOrientation(glm::vec3 const& orientation) 
{ 
  m_orientation = orientation;
  if(m_type == NODE_BB)
    updateBoundingBox();
}
  
void MeshNode::setRotationMatrix(glm::mat4 const& rotMat)
{
  m_rotationMatrix = rotMat;
  if(m_type == NODE_BB)
    updateBoundingBox();
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

void MeshNode::updateBoundingBox()
{
  glm::vec3 min,max;
  //ajout de la translation
  min = m_mesh->getMinVert();
  max = m_mesh->getMinVert();
  //application de la rotation dynamique
  min = glm::vec3(m_rotationMatrix * glm::vec4(min,1.0f));
  max = glm::vec3(m_rotationMatrix * glm::vec4(max,1.0f));
  //application de la rotation statique
  glm::mat4 rotSta(1.0f);
  rotSta = glm::rotate(rotSta,m_orientation.y,glm::vec3(0,1,0));
  rotSta = glm::rotate(rotSta,m_orientation.z,glm::vec3(0,0,1));
  rotSta = glm::rotate(rotSta,m_orientation.x,glm::vec3(1,0,0));
  min = glm::vec3(rotSta * glm::vec4(min,1.0f));
  max = glm::vec3(rotSta * glm::vec4(max,1.0f));
  if(min.x > max.x)
  {
    m_minBB.x = max.x;
    m_maxBB.x = min.x;
  }else
  {
    m_minBB.x = max.x;
    m_maxBB.x = min.x;
  }
  if(min.y > max.y)
  {
    m_minBB.y = max.y;
    m_maxBB.y = min.y;
  }else
  {
    m_minBB.y = max.y;
    m_maxBB.y = min.y;
  }
  if(min.z > max.z)
  {
    m_minBB.z = max.z;
    m_maxBB.z = min.z;
  }else
  {
    m_minBB.z = max.z;
    m_maxBB.z = min.z;
  }
  m_minBB += m_position;
  m_maxBB += m_position;
}

float MeshNode::testCollision(MeshNode *other)
{
  if(m_type == NODE_SKYBOX || other->m_type == NODE_SKYBOX)//si l'un des deux est une skybox on ne teste pas la collision
    return 0.0f;
  if(m_type == NODE_SPHERE)//si this est une sphère
  {
    if(other->m_type == NODE_SPHERE)//si other est une sphère
      return collisionSphere(other);
    else //si other n'est pas une sphère
      return collisionSphereBoundingBox(this,other);
  }else//si this n'est pas une sphère
  {
    if(other->m_minBB == other->m_maxBB)//si other est une sphère
      return collisionSphereBoundingBox(other,this);
    else //si other n'est pas une sphère
      return collisionBoundingBox(other);
  }
  //return 0.0f;
}

float MeshNode::collisionBoundingBox(MeshNode* other)
{
  glm::vec3 diffPos1 = m_minBB - other->m_minBB;
  glm::vec3 diffPos2 = other->m_minBB - m_minBB;
  glm::vec3 diffPosMax = glm::vec3(glm::max(diffPos1.x,diffPos2.x),glm::max(diffPos1.y,diffPos2.y),glm::max(diffPos1.z,diffPos2.z));
  float distance = glm::max(diffPosMax.x,diffPosMax.y);
  distance = glm::max(distance,diffPosMax.z);
  return distance;
}

float MeshNode::collisionSphereBoundingBox(MeshNode *sphere,MeshNode* bb)
{
  glm::vec3 diffPos1 = bb->m_minBB - sphere->m_position;
  glm::vec3 diffPos2 = sphere->m_position - bb->m_maxBB;
  glm::vec3 diffPosMax = glm::vec3(glm::max(diffPos1.x,diffPos2.x),glm::max(diffPos1.y,diffPos2.y),glm::max(diffPos1.z,diffPos2.z));
  float distance = glm::max(diffPosMax.x - ((Sphere*)sphere->m_mesh)->getRadius(),diffPosMax.y - ((Sphere*)sphere->m_mesh)->getRadius());
  distance = glm::max(distance,diffPosMax.z- ((Sphere*)sphere->m_mesh)->getRadius());
  return distance;
}

float MeshNode::collisionSphere(MeshNode* other)
{
  glm::vec3 diffPos = other->m_position - m_position;
  float distance = sqrt(glm::dot(diffPos,diffPos)) - (((Sphere*)m_mesh)->getRadius() + ((Sphere*)other->m_mesh)->getRadius());
  return distance;
}