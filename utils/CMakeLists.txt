project(algomon C CXX)


set(LIB_SOURCES 
        include.hpp 
        logger.hpp
)


if(TARGET utils)
    message("utils already defined")
else()
    add_library(utils STATIC ${LIB_SOURCES})
    set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()

