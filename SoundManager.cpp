#include "SoundManager.h"

SoundManager::SoundManager() : m_currentMusic(0)
{   
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2); 
  Mix_AllocateChannels(32);
}

SoundManager::~SoundManager()
{
  for(unsigned int i=0; i<m_musiques.size();i++)
    Mix_FreeMusic(m_musiques[i]);
  m_musiques.clear();
  std::map<std::string,Mix_Chunk*>::iterator it;
  for (it=m_effects.begin(); it!=m_effects.end(); ++it)
    Mix_FreeChunk(it->second);
  m_effects.clear();
  m_chanelEffects.clear();
}

void SoundManager::addMusic(std::string const& file)
{
  Mix_Music *music = NULL;
  music = Mix_LoadMUS(file.c_str());
  if(!music)
  {
    std::cerr << "Erreur lors de la lecture d'une fichier de musique: " << Mix_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  m_musiques.push_back(music);
}

 void SoundManager::addEffect(std::string const& name, std::string const& file)
 {
   static unsigned int numSong = 0;
   Mix_Chunk *son = NULL;
   son = Mix_LoadWAV(file.c_str());
   if(!son)
   {
     std::cerr << "Erreur lors de la lecture d'une fichier de son cours (effet): " << Mix_GetError() << std::endl;
    exit(EXIT_FAILURE);
   }
   Mix_VolumeChunk(son, MIX_MAX_VOLUME/2); 
   m_effects.insert(std::pair<std::string,Mix_Chunk*>(name,son));
   m_chanelEffects.insert(std::pair<std::string,int>(name,numSong));
   numSong++;
 }

bool SoundManager::isPlayingMusic() 
{ 
  return Mix_PlayingMusic() == 1; 	
}

void SoundManager::playMusic()
{
  if(m_musiques.size() == 0)
  {
    std::cerr << "Impossible de lire une musique : aucune musique chargée" << std::endl;
    exit(EXIT_FAILURE);
  }
  Mix_PlayMusic( m_musiques[m_currentMusic], 1);
}
  
void SoundManager::nextMusic()
{
  Mix_HaltMusic();
  m_currentMusic ++;
  if(m_currentMusic >= m_musiques.size())
    m_currentMusic = 0;
  playMusic();
}
  
void SoundManager::playEffect(std::string const& name,int volume)
{
  if(Mix_Playing(m_chanelEffects[name]) == 0)
  {
    
    Mix_VolumeChunk(m_effects[name], volume); 
    Mix_PlayChannel(m_chanelEffects[name], m_effects[name] , 0);
  }
}
