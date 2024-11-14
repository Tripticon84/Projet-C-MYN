cmake_minimum_required(VERSION 3.29)
project(projet_C C)

set(CMAKE_C_STANDARD 11)

# Définir les chemins vers les dossiers include et lib de SDL2
set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SDL2_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SDL2_LIBRARIES SDL2)


# Définir les chemins vers les dossiers include et lib de SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SDL2_IMAGE_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SDL2_IMAGE_LIBRARIES SDL2_image)

# Trouver SDL2_image
include_directories(${SDL2_IMAGE_INCLUDE_DIRS}/SDL2_IMAGE)


# Inclure les dossiers d'en-tête
include_directories(${SDL2_INCLUDE_DIR}/SDL2)

# Ajouter les fichiers source
file(GLOB SOURCES "main.c" "src/*.c")

# Créer l'exécutable avec le nom du projet
add_executable(projet_C ${SOURCES}
        src/utils.h
        src/player.h)

# Spécifier le répertoire des bibliothèques pour la liaison
target_link_directories(projet_C PUBLIC ${SDL2_LIBRARY_DIR})

# Lier les bibliothèques
target_link_libraries(projet_C ${SDL2_IMAGE_LIBRARIES})


# Lier les bibliothèques SDL2 à l'exécutable
target_link_libraries(projet_C ${SDL2_LIBRARIES})

# Définir le répertoire de sortie de l'exécutable
set_target_properties(projet_C PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
