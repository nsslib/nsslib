#ifndef __IMPLEMENTATIONS__
#define __IMPLEMENTATIONS__
#include <node_api.h>

typedef struct _signal_db_t signal_db_t;
typedef struct _slot_db_t slot_db_t;

struct _signal_db_t {
    napi_value val;
    slot_db_t *slots;
};

struct _slot_db_t {
    napi_value fn;
};

napi_value 
initValue(napi_env env, napi_callback_info info);

napi_value 
insertSlot(napi_env env, napi_callback_info info);

napi_value 
emitSignal(napi_env env, napi_callback_info info);

#else
#endif // __IMPLEMENTATIONS__
