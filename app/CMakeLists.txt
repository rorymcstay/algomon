ADD_EXECUTABLE(algomon main.cpp)

TARGET_LINK_LIBRARIES(algomon LINK_PUBLIC domain utils publisher)
