set(LIB_SOURCES 
    FixServer.cpp
    TestEnvironment.cpp
)

if(TARGET testAlgomon)
    message("publisher already defined")
else()
    message("Using engine includes: ${ENGINE_INCLUDES}")
    add_library(testfwk SHARED ${LIB_SOURCES})
    target_include_directories(testfwk PUBLIC 
        ${DOMAIN_INCLUDES} 
        ${FIX_INCLUDES} 
        ${ENGINE_INCLUDES} 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(testfwk LINK_PUBLIC 
        engine
        ${COMMON_LIBS}
        ${COMMON_TPP_LIBS}
        ${COMMON_FIX_LIBS}
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
        testfwk
        engine
        ${COMMON_TPP_LIBS}
        ${COMMON_FIX_LIBS}
        ${COMMON_LIBS}
    )
endif()
install(TARGETS testfwk
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
