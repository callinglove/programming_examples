add_executable(one_dims_hist one_dims_hist.cpp)
target_link_libraries(one_dims_hist ${OpenCV_LIBS})

INSTALL(TARGETS one_dims_hist
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION libstatic)