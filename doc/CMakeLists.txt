# Copyright 2013 Jan de Cuveland <cmail@cuveland.de>

include(FindDoxygen)

if(DOXYGEN_FOUND)

  set(DOXYGEN_LANGUAGE "English" CACHE STRING "Language used by doxygen")
  mark_as_advanced(DOXYGEN_LANGUAGE)

  set(DOXYGEN_SOURCE_DIRS ${CMAKE_SOURCE_DIR})
  set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

  string(REGEX REPLACE ";" " " DOXYGEN_INPUT "${DOXYGEN_SOURCE_DIRS}")
  configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  set(HTML_TARGET ${DOXYGEN_OUTPUT_DIR}/html/index.html)
  add_custom_target(doc
                    COMMAND ${DOXYGEN} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

else()

    message(STATUS "WARNING: Failed to find Doxygen - won't build documentation")

endif()
