set(LIB_SOURCES 
        Subscriber.cpp
        Threaded.cpp
        Publisher.cpp
        PublisherController.cpp
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
install(TARGETS engine 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
