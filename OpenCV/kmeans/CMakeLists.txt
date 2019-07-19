add_executable(kmeans kmeans.cpp)
target_link_libraries(kmeans ${OpenCV_LIBS})

INSTALL(TARGETS kmeans
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION libstatic)