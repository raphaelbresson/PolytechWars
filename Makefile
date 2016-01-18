COMPIL = g++
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lm -l3ds
FLAGS = -g -pg -Wall -std=c++11
OBJ = ApplicationControl.o SceneManager.o Input.o Texture.o Shader.o AbstractMesh.o MeshNode.o CameraFPS.o CameraFlightSimulator.o Font.o Label.o Model3DS.o Mesh3DS.o GuiFactory.o MeshFactory.o main.o Skybox.o SoundManager.o Sphere.o
EXE = StarWars

all: $(EXE)

clean:
	rm -f *.o $(EXE)
	
$(OBJ):%.o:%.cpp
	$(COMPIL) -c -o $@ $< $(FLAGS)
	
$(EXE):$(OBJ)
	$(COMPIL) -o $@ $(OBJ) $(LIBS) $(FLAGS)