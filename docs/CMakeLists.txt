# add a target to generate API documentation with Doxygen
find_package(Doxygen REQUIRED)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" NO)
if(${DOXYGEN_FOUND})
    set(BUILD_DOCUMENTATION YES)
endif()

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_BINARY_DIR}/docs/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/customdoxygen.css ${CMAKE_BINARY_DIR}/docs/customdoxygen.css)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doxy-boot.js ${CMAKE_BINARY_DIR}/docs/doxy-boot.js)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/header.html ${CMAKE_BINARY_DIR}/docs/header.html)
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/footer.html ${CMAKE_BINARY_DIR}/docs/footer.html)

    add_custom_target(buildDocs
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/html DESTINATION share/doc)
endif()