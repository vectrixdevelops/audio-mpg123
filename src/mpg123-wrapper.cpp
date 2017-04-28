#include "mpg123-wrapper.h"
#include "pointer_wrapper.h"
#include "out123.h"
#include <nan.h>

using namespace v8;

struct write_req {
  uv_work_t req;
  out123_handle *ao;
  unsigned char *buffer;
  int length;
  int done;
  Nan::Callback *callback;
};

void Mpg123Wrapper::callback(Nan::Callback *callback, bool callbackResult) {
  v8::Local<v8::Boolean> v8Result = Boolean::New(callbackResult);

  v8::Local<v8::Value> args[] = {
    v8Result
  };

  callback->Call(1, args);
}

void Mpg123Wrapper::write_async(uv_work_t *req) {
  write_req *wreq = reinterpret_cast<write_req *>(req->data);
  wreq->done = out123_play(wreq->ao, wreq->buffer, wreq->length);
}

void Mpg123Wrapper::write_after(uv_work_t *req) {
  write_req *wreq = reinterpret_cast<write_req *>(req->data);

  v8::Local<v8::Value> args[1] = {
    Nan::New(wreq->done)
  };

  wreq->callback->Call(1, args);
  delete wreq->callback;
}

v8::Local<v8::Object> Mpg123Wrapper::create(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  Nan::EscapableHandleScope scope;

  bool returnResult = false;

  out123_handle *ao = out123_new();

  if (out123_open(ao, NULL, NULL) == OUT123_OK) {
    returnResult = true;
  }

  Mpg123Wrapper::callback(new Nan::Callback(info[0].As<Function>()), returnResult);

  info.GetReturnValue().Set(scope.Escape(WrapPointer(ao, static_cast<uint32_t>(sizeof(ao)))));
}

void Mpg123Wrapper::start(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  bool returnResult = false;

  out123_handle *ao = UnwrapPointer<out123_handle *>(info[0]);

  long rate = info[1]->Uint32Value();
  int channels = info[2]->Uint32Value();
  int encoding = info[3]->Uint32Value();

  if (ao && out123_start(ao, rate, channels, encoding) == 0) {
    returnResult = true;
  }

  Mpg123Wrapper::callback(new Nan::Callback(info[4].As<Function>()), returnResult);

  info.GetReturnValue().SetUndefined();
}

void Mpg123Wrapper::processBuffer(const Nan::FunctionCallbackInfo<v8::Value> &info) {
  out123_handle *ao = UnwrapPointer<out123_handle *>(info[0]);
  unsigned char *buffer = UnwrapPointer<unsigned char *>(info[1]);
}

void Mpg123Wrapper::processArrayBuffer(const Nan::FunctionCallbackInfo<v8::Value> &info) {

}

void Mpg123Wrapper::flush(const Nan::FunctionCallbackInfo<v8::Value> &info) {

}

void Mpg123Wrapper::stop(const Nan::FunctionCallbackInfo<v8::Value> &info) {

}

void Mpg123Wrapper::destroy(const Nan::FunctionCallbackInfo<v8::Value> &info) {

}

void Mpg123Wrapper::init() {
  Nan::HandleScope scope;

  #define CONST_INT(value) \
      Nan::ForceSet(target, Nan::New(#value).ToLocalChecked(), Nan::New(value), \
          static_cast<PropertyAttribute>(ReadOnly|DontDelete));

      CONST_INT(MPG123_ENC_FLOAT_32);
      CONST_INT(MPG123_ENC_FLOAT_64);
      CONST_INT(MPG123_ENC_SIGNED_8);
      CONST_INT(MPG123_ENC_UNSIGNED_8);
      CONST_INT(MPG123_ENC_SIGNED_16);
      CONST_INT(MPG123_ENC_UNSIGNED_16);
      CONST_INT(MPG123_ENC_SIGNED_24);
      CONST_INT(MPG123_ENC_UNSIGNED_24);
      CONST_INT(MPG123_ENC_SIGNED_32);
      CONST_INT(MPG123_ENC_UNSIGNED_32);

  Nan::SetMethod(target, "create", create);
  Nan::SetMethod(target, "start", start);
  Nan::SetMethod(target, "processBuffer", processBuffer);
  Nan::SetMethod(target, "processArrayBuffer", processArrayBuffer);
  Nan::SetMethod(target, "flush", flush);
  Nan::SetMethod(target, "stop", stop);
  Nan::SetMethod(target, "destroy", destroy);
}
