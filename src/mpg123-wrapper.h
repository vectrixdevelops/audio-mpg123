#include <nan.h>

class Mpg123Wrapper : public Nan::ObjectWrap {
public:
  static void init();
  static v8::Local<v8::Object> create(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void start(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void processBuffer(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void processArrayBuffer(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void flush(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void stop(const Nan::FunctionCallbackInfo<v8::Value> &info);
  static void destroy(const Nan::FunctionCallbackInfo<v8::Value> &info);
private:
  static void callback(Nan::Callback *callback, bool callbackResult);
  static void write_async(uv_work_t *req);
  static void write_after(uv_work_t *req);
};
