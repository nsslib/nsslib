#ifndef __NSS__
#include <node_api.h>

void
registerMethods( napi_env env, napi_value exports, 
                  napi_value (*nativeFunction)(napi_env env, napi_callback_info info), 
                  char *nativeFunctionName);

#endif // __NSS__