#include "Shader.h"

Shader::Shader(std::string const & vertexShader, std::string const & fragmentShader): 
  m_programID(0), m_vertID(0), m_fragID(0), m_vert(vertexShader), m_frag(fragmentShader)
{
}

Shader::Shader(Shader const & shader): 
  m_programID(0), m_vertID(0), m_fragID(0)
{
  m_vert = shader.m_vert;
  m_frag = shader.m_frag;
}

Shader::~Shader()
{
  libererRessources();
}

void Shader::loadSimple()
{
  libererRessources();
  
  m_programID = createProgram();
  m_vertID = compileShader(m_vert,GL_VERTEX_SHADER);
  m_fragID = compileShader(m_frag,GL_FRAGMENT_SHADER);
  glAttachShader(m_programID, m_vertID);
  glAttachShader(m_programID, m_fragID);
  glBindAttribLocation(m_programID, 0, "in_Vertex");
  linkProgram();
}

void Shader::load()
{
  libererRessources();
  m_programID = createProgram();
  m_vertID = compileShader(m_vert,GL_VERTEX_SHADER);
  m_fragID = compileShader(m_frag,GL_FRAGMENT_SHADER);
  glAttachShader(m_programID, m_vertID);
  glAttachShader(m_programID, m_fragID);
  glBindAttribLocation(m_programID, 0, "in_Vertex");
  glBindAttribLocation(m_programID, 1, "in_TexCoord");
  linkProgram();
}

GLuint Shader::createProgram()
{
  GLuint programID = glCreateProgram();
  if(programID == 0)
  {
    std::cerr << "Shader: Erreur lors de la creation du programme" << glGetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  return programID;
}

GLuint Shader::compileShader(std::string fichierSource, GLenum type)
{
  GLuint shaderID = glCreateShader(type);
  if(shaderID == 0)
  {
    if(type == GL_VERTEX_SHADER)
      std::cerr << "Shader: Erreur lors de la creation du shader de type vertex shader: " << fichierSource << ": " << glGetError() << std::endl;
    else
      std::cerr << "Shader: Erreur lors de la creation du shader de type fragment shader: " << fichierSource << ": " << glGetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream file;
  file.open(fichierSource.c_str() ,std::ios::in);
  if(!file.is_open())
  {
    std::cerr << "Shader: Erreur lors de l'ouverture du fichier source" << fichierSource << std::endl;
    exit(EXIT_FAILURE);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  char *codeSource = strdup(buffer.str().c_str());
  glShaderSource(shaderID, 1, (const GLchar**) &codeSource, NULL);
  glCompileShader(shaderID);
  free(codeSource);
  GLint erreurCompilation(0);
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &erreurCompilation);
  if(erreurCompilation != GL_TRUE)
  {
    GLint errorSize;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorSize);
    char *erreur = new char[errorSize];
    glGetShaderInfoLog(shaderID, errorSize, &errorSize, erreur);
    std::cerr << "Shader: Erreur lors de la compilation d'un shader:" << erreur << std::endl;
    delete erreur;
    exit(EXIT_FAILURE);
  }
  return shaderID;
}

void Shader::linkProgram()
{
  glLinkProgram(m_programID);
  GLint linkError;
  glGetProgramiv(m_programID, GL_LINK_STATUS, &linkError);
  if(linkError != GL_TRUE)
  {
    GLint errorSize;
    glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);
    char *erreur = new char[errorSize];
    glGetShaderInfoLog(m_programID, errorSize, &errorSize, erreur);
    std::cerr <<"Shader: Erreur lors de l'édition de liens d'un programme shader:" << erreur << std::endl;
    delete erreur;
    exit(EXIT_FAILURE);
  }
}

void Shader::libererRessources()
{
  if(glIsShader(m_vertID) == GL_TRUE)
    glDeleteShader(m_vertID);
  if(glIsShader(m_fragID) == GL_TRUE)
    glDeleteShader(m_fragID);
  if(glIsProgram(m_programID) == GL_TRUE)
    glDeleteProgram(m_programID);
  m_vertID = 0;
  m_fragID = 0;
  m_programID = 0;
}

void Shader::envoyerMat4(std::string const& nom, glm::mat4 const& matrice)
{
  int localisation = glGetUniformLocation(m_programID, nom.c_str());
  glUniformMatrix4fv(localisation, 1, GL_FALSE, glm::value_ptr(matrice));
}