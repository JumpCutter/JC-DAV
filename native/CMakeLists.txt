# Generate compile_commands.json to make it easier to work with clang based tools
link_compile_commands()
set(LIB_NAME vad)

set(SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/native/webrtcvad.cc"
    "${CMAKE_SOURCE_DIR}/native/vad.cc"
    "${CMAKE_SOURCE_DIR}/native/webrtc/rtc_base/checks.cc"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/complex_bit_reverse.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/complex_fft.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/cross_correlation.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/division_operations.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/downsample_fast.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/energy.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/get_scaling_square.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/min_max_operations.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/resample_48khz.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/resample_by_2_internal.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/resample_fractional.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/spl_init.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/spl_inl.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/spl_sqrt.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/signal_processing/vector_scaling_operations.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/third_party/spl_sqrt_floor/spl_sqrt_floor.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/vad/vad_core.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/vad/vad_filterbank.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/vad/vad_gmm.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/vad/vad_sp.c"
    "${CMAKE_SOURCE_DIR}/native/webrtc/common_audio/vad/webrtc_vad.c"
)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

target_link_libraries(
    ${LIB_NAME}
    PRIVATE project_options
            project_warnings
            CONAN_PKG::spdlog
            CONAN_PKG::ms-gsl
            ${CMAKE_JS_LIB}
)

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

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
            ${CMAKE_SOURCE_DIR}/native
)

target_compile_definitions(
    ${LIB_NAME}
    PRIVATE NAPI_VERSION=8
            # $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS> # To silence MSVC about *_s functions
            $<IF:$<C_COMPILER_ID:MSVC>,WEBRTC_WIN,WEBRTC_POSIX> # To silence MSVC about *_s functions
)
