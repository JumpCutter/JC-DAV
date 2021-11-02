#include "vad.h"

#include <spdlog/spdlog.h>


#ifdef NDEBUG
#define SET_LOG_LEVEL() spdlog::set_level(spdlog::level::info)
#else
#define SET_LOG_LEVEL() spdlog::set_level(spdlog::level::debug)
#endif


Napi::FunctionReference VAD::constructor;

Napi::Object VAD::Init(Napi::Env env, Napi::Object exports) {
    spdlog::set_pattern("%^[%l]%$: %v");
    SET_LOG_LEVEL();
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "VAD", {InstanceMethod("process", &VAD::Process)});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("VAD", func);

    return exports;
}

VAD::VAD(const Napi::CallbackInfo &info): Napi::ObjectWrap<VAD>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        Napi::TypeError::New(env, "Expected two arguments").ThrowAsJavaScriptException();
    }

    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Expected number for first argument").ThrowAsJavaScriptException();
    }

    if (!info[1].IsNumber()) {
        Napi::TypeError::New(env, "Expected number for second argument").ThrowAsJavaScriptException();
    }

    this->sample_rate_ = info[0].As<Napi::Number>().Int32Value();
    int level = info[1].As<Napi::Number>().Int32Value();

    this->instance_ = WebRtcVad_Create();
    WebRtcVad_Init(this->instance_);
    WebRtcVad_set_mode(this->instance_, level);
}

VAD::~VAD() {
    WebRtcVad_Free(this->instance_);
}

Napi::Value VAD::Process(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 2) {
        Napi::TypeError::New(env, "Expected two arguments").ThrowAsJavaScriptException();
    }

    if (!info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Expected buffer for first argument").ThrowAsJavaScriptException();
    }

    if (!info[1].IsNumber()) {
        Napi::TypeError::New(env, "Expected number for second argument").ThrowAsJavaScriptException();
    }

    Napi::Buffer<int16_t> audio = info[0].As<Napi::Buffer<int16_t>>();
    uint32_t length = info[1].As<Napi::Number>().Uint32Value();
    int result = WebRtcVad_Process(this->instance_, this->sample_rate_, audio.Data(), length);

    return Napi::Value::From(info.Env(), result == 1);
}
