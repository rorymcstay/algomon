
set(LIB_SOURCES 
        Subscriber.cpp
        Publisher.cpp
        Task.cpp
        Worker.cpp
        ThreadPool.cpp
)

if(TARGET engine)
    message("publisher already defined")
else()
    add_library(engine SHARED ${LIB_SOURCES})
    target_link_libraries(engine LINK_PUBLIC utils domain)
    target_include_directories(engine PUBLIC ${DOMAIN_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})
endif()
