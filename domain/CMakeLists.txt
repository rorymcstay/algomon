set(LIB_SOURCES 
        src/Quote.cpp 
        src/Data.cpp
        src/MarketData.cpp 
        src/TradeMessage.cpp
)

if(TARGET domain)
    message("utils already defined")
else()
    add_library(domain SHARED ${LIB_SOURCES})
    target_link_libraries(domain LINK_PUBLIC utils) 
    target_include_directories(domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif()

