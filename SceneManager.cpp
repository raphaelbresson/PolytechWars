#include "SceneManager.h"

/*
 * CONSTRUCTEUR
 */
SceneManager::SceneManager(): m_cameras(),m_activeCamera(0), m_input(), m_guiFact(), m_meshFact(), m_soundMgr()
{
}

/*
 * DESTRUCTEUR
 */
SceneManager::~SceneManager()
{
  for(unsigned int i=0; i < m_widgets.size(); i++)
    delete m_widgets[i];
  m_widgets.clear();
  for(unsigned int i=0; i < m_meshNodes.size(); i++)
    delete m_meshNodes[i];
  m_meshNodes.clear();
  m_meshDynNodes.clear();
  for(unsigned int i = 0 ; i < m_cameras.size() ; i++)
    delete m_cameras[i];
  m_cameras.clear();
}

/*
 * AFFICHER TOUS LES OBJETS
 */
void SceneManager::drawAll()
{
  for(unsigned int i = 0 ; i < m_meshNodes.size(); i++)
    m_meshNodes[i]->draw(m_cameras[m_activeCamera]->getProjection(),m_cameras[m_activeCamera]->getModelview());
  for(unsigned int i = 0 ; i < m_widgets.size() ; i++)
    m_widgets[i]->draw(m_ortho);
}



/*
 * AJOUT D'UN MESH
 */
MeshNode* SceneManager::addMeshNode(NodeType type,AbstractMesh* mesh, glm::vec3 const& position, glm::vec3 const& orientation)
{
  MeshNode* m = new MeshNode(type,mesh,position,orientation);
  m_meshNodes.push_back(m);
  return m;
}

/*
 * AJOUT D'UN WIDGET (GUI)
 */
void SceneManager::addWidget(AbstractWidget* wid)
{
  m_widgets.push_back(wid);
}

/*
 * INITIALISATION DES MODELES 2D ET DE LA MATRICE ORTHOGONALE
 */
void SceneManager::init2D()
{
  m_ortho = glm::ortho(0.0f, 800.0f ,0.0f, 600.0f);					/* INITIALISATION DE LA MATRICE ORTHOGONALE (PROJECTION 2D) */
  SDL_Color blanc = { 255,255,255 };
  Label* vitesse = m_guiFact.createLabel(glm::vec2(2.0f,2.0f),"Font/digital.ttf");
  vitesse->setText("vitesse: 0",blanc,30.0, GL_DYNAMIC_DRAW);
  addWidget(vitesse);
  Label* position = m_guiFact.createLabel(glm::vec2(350.0f,2.0f),"Font/digital.ttf");
  position->setText("position: (0,0,0)",blanc,30.0, GL_DYNAMIC_DRAW);
  addWidget(position);
  SDL_Color rouge = { 255,0,0 };
  Label* indication = m_guiFact.createLabel(glm::vec2(100.0f,550.0f),"Font/cs.ttf");
  indication->setText("Pour quitter, echap tu presseras", rouge, 20.0, GL_STATIC_DRAW);
  addWidget(indication);
  Label* collisionTest = m_guiFact.createLabel(glm::vec2(2.0f,2.0f),"Font/cs.ttf");
  vitesse->setText("Distance : 0",blanc,30.0, GL_DYNAMIC_DRAW);
  addWidget(collisionTest);
}

/*
 * INITIALISATION DES MODELES 3D ET DES CAMERAS
 */
void SceneManager::init3D(int w, int h)
{ 
  Skybox *sky = m_meshFact.createSkybox("Images/textureCube.jpg"); 					/* CREATION D'UN CUBE (SKYBOX) */
  addMeshNode(NODE_SKYBOX,sky,glm::vec3(1.0f,0.0f,1.0f));									
  Model3DS *vaisseau = m_meshFact.create3DSModel("Models/falcon3DS/milfalcon.3ds");				/* CREATION DU VAISSEAU DE YANN SOLO */
  MeshNode *vaisseauNode = addMeshNode(NODE_BB,vaisseau,glm::vec3(0.0f,0.0f,0.0f), glm::vec3(270.0f,0.0f,0.0f));
  m_meshDynNodes.push_back(vaisseauNode); /* On ajoute le modele du vaisseau à la liste des modeles à tester pour les collisions */
  Sphere* terre = m_meshFact.createPlanet(50.0f,"Images/terre.jpg");						/* TERRE */
  addMeshNode(NODE_SPHERE,terre, glm::vec3(300.0f,50.0f,-12.0f));
  Sphere* venus = m_meshFact.createPlanet(50.0f,"Images/venus.jpg");						/* VENUS */
  addMeshNode(NODE_SPHERE,venus, glm::vec3(300.0f,-100.0f,400.0f));
  Sphere *pluton = m_meshFact.createPlanet(50.0f,"Images/pluton.jpg");						/* PLUTON */
  addMeshNode(NODE_SPHERE,pluton, glm::vec3(-100.0f,150.0f,-300.0f));
  Sphere *neptune = m_meshFact.createPlanet(50.0f,"Images/neptune.jpg");					/* NEPTUNE */
  addMeshNode(NODE_SPHERE,neptune, glm::vec3(-400.0f,100.0f,-150.0f));
  Sphere *jupiter = m_meshFact.createPlanet(50.0f,"Images/jupiter.jpg");					/* JUPITER */
  addMeshNode(NODE_SPHERE,jupiter, glm::vec3(200.0f,10.0f,-300.0f));
  glm::vec3 position(0.0f,0.0f,-15.0f), cible(0.0f,0.0f,-14.0f), up(0.0f,1.0f,0.0f);
  float proche = 0.01f, loin=1000000.0f, ratio = (float) w / (float) h, vitesseFPS = 0.1f, sensibiliteFPS = 0.1f;
  CameraFPS* cameraFPS = new CameraFPS(position, up, cible, proche, loin, ratio, vitesseFPS, sensibiliteFPS);
  cameraFPS->setActive(true);
  m_cameras.push_back(cameraFPS);
  CameraFlightSimulator* cameraFlight = new CameraFlightSimulator(position, up, cible, proche, loin, ratio, vaisseauNode);
  m_cameras.push_back(cameraFlight);
  cameraFlight->setActive(false);
}
/*
 * INITIALISATION DES MUSIQUES ET DES EFFETS SONORES
 */
void SceneManager::initSounds()
{
  m_soundMgr.addMusic("Musiques/MainTitle.ogg");
  m_soundMgr.addMusic("Musiques/Imperial.ogg");
  m_soundMgr.addMusic("Musiques/duelDarkMall.ogg");
  m_soundMgr.addMusic("Musiques/JediTheme.ogg");
  m_soundMgr.addEffect("vaisseau","Musiques/vaisseau.wav");
  m_soundMgr.addEffect("laser","Musiques/laser.wav");
  m_soundMgr.playMusic();
}
/*
 * AVANT LE RENDU
 */
void SceneManager::onPreRender()
{
  /* GUI */
  float period = 1.0 / FPS_LIMIT;
  static float vitesseCamera = 0.0f;
  static glm::vec3 positionCamera(0.0f,0.0f,-15.0f);
  SDL_Color blanc = { 255,255,255 };
  if(vitesseCamera != m_cameras[m_activeCamera]->getVitesse())
  {	
    vitesseCamera = m_cameras[m_activeCamera]->getVitesse();
    std::ostringstream streamVitesse;
    streamVitesse << "Vitesse: " << int(vitesseCamera / period);   				
    ((Label*)m_widgets[0])->setText(streamVitesse.str(),blanc,30.0, GL_DYNAMIC_DRAW);				/* ON AFFICHE LA VITESSE DE LA CAMERA (WIDGET 0) */
  }   
  if(positionCamera != m_cameras[m_activeCamera]->getPosition())
  {
    positionCamera = m_cameras[m_activeCamera]->getPosition();
    std::ostringstream streamPosition;
    streamPosition << "Position: (" << int(positionCamera.x) << "," << int(positionCamera.y) << "," << int(positionCamera.z) << ")";
    ((Label*)m_widgets[1])->setText(streamPosition.str(),blanc,30.0, GL_DYNAMIC_DRAW);				/* ON AFFICHE LA POSITION DE LA CAMERA (WIDGET 1) */
  }
  if(!m_soundMgr.isPlayingMusic())
    m_soundMgr.nextMusic();
  m_soundMgr.playEffect("vaisseau",m_cameras[m_activeCamera]->getVitesse() * 127 / 100);
  /* 3D */
  testsCollision();
}

void SceneManager::testsCollision()
{
  SDL_Color blanc = { 255,255,255 };
  float distanceMin = 2000000;
  for(unsigned int i=0;i<m_meshDynNodes.size();i++)
  {
    for(unsigned int j=0;j<m_meshNodes.size();j++)
    {
      if(m_meshDynNodes[i] != m_meshNodes[j])
      {
	float distance = m_meshDynNodes[i]->testCollision(m_meshNodes[j]);
	if(distance < distanceMin )
	  distanceMin = distance;
	//m_meshDynNodes[i]->animationCollision();
      }
    }
  }
  std::ostringstream streamDistance;
  streamDistance << "Distance: " << int(distanceMin);   				
  ((Label*)m_widgets[2])->setText(streamDistance.str(),blanc,30.0, GL_DYNAMIC_DRAW);

}
/*
 * ANIMATION DES CAMERAS
 */
void SceneManager::updateCameras()
{
  for(unsigned int i=0;i<m_cameras.size();i++)
    m_cameras[i]->onEvent(m_input);
}
/*
 * CHANGEMENT DE CAMERA
 */
void SceneManager::changeCamera()
{
  m_activeCamera++;
  if(m_activeCamera == m_cameras.size())
  {
    m_activeCamera = 0;
    m_cameras[m_cameras.size()-1]->setActive(false);
  }else
    m_cameras[m_activeCamera - 1]->setActive(false);
  m_cameras[m_activeCamera]->setActive(true);
}

/*
 * BOUCLE D'AFFICHAGE
 */
bool SceneManager::execute(SDL_Window* window, unsigned int w, unsigned int h)
{
  init3D(w,h);
  init2D();
  initSounds();
  unsigned int debut ,fin;							  	/* VARIABLES DE GESTION DU TEMPS */
  float period = 1.0 / FPS_LIMIT,fps,time;
  while(!m_input.terminer())								/* BOUCLE D'EXECUTION */
  {
    debut = SDL_GetTicks();								/* ON RELEVE LE TEMPS DE DEBUT DE BOUCLE */
    onPreRender();									/* ON MET À JOUR LES MODELES DYNAMIQUES */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					/* NETTOYAGE DE LA FENETRE */
    m_input.update();									/* MISE A JOUR DES EVENEMENTS */
    updateCameras();									/* MISE À JOUR DES CAMERAS */
    if(m_input.getKey(SDL_SCANCODE_ESCAPE))  break;					/* QUITTER EN APPUYANT SUR ESPACE */
    if(m_input.getKeyRelease(SDL_SCANCODE_V)) changeCamera();					/* CHANGER DE CAMERA EN APPUYANT SUR ESPACE */
    if(m_input.getKeyRelease(SDL_SCANCODE_SPACE)) m_soundMgr.playEffect("laser",127/2);	/* SON DU LASER SI ON APPUIE SUR ESPACE */
    drawAll();										/* AFFICHAGE DE TOUS LES MODELES DU MONDE 3D */
    SDL_GL_SwapWindow(window);								/* RAFRAICHISSEMENT DE LA FENETRE */    
    fin = SDL_GetTicks();								/* ON RELEVE LE TEMPS DE FIN DE BOUCLE */
    time = (float)(fin - debut);							/* ON CALCULE LE TEMPS D'EXECUTION DE LA BOUCLE */
    fps = 1000.0/time;									/* ON CALCULE LA FREQUENCE MAXIMALE */
    std::ostringstream streamTitle;
    streamTitle << "fps: " << int(fps);							
    SDL_SetWindowTitle(window,streamTitle.str().c_str());				/* ON AFFICHE LA FREQUENCE COMME TITRE DE LA FENETRE */
    if(time < period)
      SDL_Delay((unsigned int)(period - time));  					/* ON LIMITE LA FREQUENCE A 60 FPS */
  }
  return true;
}