
#include <napi.h>

#define CHECK_NAPI_RESULT(condition) (assert((condition) == napi_ok))

namespace audio_mpg123 {

  napi_value Create (napi_env env, napi_callback_info info) {
  
    return nullptr;
  }
  
  napi_value Open (napi_env env, napi_callback_info info) {
  
    return nullptr;
  }
  
  napi_value Close (napi_env env, napi_callback_info info) {
  
    return nullptr;
  }
  
  napi_value Write (napi_env env, napi_callback_info info) {
  
    return nullptr;
  }
 
  napi_value Flush (napi_env env, napi_callback_info info) {
  
   return  nullptr;
  }

  void Init(napi_env env, napi_value exports, napi_value module, void* priv) {
    
    CHECK_NAPI_RESULT(napi_define_properties(env, exports, 5, napi_property_descriptor[] {
      {"create", Create, 0, 0, 0, napi_default, 0},
      {"open", Open, 0, 0, 0, napi_default, 0},
      {"close", Close, 0, 0, 0, napi_default, 0},
      {"write", Write, 0, 0, 0, napi_default, 0},
      {"flush", Flush, 0, 0, 0, napi_default, 0}
    }));
  }


  NAPI_MODULE(audio_mpg123, Init)

} // namespace audio_mpg123
