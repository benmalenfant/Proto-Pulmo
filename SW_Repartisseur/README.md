vous devez installer la librairie oscpack (Necessaire pour la communication avec max)

sudo apt-get install liboscpack-dev


Doit ajouter l'utilisateur au groupe dialout pour avoir acces au capteur : 

sudo usermod -a -G dialout $USER


Necessite Gcc make et CMake

Pour build : 

cmake CMakeLists.txt

suivi de

make

