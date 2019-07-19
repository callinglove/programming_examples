add_executable( connectedComponentsWithStats_demo connectedComponentsWithStats_demo.cpp )
target_link_libraries( connectedComponentsWithStats_demo ${OpenCV_LIBS} )

add_executable(findContours_demo findContours_demo.cpp)
target_link_libraries(findContours_demo ${OpenCV_LIBS})

INSTALL(TARGETS connectedComponentsWithStats_demo findContours_demo
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION libstatic)