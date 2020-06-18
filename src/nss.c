#include <node_api.h>
#include "./impl.h"

napi_value Init(napi_env env, napi_value exports) 
{
  registerFunction(env, exports, &initValue, "initValue");
  registerFunction(env, exports, &insertSlot, "insertSlot");
  registerFunction(env, exports, &emitSignal, "emitSignal");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
