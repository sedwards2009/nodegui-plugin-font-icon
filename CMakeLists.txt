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

if (UNIX AND NOT APPLE)
    # Make the output shared library's RPATH relative so that it can
    # find the other Qt and NodeGui libs even if the dir is moved.

    # NodeGui and qode are assumed to be in the same node_modules directory as nodegui-plugin-font-icon.
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "\$ORIGIN/../../../@nodegui/nodegui/miniqt/5.15.2/gcc_64/lib:\$ORIGIN/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
endif()

if (APPLE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES
        INSTALL_RPATH "@loader_path/../../../@nodegui/nodegui/miniqt/5.15.2/clang_64/lib:@loader_path/../../../@nodegui/nodegui/build/Release")
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES SKIP_BUILD_RPATH FALSE)
    set_target_properties(${PLUGIN_ADDON_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
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
