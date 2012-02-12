cmake_minimum_required(VERSION 2.6)
project(BOMBERBOTS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

file(GLOB SOURCES_robokot "${PROJECT_BINARY_DIR}/src/*.cpp")

message (SRC: ${SOURCES_robokot})
message ("option")

OPTION(IS86 "x86 architecture?" OFF)
if (IS86)
  set (binname "robokot-x86")
  set (SDL_LIBRARY86 "/usr/lib32/libSDL.so")
  set (SDLIMAGE_LIBRARY86 "/usr/lib32/libSDL_image-1.2.so")
  set (SDLMAIN_LIBRARY86 "/usr/lib32/libSDLmain.a")
  set (SDLTTF_LIBRARY86 "/usr/lib32/libSDL_ttf-2.0.so")  
else (IS86)
  set (binname "robokot-x64")
endif (IS86)

set (SOURCES ${SOURCES_robokot}) 

#if (WIN32) 
#set (
#	CMAKE_C_FLAGS
#	-static-libgcc
#)
#set (
#	CMAKE_CXX_FLAGS
#	-static-libstdc++
#)

#endif (WIN32)
# REQUIRED does not work in CMake <=2.4.6 for SDL
#if (not WIN32)3
if (IS86)
  set (SDL_LIBRARY ${SDL_LIBRARY86})
  set (SDLIMAGE_LIBRARY ${SDLIMAGE_LIBRARY86} )
  set (SDLMAIN_LIBRARY ${SDLMAIN_LIBRARY86})
  set (SDLTTF_LIBRARY ${SDLTTF_LIBRARY86})
  message (SDL_LIBRARY: ${SDL_LIBRARY} )
  message (SDLIMAGE_LIBRARY: ${SDLIMAGE_LIBRARY})
  message (SDLTTF_LIBRARY: ${SDLTTF_LIBRARY})
  message (SDLMAIN_LIBRARY: ${SDLMAIN_LIBRARY}) 
else (IS86)
  Find_Package ( SDL REQUIRED )
  Find_Package ( SDL_image REQUIRED ) # if using SDL_image
  Find_Package ( SDL_ttf REQUIRED )
endif (IS86)
#endif (not WIN32)

if (IS86)
  
endif (IS86)

message (SDLDIR: $ENV{SDLDIR})
message (CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS})
message (CMAKE_C_FLAGS: ${CMAKE_CXX_FLAGS})
message (SDL_FOUND: ${SDL_FOUND})
message (SDLIMAGE_FOUND: ${SDLIMAGE_FOUND})
message (SDLTTF_FOUND: ${SDLTTF_FOUND})
message (SDLMAIN_FOUND: ${SDLMAIN_FOUND})
message (SDL_LIBRARY: ${SDL_LIBRARY} )
message (SDLMAIN_LIBRARY: ${SDLMAIN_LIBRARY} )
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
   ${binname}
   WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)
