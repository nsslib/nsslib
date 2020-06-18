#ifndef __IMPLEMENTATIONS__
#include <node_api.h>

typedef struct _signal signal;
typedef struct _slot slot;

struct _signal {
    napi_value val;
    slot *slots;
};

struct _slot {
    napi_value fn;
};


napi_value 
initValue(napi_env env, napi_callback_info info);

napi_value 
insertSlot(napi_env env, napi_callback_info info);

napi_value 
emitSignal(napi_env env, napi_callback_info info);

#endif // __IMPLEMENTATIONS__
