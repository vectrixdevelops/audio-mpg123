
#include <napi.h>
#include "out123.h"

#define CHECK_NAPI_RESULT(condition) (assert((condition) == napi_ok))

namespace audio_mpg123 {

  out123_handle* unwrap_handle(napi_env env, napi_value input) {
    void *js_pointer;
    napi_get_value_external(env, input, &js_pointer);
    out123_handle *ao = (out123_handle *) js_pointer;
    return ao;
  }

  napi_value Create (napi_env env, napi_callback_info info) {
    napi_value result;

    // Create out123 handle
    out123_handle *ao = out123_new();

    // Return false on failure
    if (!ao || out123_open(ao, NULL, NULL) != OUT123_OK) {
      out123_del(ao); 
      napi_get_boolean(env, false, &result);
      return result;
    }

    // Return handle on success
    napi_create_external(env, ao, nullptr, nullptr, &result);
    return result;
  }
  
  napi_value Open (napi_env env, napi_callback_info info) {
    size_t argc = 5;
    napi_value argv[5];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    napi_value result;

    // Get handle
    out123_handle *ao = unwrap_handle(env, argv[0]);

    // Get rate, channels, and format
    int32_t rate; napi_get_value_int32(env, argv[1], &rate);
    int32_t channels; napi_get_value_int32(env, argv[2], &channels);
    int32_t format; napi_get_value_int32(env, argv[3], &format);

    // Start out123 (returning false on failure)
    if (out123_start(ao, rate, channels, format) || !ao) {
      out123_del(ao);
      napi_get_boolean(env, false, &result);
      return result;
    }
    
    // Return true for success
    napi_get_boolean(env, true, &result);
    return result;
  }
  
  napi_value Close (napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr); 

    napi_value result;

    // Get handle
    out123_handle *ao = unwrap_handle(env, argv[0]);
    
    if (ao) {
      out123_drop(ao);
      out123_del(ao);
      napi_get_boolean(env, true, &result);
    } else {
      napi_get_boolean(env, false, &result);
    }

    return result;
  }
  
  napi_value Write (napi_env env, napi_callback_info info) {
  
    return nullptr;
  }
 
  napi_value Flush (napi_env env, napi_callback_info info) {
  
   return  nullptr;
  }

  void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
    napi_status status;

    napi_value create, open, close, write, flush,
               f32, f64, s8, u8, s16, u16, s32, u32;

    napi_create_function(env, "create", Create, nullptr, &create);
    napi_create_function(env, "open", Open, nullptr, &open);
    napi_create_function(env, "close", Close, nullptr, &close);
    napi_create_function(env, "write", Write, nullptr, &write);
    napi_create_function(env, "flush", Flush, nullptr, &flush);

    napi_create_number(env, MPG123_ENC_FLOAT_32, &f32);
    napi_create_number(env, MPG123_ENC_FLOAT_64, &f64);
    napi_create_number(env, MPG123_ENC_SIGNED_8, &s8);
    napi_create_number(env, MPG123_ENC_UNSIGNED_8, &u8);
    napi_create_number(env, MPG123_ENC_SIGNED_16, &s16);
    napi_create_number(env, MPG123_ENC_UNSIGNED_16, &u16);
    napi_create_number(env, MPG123_ENC_SIGNED_32, &s32);
    napi_create_number(env, MPG123_ENC_UNSIGNED_32, &u32);

    napi_set_named_property(env, exports, "create", create);
    napi_set_named_property(env, exports, "open", open);
    napi_set_named_property(env, exports, "close", close);
    napi_set_named_property(env, exports, "write", write);
    napi_set_named_property(env, exports, "flush", flush);
    napi_set_named_property(env, exports, "F32", f32);
    napi_set_named_property(env, exports, "F64", f64);
    napi_set_named_property(env, exports, "S8", s8);
    napi_set_named_property(env, exports, "U8", u8);
    napi_set_named_property(env, exports, "S16", s16);
    napi_set_named_property(env, exports, "U16", u16);
    napi_set_named_property(env, exports, "S32", s32);
    napi_set_named_property(env, exports, "U32", u32);

  }

  NAPI_MODULE(audio_mpg123, Init);

} // namespace audio_mpg123

