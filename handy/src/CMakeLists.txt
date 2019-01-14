IF(OPENCV_FOUND)
  aux_source_directory(cvUtils cvUtils_SRC)
  SET(CVUTILSLIBS ${OpenCV_LIBS})

  IF(NOT FREETYPE_FOUND)
	message(WARNING "not found freetype, so not compile OpencvText")
    list(REMOVE_ITEM cvUtils_SRC "OpencvText.cpp")
  ELSE()
    ADD_DEFINITIONS(-DENABLE_CHINESE_TEXT_SUPPORT)
    SET(CVUTILSLIBS ${CVUTILSLIBS} ${FREETYPE_LIBRARIES})  
  ENDIF()
  
  # add_library( cvUtils SHARED ${cvUtils_SRC})
  add_library( cvUtils STATIC  ${cvUtils_SRC})
  target_link_libraries( cvUtils  ${CVUTILSLIBS})
ELSE()
  message(WARNING "not found opencv, so not compile cvUtils")
ENDIF()

aux_source_directory(parameterHandler parameterhandler_SRC)
add_library( parameter STATIC ${parameterhandler_SRC})


