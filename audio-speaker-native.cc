
#include <napi.h>
#include <out123.h>

#define NAPI_CALL(env, call) if (call != napi_ok) return NULL;

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

  struct write_data {
    out123_handle *ao;
    unsigned char *buffer;
    int length;
    napi_value callback;
  };

  void write_exec(napi_env env, void* req) {
    write_data *data = reinterpret_cast<write_data *>(req);
    out123_play(data->ao, data->buffer, data->length);
  }

  void write_finish(napi_env env, napi_status status, void* req) {
    write_data *data = reinterpret_cast<write_data *>(req);
    napi_call_function(env, nullptr, data->callback, 0, nullptr, nullptr);
  }

  napi_value Write(napi_env env, napi_callback_info info) {
    size_t argc = 3;
    napi_value args[3];
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

    printf("arraybuffer length %i\n", length);

    write_data *data =  new write_data;
    data->ao = ao;
    data->buffer = buffer;
    data->length = length;
    data->callback = args[2];

    napi_value async_resource_name;
    napi_async_work result;

    napi_create_string_utf8(env, "audio-speaker-native:write", -1, &async_resource_name);
    napi_create_async_work(env, NULL, async_resource_name, write_exec, write_finish, &data, &result);
    napi_queue_async_work(env, result);

    return nullptr;
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

    napi_property_descriptor type_properties[] = {
      {"float32", 0, 0, 0, 0, float32, napi_enumerable, 0},
      {"float64", 0, 0, 0, 0, float64, napi_enumerable, 0},
      {"int8", 0, 0, 0, 0, int8, napi_enumerable, 0},
      {"uint8", 0, 0, 0, 0, uint8, napi_enumerable, 0},
      {"int16", 0, 0, 0, 0, int16, napi_enumerable, 0},
      {"uint16", 0, 0, 0, 0, uint16, napi_enumerable, 0},
      {"int32", 0, 0, 0, 0, int32, napi_enumerable, 0},
      {"uint32", 0, 0, 0, 0, uint32, napi_enumerable, 0}
    };

    NAPI_CALL(env, napi_create_object(env, &types));
    NAPI_CALL(env, napi_define_properties(env, types, 8, type_properties));

    napi_property_descriptor export_properties[] = {
      {"open", 0, 0, 0, 0, open, napi_enumerable, 0},
      {"write", 0, 0, 0, 0, write, napi_enumerable, 0},
      {"close", 0, 0, 0, 0, close, napi_enumerable, 0},
      {"types", 0, 0, 0, 0, types, napi_enumerable, 0},
    };

    NAPI_CALL(env, napi_define_properties(env, exports, 4, export_properties));

    return exports;
  }

  NAPI_MODULE(audio_speaker_native, Init);

}
