set(LIB_SOURCES
    IEXProvider.cpp
)

add_library(iex_provider SHARED ${LIB_SOURCES})

TARGET_LINK_LIBRARIES(iex_provider LINK_PUBLIC 
    utils 
    iex_api
)

target_include_directories(iex_provider PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS iex_provider
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
