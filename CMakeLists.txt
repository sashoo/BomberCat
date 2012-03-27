cmake_minimum_required(VERSION 2.6)

project(ROBOKOT)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

file(GLOB SOURCES_robokot "${PROJECT_BINARY_DIR}/src/*.cpp")

set (binname "bombercat")

set (SOURCES ${SOURCES_robokot}) 

if (MSVC)
    # 1. MSVC takes "Wall" literally, spitting a lot of useless warnings
    # 2. Recent MSVC versions always operate in C++11 mode
    set (CMAKE_CXX_FLAGS "-W4")
else()
    set (CMAKE_CXX_FLAGS "-Wall -std=c++0x")
endif()

Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED ) # if using SDL_image
Find_Package ( SDL_ttf REQUIRED )
  
if (WIN32)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)

    link_libraries(
        ${WS2_32_LIBRARY}
        ${WSOCK32_LIBRARY}
    )
endif()
 

link_libraries (
   ${SDL_LIBRARY}
   ${SDLIMAGE_LIBRARY} # if using SDL_image, obviously
   ${SDLTTF_LIBRARY}
   ${SDLMAIN_LIBRARY}
)


include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})

add_executable (
   ${binname}
   WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)
