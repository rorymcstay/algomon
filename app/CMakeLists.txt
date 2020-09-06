add_executable(algomon main.cpp)
TARGET_LINK_LIBRARIES(algomon PUBLIC 
    engine 
    ${COMMON_TPP_LIBS}
    ${COMMON_LIBS}
    ${COMMON_FIX_LIBS}
)



#add_executable(iex iex.cpp)
#target_link_libraries(iex PUBLIC         
#    utils
#    iex_api
#    iex_provider
#    ${COMMON_TPP_LIBS}
#)


install(TARGETS algomon # iex
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
