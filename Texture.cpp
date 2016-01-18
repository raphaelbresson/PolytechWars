#include "Texture.h"

Texture::Texture(): m_id(0), m_fn("")
{
}

Texture::Texture(std::string const & fn): m_id(0), m_fn(fn)
{ 
}

Texture::Texture(Texture & tex) : m_id(0), m_fn(tex.m_fn)
{ 
}

void Texture::load()
{
    if(m_fn == "")
      return;
    SDL_Surface *img = readPixels();
    uploadToGPU(img);
    SDL_FreeSurface(img);
}

void Texture::loadEmpty(unsigned int width, unsigned int height, GLenum format, GLenum formatInterne)
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
  if(glIsTexture(m_id) == GL_TRUE)
    glDeleteTextures(1,&m_id);
  bind();
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, width, height, 0, format, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  unbind();
}

Texture & Texture::operator = (Texture & tex)
{
  if(glIsTexture(m_id) == GL_TRUE)
    glDeleteTextures(1,&m_id);
  m_id = 0;
  m_fn = tex.m_fn;
  return *this;
}

void Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D,m_id);
}

void Texture::unbind()
{
  glBindTexture(GL_TEXTURE_2D,0);
}

Texture::~Texture()
{
  if(glIsTexture(m_id) == GL_TRUE)
    glDeleteTextures(1,&m_id);
}

SDL_Surface * Texture::readPixels()
{
  SDL_Surface *sdl_img = NULL, *img = NULL;
  sdl_img = IMG_Load(m_fn.c_str());
  if(!sdl_img)
  {
    std::cerr << "Texture: Erreur d'importation de l'image : " << m_fn  <<  ": " << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  img = inversePixels(sdl_img);
  SDL_FreeSurface(sdl_img);
  return img;
}

SDL_Surface* Texture::inversePixels(SDL_Surface *imageSource)
{
  SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource->w, imageSource->h, imageSource->format->BitsPerPixel, imageSource->format->Rmask, imageSource->format->Gmask, imageSource->format->Bmask, imageSource->format->Amask);
  unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
  unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;
  for(int i = 0; i < imageSource->h; i++)
  {
    for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
      pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];
  }
  return imageInversee;
}

void Texture::uploadToGPU(SDL_Surface* image)
{
  GLenum formatInterne(0);
  GLenum format(0);
  detectFormat(image,formatInterne,format);
  if(glIsTexture(m_id) == GL_TRUE)
    glDeleteTextures(1, &m_id);
  glGenTextures(1,&m_id);
  bind();
    glTexImage2D(GL_TEXTURE_2D, 0, formatInterne, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  unbind();
}

void Texture::detectFormat(SDL_Surface* image,GLenum & formatInterne, GLenum & format)
{
  if(image->format->BytesPerPixel == 3)
  {
    formatInterne = GL_RGB;
    if(image->format->Rmask == 0xff)
      format = GL_RGB;
    else
      format = GL_BGR;
  }
  else if(image->format->BytesPerPixel == 4)
  {    
    formatInterne = GL_RGBA;
    if(image->format->Rmask == 0xff)
      format = GL_RGBA;
    else
      format = GL_BGRA;
  }
  else
  {
    std::cerr << "Texture: Format non reconnu" << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::string Texture::getName()
{
  return m_fn;
}
//--------------------------------------------------------------------------------------------------------------------------------------

void Texture::loadCubemap(std::vector<std::string> faces)
{
    if(glIsTexture(m_id)==GL_TRUE)
      glDeleteTextures(1,&m_id);
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    for(unsigned int i = 0; i < faces.size(); i++)
    {
      SDL_Surface *img = readPixels(faces[i]);
      GLenum formatInterne, format;
      printf("tamere\n");
      detectFormat(img,formatInterne,format);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, formatInterne, img->w, img->h, 0, format, GL_UNSIGNED_BYTE, img);
      SDL_FreeSurface(img);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

SDL_Surface* Texture::readPixels(std::string image)
{
  printf("%s\n",image.c_str());
  SDL_Surface *sdl_img = NULL, *img = NULL;
  sdl_img = IMG_Load(image.c_str());
  if(!sdl_img)
  {
    std::cerr << "Texture: Erreur d'importation de l'image : " << m_fn  <<  ": " << IMG_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  img = inversePixels(sdl_img);
  SDL_FreeSurface(sdl_img);
  return img;
}