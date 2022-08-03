**Vous devez installer la librairie oscpack (Necessaire pour la communication avec max)**

    sudo apt-get install liboscpack-dev

**Vous devez ajouter votre utilisateur au groupe dialout pour avoir acces au capteur :**

    sudo usermod -a -G dialout $USER


**Necessite GCC, Make et CMake**

**Pour compiler, executer les commandes suivantes:** 

    cmake CMakeLists.txt
    make

