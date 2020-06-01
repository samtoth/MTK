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

    add_custom_target(buildDocs
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/docs
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

    find_package(Python3 COMPONENTS Interpreter Development)
    if(Python3_FOUND)
        set(script_in ${CMAKE_CURRENT_SOURCE_DIR}/doxyToHTML.py)
        set(script ${CMAKE_BINARY_DIR}/docs/doxyToHTML.py)

        set(README_IN ${CMAKE_SOURCE_DIR}/README.md)
        set(README ${CMAKE_BINARY_DIR}/docs/README.md)

        set(web_in ${CMAKE_CURRENT_SOURCE_DIR}/web)
        set(web ${CMAKE_BINARY_DIR}/docs/web)

        configure_file(${script_in} ${script} @ONLY)
        add_custom_command(TARGET buildDocs COMMAND ${CMAKE_COMMAND} -E copy ${README_IN} ${README} VERBATIM)
        add_custom_command(TARGET buildDocs COMMAND ${CMAKE_COMMAND} -E copy_directory ${web_in} ${web} VERBATIM )
    #    add_custom_command(TARGET buildDocs
   #             COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/docs/doxyToHTML.py "xml" "web"
  #              WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
 #               COMMENT "Building HTML files"
#                VERBATIM)
    endif()

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/html DESTINATION share/doc)
endif()