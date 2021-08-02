cmake_minimum_required(VERSION 3.1)
# -------------- Plugin Config ---------------
execute_process(COMMAND node -p "require('@nodegui/nodegui/plugin').CMAKE_HELPER_FILE"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODEGUI_PLUGIN_CMAKE_HELPER
)
string(REPLACE "\n" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
string(REPLACE "\"" "" NODEGUI_PLUGIN_CMAKE_HELPER ${NODEGUI_PLUGIN_CMAKE_HELPER})
include("${NODEGUI_PLUGIN_CMAKE_HELPER}")

# -------------- User Config ---------------
set(PLUGIN_ADDON_NAME "nodegui_plugin_font_icon")

project(${PLUGIN_ADDON_NAME})

add_library(${PLUGIN_ADDON_NAME} SHARED
    "${CMAKE_JS_SRC}"
    "${PROJECT_SOURCE_DIR}/src/cpp/main.cpp"
    "${PROJECT_SOURCE_DIR}/src/cpp/FontIcon.cpp"
)

AddPluginConfig(${PLUGIN_ADDON_NAME})

if (UNIX)
    # Make the output shared library's RPATH relative so that it can
    # find the other Qt and NodeGui libs even if the dir is moved.

    get_filename_component(NODEGUI_LIBRARY_DIR "${NODEGUI_LIBRARY}" DIRECTORY)
    file(RELATIVE_PATH NODEGUI_LIBRARY_REL_PATH "${CMAKE_BINARY_DIR}/Release" "${NODEGUI_LIBRARY_DIR}")

    file(RELATIVE_PATH QT_LIBRARY_REL_PATH "${CMAKE_BINARY_DIR}/Release" "${QT_CMAKE_HOME_DIR}/../..")

    set_target_properties(${PLUGIN_ADDON_NAME}
        PROPERTIES BUILD_RPATH "\$ORIGIN/${NODEGUI_LIBRARY_REL_PATH}:\$ORIGIN/${QT_LIBRARY_REL_PATH}")
endif()

target_include_directories(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_INC}"
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/src/cpp"
)
target_link_libraries(${PLUGIN_ADDON_NAME} PRIVATE
    "${CMAKE_JS_LIB}"
     Qt5::Gui
)
