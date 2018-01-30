
#include <napi.h>
#include <out123.h>

#define NAPI_CALL(env, call) if (call != napi_ok) return NULL;
#define NAPI_ARGS(env, types)                          

namespace audio_speaker_native {

  napi_value Open(napi_env env, napi_callback_info info) {   
    size_t argc = 3;
    napi_value args[3];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

    int32_t channels;
    int32_t rate;
    int32_t format;
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &channels));
    NAPI_CALL(env, napi_get_value_int32(env, args[1], &rate));
    NAPI_CALL(env, napi_get_value_int32(env, args[2], &format));

    napi_value result;
    out123_handle *ao = out123_new();
    
    if (!ao || out123_open(ao, NULL, NULL) != OUT123_OK) {
      out123_del(ao); 
      NAPI_CALL(env, napi_get_boolean(env, false, &result));
      return result;
    } else {
      NAPI_CALL(env, napi_create_external(env, ao, NULL, NULL, &result));;
    }

    if (out123_start(ao, rate, channels, format) || !ao) {
      out123_del(ao);
      NAPI_CALL(env, napi_get_boolean(env, false, &result));
      return result;
    }
    
    return result;
  };

  napi_value Write(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, 0, 0));
    
    // Get ao handle arg
    void* tmp;
    NAPI_CALL(env, napi_get_value_external(env, args[0], &tmp));
    out123_handle *ao = reinterpret_cast<out123_handle *>(tmp);
    
    // Get buffer arg
    void* tmp_buffer;
    size_t length;
    napi_get_arraybuffer_info(env, args[1], &tmp_buffer, &length);
    unsigned char *buffer = reinterpret_cast<unsigned char *>(tmp_buffer);
    
    // TODO: async
    out123_play(ao, &buffer, length);
    out123_drain(ao);

    napi_value result;
    NAPI_CALL(env, napi_get_boolean(env, true, &result));
    
    return result;
  };

  napi_value Close(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, 0, 0));

    // Get ao handle arg
    void* tmp;
    NAPI_CALL(env, napi_get_value_external(env, args[0], &tmp));
    out123_handle *ao = reinterpret_cast<out123_handle *>(tmp);

    napi_value result;

    if (ao) {
      out123_drop(ao);
      out123_del(ao);
      napi_get_boolean(env, true, &result);
    } else {
      napi_get_boolean(env, false, &result);
    }
    
    return result;
  };

  napi_value Init(napi_env env, napi_value exports) {
    napi_value open, close, write, types, float32, float64, int8, uint8, int16,
      uint16, int32, uint32;

    NAPI_CALL(env, napi_create_function(env, nullptr, 0, Open, nullptr, &open));
    NAPI_CALL(env, napi_create_function(env, nullptr, 0, Write, nullptr, &write));
    NAPI_CALL(env, napi_create_function(env, nullptr, 0, Close, nullptr, &close));

    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_FLOAT_32, &float32));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_FLOAT_64, &float64));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_SIGNED_8, &int8));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_UNSIGNED_8, &uint8));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_SIGNED_16, &int16));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_UNSIGNED_16, &uint16));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_SIGNED_32, &int32));
    NAPI_CALL(env, napi_create_int32(env, MPG123_ENC_UNSIGNED_32, &uint32));

    NAPI_CALL(env, napi_create_object(env, &types));
    NAPI_CALL(env, napi_set_named_property(env, types, "float32", float32));
    NAPI_CALL(env, napi_set_named_property(env, types, "float64", float64));
    NAPI_CALL(env, napi_set_named_property(env, types, "int8", int8));
    NAPI_CALL(env, napi_set_named_property(env, types, "uint8", uint8));
    NAPI_CALL(env, napi_set_named_property(env, types, "int16", int16));
    NAPI_CALL(env, napi_set_named_property(env, types, "uint16", uint16));
    NAPI_CALL(env, napi_set_named_property(env, types, "int32", int32));
    NAPI_CALL(env, napi_set_named_property(env, types, "uint32", uint32));
    
    NAPI_CALL(env, napi_set_named_property(env, exports, "open", open));
    NAPI_CALL(env, napi_set_named_property(env, exports, "write", write));
    NAPI_CALL(env, napi_set_named_property(env, exports, "close", close));
    NAPI_CALL(env, napi_set_named_property(env, exports, "types", types));
    
    return exports;
  }
  
  NAPI_MODULE(audio_speaker_native, Init);

}
