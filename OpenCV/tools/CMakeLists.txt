add_executable(phone_adjustment phone_adjustment.cpp)
target_link_libraries(phone_adjustment ${OpenCV_LIBS})

INSTALL(TARGETS phone_adjustment
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION libstatic)