#include <napi.h>

Napi::ThreadSafeFunction threadSafeCallback;
bool callbackWasSet = false;

Napi::String SetCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    throw Napi::Error::New(env, "Missing argument");
  }

  if (!info[0].IsFunction()) {
    throw Napi::TypeError::New(env, "Wrong argument type");
  }

  Napi::Function napiFunction = info[0].As<Napi::Function>();

  threadSafeCallback =
      Napi::ThreadSafeFunction::New(env, napiFunction, "Callback", 0, 1);

  callbackWasSet = true;

  return Napi::String::New(env, "Done");
}

Napi::String TriggerCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (!callbackWasSet) {
    throw Napi::Error::New(env, "Callback was never set");
  }

  Napi::String napiMessageString = info[0].As<Napi::String>();

  auto callback = [napiMessageString](Napi::Env env,
                                      Napi::Function jsCallback) {
    jsCallback.Call({napiMessageString});
  };

  threadSafeCallback.NonBlockingCall(callback);
  threadSafeCallback.Release();
  return Napi::String::New(env, "Done");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "SetCallback"),
              Napi::Function::New(env, SetCallback));

  exports.Set(Napi::String::New(env, "TriggerCallback"),
              Napi::Function::New(env, TriggerCallback));

  return exports;
}

NODE_API_MODULE(addon, Init)
