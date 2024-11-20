cmake_minimum_required(VERSION 3.10)
project(Projet_C_v2 C)

set(CMAKE_C_STANDARD 11)

# Chemins vers les répertoires include et lib
set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/SDL2)
set(SDL2_IMAGE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/SDL2_image)
set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
set(SDL2_IMAGE_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# Ajouter les répertoires d'inclusion
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include  # Si vous avez d'autres en-têtes
)

# Récupérer tous les fichiers sources dans src/
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Lier les bibliothèques SDL2 et SDL2_image, avec -lmingw32 au début
target_link_libraries(${PROJECT_NAME}
        -lmingw32
        ${SDL2_LIB_DIR}/libSDL2main.a
        ${SDL2_LIB_DIR}/libSDL2.dll.a
        ${SDL2_IMAGE_LIB_DIR}/libSDL2_image.dll.a
        -lm
        -mwindows
)
