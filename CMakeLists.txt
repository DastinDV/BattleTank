cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
project(BattleTank VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" FORCE)
endif()

# Export compile commands for completion engines (optional)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set option to control setting the resource path variable
#option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

#if(NOT USE_INSTALL_RESOURCE_PATH)
  #set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/Assets/")
#else()
  #set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/content/")
#endif()

# Generate config.h
#configure_file(include/config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.2 COMPONENTS system window graphics audio REQUIRED)

# Compile executable
add_executable(BattleTank TankBattle/Main.cpp TankBattle/IMovable.cpp TankBattle/BaseUnit.cpp TankBattle/Bullet.cpp TankBattle/PlayerTank.cpp TankBattle/AITank.cpp TankBattle/GameWorld.cpp TankBattle/Map.cpp)

# Set include directory search paths
target_include_directories(BattleTank 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/TankBattle"
  )

# Set executable RPATH
set_target_properties(BattleTank
  PROPERTIES
      INSTALL_RPATH
        "${CMAKE_INSTALL_PREFIX}/lib"
  )

# Link executable to required SFML modules
target_link_libraries(BattleTank sfml-graphics sfml-audio)

# Set executable install location
install(TARGETS BattleTank DESTINATION bin)

# Set install location for resources
install(DIRECTORY content
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
)
