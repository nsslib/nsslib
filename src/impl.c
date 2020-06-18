#include "./impl.h"

napi_value 
initValue(napi_env env, napi_callback_info info) 
{

    return NULL;
}

napi_value 
insertSlot(napi_env env, napi_callback_info info) 
{

    return NULL;
}

napi_value 
emitSignal(napi_env env, napi_callback_info info) 
{

    return NULL;
}

void
registerFunction( napi_env env, napi_value exports, 
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