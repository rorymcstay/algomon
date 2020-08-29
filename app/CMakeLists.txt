
find_package (Boost 1.55.0 REQUIRED COMPONENTS log log_setup system filesystem thread)

add_executable(algomon main.cpp)
TARGET_LINK_LIBRARIES(algomon PUBLIC 
    utils 
    engine 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LOG_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_LOG_SETUP_LIBRARY} 
    ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(iex iex.cpp)
target_link_libraries(iex PUBLIC         
    utils
    iex_api
    iex_provider
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LOG_LIBRARY} 
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_LOG_SETUP_LIBRARY} 
    ${CMAKE_THREAD_LIBS_INIT}
)


install(TARGETS algomon iex
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
