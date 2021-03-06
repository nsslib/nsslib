#include "./impl.h"
#include "./errorhandling.h"
#include <node_api.h>
#include <stdlib.h>

void
registerMethods(napi_env env,
              napi_value exports,
              napi_value (*nativeFunction)(napi_env env, napi_callback_info info),
              char *nativeFunctionName)
{
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0, nativeFunction, NULL, &fn);
  if (status != napi_ok) {
    raiseError(env, UNABLE_TO_WRAP_NATIVE, NULL);
  }

  status = napi_set_named_property(env, exports, nativeFunctionName, fn);
  if (status != napi_ok) {
    raiseError(env, UNABLE_TO_POPULATE, NULL);
  }
}

napi_value Init(napi_env env, napi_value exports) 
{
  allocateTable();
  
  registerMethods(env, exports, &initValue, "initValue");
  registerMethods(env, exports, &insertSlot, "insertSlot");
  registerMethods(env, exports, &emitSignal, "emitSignal");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
