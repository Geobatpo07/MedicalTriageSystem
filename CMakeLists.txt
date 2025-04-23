cmake_minimum_required(VERSION 3.31)
project(MedicalTriageSystem)

# Spécifier la version du C++ que vous souhaitez utiliser
set(CMAKE_CXX_STANDARD 14)

# Inclure les répertoires nécessaires
include_directories(include)

# Détecter Python dans votre environnement virtuel
find_package(Python3 REQUIRED)

# Spécifier l'exécutable Python (si nécessaire, pour un environnement virtuel spécifique)
set(PYTHON_EXECUTABLE "C:/Users/lgeov/OneDrive/Documents/Data Analytics Projects/MedicalTriageSystem/.venv/Scripts/python.exe")

# Ajouter l'exécutable de votre application C++
add_executable(MedicalTriageSystem
        include/Patient.h
        include/TriageSystem.h
        include/utils.h
        scripts/train_model.py
        src/Patient.cpp
        src/TriageSystem.cpp
        src/utils.cpp
        main.cpp
)

# Commande pour exécuter train_model.py après la construction de l'exécutable
add_custom_command(TARGET MedicalTriageSystem POST_BUILD
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/train_model.py
        COMMENT "Entraînement du modèle avec train_model.py"
)
