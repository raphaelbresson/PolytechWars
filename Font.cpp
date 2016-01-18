#include "Font.h"

//CREATION D'UN GESTIONNAIRE DE POLICE
Font::Font(std::string const& fn_font, unsigned int taille): Texture(fn_font), m_font(NULL), m_h(0), m_w(0)
{
  m_font = TTF_OpenFont(fn_font.c_str(), taille);
  if(!m_font)
  {
    std::cerr << "Erreur lors de l'ouverture de la police: " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

//CREATION D'UN TEXTE SANS FOND (GL_BLEND OBLIGATOIRE!)
void Font::createText(std::string const& text, SDL_Color color)
{
  SDL_Surface *message = TTF_RenderText_Blended(m_font, text.c_str(),color);
  if(!message)
  {
    std::cerr << "Erreur lors de l'extraction du texte : " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  m_h = message->h;
  m_w = message->w;
  SDL_Surface *res = inversePixels(message);
  uploadToGPU(res);
  SDL_FreeSurface(message);
  SDL_FreeSurface(res);
}

//CREATION D'UN TEXTE AVEC FOND COLORE
void Font::createTextWithBackground(std::string const& text, SDL_Color textColor,SDL_Color backgroundColor)
{
  SDL_Surface *message = TTF_RenderText_Shaded(m_font, text.c_str(),textColor,backgroundColor);
  if(!message)
  {
    std::cerr << "Erreur lors de l'extraction du texte : " << TTF_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  m_h = message->h;
  m_w = message->w;
  SDL_Surface *intermediaire = SDL_CreateRGBSurface(0, m_w, m_h, 24, 0xff0000, 0x00ff00, 0x0000ff, 0);
  SDL_BlitSurface(message, NULL, intermediaire, NULL);
  SDL_Surface *res = inversePixels(intermediaire);
  
  uploadToGPU(res);
  SDL_FreeSurface(message);
  SDL_FreeSurface(intermediaire);
  SDL_FreeSurface(res);
  printf("%s\n",TTF_GetError());
}

//DESTRUCTION D'UN GESTIONNAIRE DE POLICE
Font::~Font()
{
  //TTF_RenderText_Blended(m_font, "toto",{0,0,0});
  free(m_font);
  //TTF_CloseFont(m_font);
}
