set(LIB_SOURCES 
    Myfix_classes.cpp
    Myfix_traits.cpp
    Myfix_types.cpp
)

set(FIX_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
if(TARGET fix)
    message("fix already defined")
else()
    add_library(fix SHARED ${LIB_SOURCES})
    target_link_libraries(fix LINK_PUBLIC fix8)
    target_include_directories(fix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
install(TARGETS fix
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
