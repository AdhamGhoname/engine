cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(Engine CXX)

#===========================================================================================
# OPTIONAL LIBRARiES
#
# The following libraries can be pulled down and added to the project by turnning the
# desired options on. Open an issue for additional default support.
# See: https://github.com/Hoshiningen/engine/issues

set(ENABLE_ASSIMP   ON CACHE BOOL "Add Open Asset Import Library (assimp) to the project" FORCE)
set(ENABLE_STB   ON CACHE BOOL "Add STB Image to the project" FORCE)
set(ENABLE_GLM   ON CACHE BOOL "Add GLM to the project" FORCE)
set(KEEP_FOLDER_STRUCTURE ON CACHE BOOL "Keep the folder structure of the source folder as is in the build project" FORCE)

#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# CMakeLists.txt file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

#===========================================================================================

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_compile_definitions(WORKING_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES_AND_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h
                                        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

file(GLOB_RECURSE SHADERS ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/*.frag
                          ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/*.vert)

add_executable(engine ${SOURCES_AND_INCLUDES} ${SHADERS})

if (KEEP_FOLDER_STRUCTURE)
    include(${CMAKE_DIR}/GroupSources.cmake)
    GroupSourcesByFolder(engine)
endif()


set_target_properties(engine PROPERTIES 
                      XCODE_GENERATE_SCHEME TRUE
                      XCODE_SCHEME_WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(engine copy_resources)

# Perform dependency linkage
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(engine PRIVATE)

include(${CMAKE_DIR}/LinkGLAD.cmake)
LinkGLAD(engine PRIVATE)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(engine PRIVATE ${OPENGL_INCLDUE_DIRS})
    target_link_libraries(engine PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

# Handle the optional libraries
if (${ENABLE_ASSIMP})
    include(${CMAKE_DIR}/LinkASSIMP.cmake)
    LinkASSIMP(engine PRIVATE)
endif()

if (${ENABLE_STB})
    include(${CMAKE_DIR}/LinkSTB.cmake)
    LinkSTB(engine PRIVATE)
endif()

if (${ENABLE_GLM})
    include(${CMAKE_DIR}/LinkGLM.cmake)
    LinkGLM(engine PRIVATE)
endif()

# Enable C++17
set_target_properties(engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

# Set project folders
set_target_properties(engine PROPERTIES FOLDER ${PROJECT_NAME})