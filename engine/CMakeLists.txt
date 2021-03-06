set(LIB_SOURCES 
        Subscriber.cpp
        Threaded.cpp
        Publisher.cpp
        PublisherController.cpp
        Task.cpp
        Worker.cpp
        ThreadPool.cpp
        SessionImpl.cpp
        StrategyEngine.cpp
        Strategy.cpp
        ConfigManager.cpp
)

set(ENGINE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
if(TARGET engine)
    message("publisher already defined")
else()
    add_library(engine SHARED ${LIB_SOURCES})

    target_link_libraries(engine PRIVATE 
        ${COMMON_TPP_LIBS}
        ${COMMON_FIX_LIBS}
        ${COMMON_LIBS}
    )
    target_include_directories(engine PUBLIC 
        ${DOMAIN_INCLUDES}
        ${FIX_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()
install(TARGETS engine 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
