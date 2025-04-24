cmake_minimum_required(VERSION 3.14)  # 3.14 suffit pour ce projet, sauf besoin spécifique
project(MedicalTriageSystem)

# Utiliser C++17 pour avoir std::filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajouter les headers
include_directories(include)

# Trouver Python
# find_package(Python3 REQUIRED)

# Ajouter les fichiers sources (uniquement les .cpp et .h, PAS le script Python)
add_executable(MedicalTriageSystem
        src/Patient.cpp
        src/TriageSystem.cpp
        src/utils.cpp
        main.cpp
)

# Lier stdc++fs pour std::filesystem
target_link_libraries(MedicalTriageSystem stdc++fs)

# Supprimer la commande qui exécute train_model.py après la construction
# add_custom_command(TARGET MedicalTriageSystem POST_BUILD
#        COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/train_model.py
#        COMMENT "Entraînement du modèle avec train_model.py"
# )
