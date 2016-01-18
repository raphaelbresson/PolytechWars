#ifndef INCLUDE_GL_AND_GLM_H
#define INCLUDE_GL_AND_GLM_H
/**
 * \file Include_GL_and_GLM.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Inclusion des header de OpenGL 3 et GLM
 */


/**
 * \def GL3_PROTOTYPES
 * \brief Obligatoire sur Linux et Mac OS (forcer à 1)
 */
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif