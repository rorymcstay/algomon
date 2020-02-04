
set(LIB_SOURCES 
        src/Event.cpp
        src/Publisher.cpp 
        src/Subscriber.cpp
)

if(TARGET publisher)
    message("publisher already defined")
else()
    add_library(publisher SHARED ${LIB_SOURCES})
    target_link_libraries(publisher LINK_PUBLIC utils domain) 
    target_include_directories(publisher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif()
