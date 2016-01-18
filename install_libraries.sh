#!/bin/bash
cd Bibliotheques/SDL2-2.0.3/
./configure
make -j4
make clean
cd ../SDL2_image-2.0.0
./configure
make -j4
sudo make install 
cd ../SDL2_ttf-2.0.12
./configure
make -j4
sudo make install	
cd ../SDL2_mixer-2.0.1
./configure
make -j4
sudo make install
cd ../lib3ds-1.3.0
./configure
make -j4
sudo make install
cd ..
sudo cp -r glm /usr/local/include
sudo cp -r GL3 /usr/local/include
echo "Les libraries ont bien été installées"