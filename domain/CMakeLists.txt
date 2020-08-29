set(LIB_SOURCES 
        Quote.cpp 
        Event.cpp
        MarketData.cpp 
        TradeMessage.cpp
)

set(DOMAIN_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

if(TARGET domain)
    message("utils already defined")
else()
    add_library(domain SHARED ${LIB_SOURCES})
    target_link_libraries(domain LINK_PUBLIC utils) 
    target_include_directories(domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()

install(TARGETS domain
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

