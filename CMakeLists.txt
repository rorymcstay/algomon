cmake_minimum_required(VERSION 3.10)


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

PROJECT(algomon C CXX)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(
    -Wall -gdwarf-2 -ggdb -g3 # debug flags
    -DBOOST_LOG_DYN_LINK -lboost_log 
    -lboost_thread -lboost_log_setup # boost loggin reqs
    -lpthread -lboost_system 
    -lfix8 -lFIX44 # fix libs
    -ljsoncpp -DCURL_STATICLIB 
    -fPIC
)
find_package (Threads)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


find_package (Boost 1.55.0 REQUIRED COMPONENTS system filesystem log log_setup thread)
if (Boost_FOUND)
  # From the offical documentation:
  # Add include directories to the build. [...] If the SYSTEM option is given,
  # the compiler will be told the directories are meant as system include
  # directories on some platforms (signalling this setting might achieve effects
  # such as the compiler skipping warnings [...])."
  include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif()


# define common libraries
set(COMMON_TPP_LIBS 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LOG_LIBRARY} 
    ${Boost_LOG_SETUP_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
)
set(COMMON_FIX_LIBS
        tinyxml2 
        PocoFoundation
        PocoEncodings
        PocoNet
        PocoNetSSL
        fix8 
        FIX44
)
set(COMMON_LIBS
    utils
    domain
)

include_directories(/home/rory/dev/fix8-1.4.1/stocklib)
set(ENGINE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/engine)
set(UTILS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/utils)
set(DOMAIN_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/domain)
set(IEX_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/iex_provider)


include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib)

add_subdirectory(utils)
add_subdirectory(domain)
add_subdirectory(engine)
add_subdirectory(iex_api)
add_subdirectory(iex_provider)
add_subdirectory(app)
add_subdirectory(test)


