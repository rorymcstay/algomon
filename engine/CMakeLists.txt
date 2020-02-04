
set(LIB_SOURCES 
        src/Event.cpp
        src/Publisher.cpp 
        src/Subscriber.cpp
)

if(TARGET engine)
    message("publisher already defined")
else()
    add_library(engine SHARED ${LIB_SOURCES})
    target_link_libraries(engine LINK_PUBLIC utils domain)
    target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif()
