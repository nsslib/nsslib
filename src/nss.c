#include "./nss.h"
#include "./impl.h"

void
registerMethods(napi_env env, napi_value exports, 
                napi_value (*nativeFunction)(napi_env env, napi_callback_info info), 
                char *nativeFunctionName)
{
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0, nativeFunction, NULL, &fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }

  status = napi_set_named_property(env, exports, nativeFunctionName, fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }
}

napi_value Init(napi_env env, napi_value exports) 
{
  registerMethods(env, exports, &initValue, "initValue");
  registerMethods(env, exports, &insertSlot, "insertSlot");
  registerMethods(env, exports, &emitSignal, "emitSignal");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
