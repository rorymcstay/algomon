PROJECT(algomon C CXX)
set (CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_COMPILER /usr/bin/g++-8)
add_compile_options(-Wall -gdwarf-2 -ggdb -g3)
find_package (Threads)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


MACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD MSG)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${CMAKE_BINARY_DIR}" insource)
     GET_FILENAME_COMPONENT(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
     STRING(COMPARE EQUAL "${CMAKE_SOURCE_DIR}"
     "${PARENTDIR}" insourcesubdir)
    IF(insource OR insourcesubdir)
        MESSAGE(FATAL_ERROR "${MSG}")
    ENDIF(insource OR insourcesubdir)
ENDMACRO(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)

MACRO_ENSURE_OUT_OF_SOURCE_BUILD(
    "${CMAKE_PROJECT_NAME} requires an out of source build."
)

find_package (Boost 1.55.0 REQUIRED COMPONENTS system filesystem)
if (Boost_FOUND)
  # From the offical documentation:
  # Add include directories to the build. [...] If the SYSTEM option is given,
  # the compiler will be told the directories are meant as system include
  # directories on some platforms (signalling this setting might achieve effects
  # such as the compiler skipping warnings [...])."
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib)


add_subdirectory(utils)
add_subdirectory(domain)
add_subdirectory(engine)



add_subdirectory(app)


