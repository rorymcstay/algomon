project(algomon C CXX)


set(LIB_SOURCES 
        include.hpp 
        logger.cpp
        cli_opts.h
)

if(TARGET utils)
    message("utils already defined")
else()
    add_library(utils STATIC ${LIB_SOURCES})
    set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(utils PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIR}
    )
    target_link_libraries( utils PRIVATE 
        ${COMMON_TPP_LIBS}
    )

endif()

install(TARGETS utils
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
