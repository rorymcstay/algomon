find_package (Boost 1.55.0 REQUIRED COMPONENTS log log_setup system filesystem thread)
set(LIB_SOURCES 
    FixServer.cpp
)

if(TARGET testAlgomon)
    message("publisher already defined")
else()
    add_library(testfwk SHARED ${LIB_SOURCES})
    target_include_directories(testfwk PUBLIC 
        ${DOMAIN_INCLUDES} 
        ${FIX_INCLUDES} 
        ${ENGINE_INCLUDES} 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(testfwk LINK_PUBLIC 
        utils
        domain
        PocoFoundation
        PocoEncodings
        PocoNet
        PocoNetSSL
        fix8
        fix
        )
endif()

if(TARGET testAlgomon)
    message("testfwk already defined.")
else()
    add_executable(testAlgomon main.cpp)
    message("Engine includes: '${ENGINE_INCLUDES}'")
    target_include_directories(testAlgomon PUBLIC 
        ${DOMAIN_INCLUDES} 
        ${FIX_INCLUDES} 
        ${ENGINE_INCLUDES} 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries( testAlgomon PUBLIC
        utils
        engine
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LOG_LIBRARY} 
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_LOG_SETUP_LIBRARY} 
        ${CMAKE_THREAD_LIBS_INIT}
        fix8
        fix
    )
endif()
install(TARGETS testfwk
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
