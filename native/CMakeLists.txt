# Generate compile_commands.json to make it easier to work with clang based tools
link_compile_commands()
set(LIB_NAME VAD)

file(
    GLOB
    SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/native/webrtc/**/*"
    "*.c*"
)

file(
    GLOB
    HEADER_FILES
    "${CMAKE_SOURCE_DIR}/native/webrtc/**/*"
    "*.h"
)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${CMAKE_JS_SRC})

target_link_libraries(
    ${LIB_NAME}
    PRIVATE project_options
            project_warnings
            CONAN_PKG::spdlog
            CONAN_PKG::ms-gsl
            ${CMAKE_JS_LIB}
)

set_target_properties(${project_name} PROPERTIES PREFIX "" SUFFIX ".node")

execute_process(
    COMMAND node -p "require('node-addon-api').include"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODE_ADDON_API_DIR
)

string(
    REPLACE "\n"
            ""
            NODE_ADDON_API_DIR
            ${NODE_ADDON_API_DIR}
)
string(
    REPLACE "\""
            ""
            NODE_ADDON_API_DIR
            ${NODE_ADDON_API_DIR}
)
target_include_directories(
    ${LIB_NAME} SYSTEM
    PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG}
            ${CONAN_INCLUDE_DIRS_MS-GSL}
            ${NODE_ADDON_API_DIR}
            ${CMAKE_JS_INC}
            "${CMAKE_SOURCE_DIR}/native"
)

target_compile_definitions(
    ${LIB_NAME}
    PRIVATE NAPI_VERSION=3
            # $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS> # To silence MSVC about *_s functions
            $<$<CONFIG:Debug>:DEBUG>
            $<IF:$<C_COMPILER_ID:MSVC>,WEBRTC_WIN,WEBRTC_POSIX> # To silence MSVC about *_s functions
)
