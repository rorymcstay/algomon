ADD_EXECUTABLE(algomon main.cpp)


find_package (Boost 1.55.0 REQUIRED COMPONENTS log log_setup system filesystem thread)

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
