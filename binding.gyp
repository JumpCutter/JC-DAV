{
  "targets": [
    {
      "target_name": "vad",
      "cflags!": ["-fexceptions"],
      "cflags_cc!": ["-fexceptions", "-std=c++11", "-stdlib=libc++"],
      "sources": [
        "native/webrtcvad.cc",
        "native/vad.cc",
        "native/webrtc/common_audio/signal_processing/complex_bit_reverse.c",
        "native/webrtc/common_audio/signal_processing/complex_fft.c",
        "native/webrtc/common_audio/signal_processing/cross_correlation.c",
        "native/webrtc/common_audio/signal_processing/division_operations.c",
        "native/webrtc/common_audio/signal_processing/downsample_fast.c",
        "native/webrtc/common_audio/signal_processing/energy.c",
        "native/webrtc/common_audio/signal_processing/get_scaling_square.c",
        "native/webrtc/common_audio/signal_processing/min_max_operations.c",
        "native/webrtc/common_audio/signal_processing/resample_48khz.c",
        "native/webrtc/common_audio/signal_processing/resample_by_2_internal.c",
        "native/webrtc/common_audio/signal_processing/resample_fractional.c",
        "native/webrtc/common_audio/signal_processing/spl_init.c",
        "native/webrtc/common_audio/signal_processing/spl_inl.c",
        "native/webrtc/common_audio/signal_processing/spl_sqrt.c",
        "native/webrtc/common_audio/signal_processing/vector_scaling_operations.c",
        "native/webrtc/common_audio/third_party/spl_sqrt_floor/spl_sqrt_floor.c",
        "native/webrtc/common_audio/vad/vad_core.c",
        "native/webrtc/common_audio/vad/vad_filterbank.c",
        "native/webrtc/common_audio/vad/vad_gmm.c",
        "native/webrtc/common_audio/vad/vad_sp.c",
        "native/webrtc/common_audio/vad/webrtc_vad.c",
        "native/webrtc/rtc_base/checks.cc"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "native"
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
      "conditions": [
        [
          'OS=="mac"', {
            "defines": ["WEBRTC_POSIX"]
          }
        ],
        [
          'OS=="win"', {
            "defines": ["WEBRTC_WIN"]
          }
        ],
        [
          'OS=="linux"', {
            "defines": ["WEBRTC_POSIX"]
          }
        ],
      ]
    }
  ]
}
