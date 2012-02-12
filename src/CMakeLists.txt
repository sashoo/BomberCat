cmake_minimum_required(VERSION 2.6)
Project(BOMBERBOTS)

set (
    ENV{SDLDIR} 
	${PROJECT_BINARY_DIR}/SDL
)
set (
    ENV{SDLIMAGEDIR} 
	${PROJECT_BINARY_DIR}/SDL/include/SDL
)

set (
   SOURCES
   MirageApp.cpp
   CAnimation.cpp     
   CArea.cpp 
   CBomb.cpp
   CBomber.cpp
   CCamera.cpp 
   CEntity.cpp 
   CEntityCol.cpp 
   CEvent.cpp 
   CFlame.cpp
   CFPS.cpp   
   CPlayer.cpp   
   CPowerup.cpp
   CSurface.cpp 
   CTile.cpp
   IState.cpp
   STimer.cpp
   Srand.cpp
   MenuButton.cpp
   MenuManager.cpp   
   StateCredits.cpp
   StateGame.cpp
   StateIntro.cpp
   StateManager.cpp
   StateMenu.cpp
)

if (WIN32) 
set (
	CMAKE_C_FLAGS
	-static-libgcc
)
set (
	CMAKE_CXX_FLAGS
	-static-libstdc++
)

endif (WIN32)
	

# REQUIRED does not work in CMake <=2.4.6 for SDL
#if (not WIN32)3
Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image
Find_Package ( SDL_ttf REQUIRED )
#endif (not WIN32)

message (SDLDIR: $ENV{SDLDIR})
message (CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS})
message (CMAKE_C_FLAGS: ${CMAKE_CXX_FLAGS})
message (SDL_FOUND: ${SDL_FOUND})
message (SDLIMAGE_FOUND: ${SDLIMAGE_FOUND})
message (SDLTTF_FOUND: ${SDLTTF_FOUND})
message (SDL_LIBRARY: ${SDL_LIBRARY} )
message (SDL_INCLUDE_DIR: ${SDL_INCLUDE_DIR})
message (SDLIMAGE_INCLUDE_DIR: ${SDLIMAGE_INCLUDE_DIR} )
message (SDLIMAGE_LIBRARY: ${SDLIMAGE_LIBRARY})
message (SDLTTF_INCLUDE_DIR: ${SDLTTF_INCLUDE_DIR} )
message (SDLTTF_LIBRARY: ${SDLTTF_LIBRARY})
message (CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH})

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ("SDL not found!" )
endif ( NOT SDL_FOUND )

if (WIN32)
set (
    CMAKE_EXE_LINKER_FLAFS
	-static-libgcc -static-libstdc++
)

endif (WIN32)

link_libraries (
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${SDLTTF_LIBRARY}
   SDLmain # Sadly not included in SDL_LIBRARY variable
)

include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})

add_executable (
   bbots
   WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)
