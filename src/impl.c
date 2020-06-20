#include "./impl.h"
#include <stdio.h>
#include <stdlib.h> 

void
registerSignalIntoSignalDB(napi_env env, napi_callback_info info){
    
}

napi_value 
initValue(napi_env env, napi_callback_info info) 
{
  napi_status status;
  size_t argc = 2;

  char *signalName;
  napi_value *signalValue;

  // MARK: - Take all parameters and set them to args.
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  // MARK: - Signal name will always be string.
  // for utf8 parameter values see => https://nodejs.org/api/n-api.html#n_api_napi_get_value_string_utf8
  size_t signal_name_size;
  size_t signal_name_size_read;
  napi_get_value_string_utf8(env, args[0], NULL, 0, &signal_name_size); // If NULL is passed in, the length of the string (in bytes) is returned into "str_size parameter".

  signalName = (char*)calloc(signal_name_size + 1, sizeof(char)); // create the buffer size.
  signal_name_size = signal_name_size + 1;
  napi_get_value_string_utf8(env, args[0], signalName, signal_name_size, &signal_name_size_read);

  // MARK: - Value of signals. It could be (boolean, string, integer or Object)
  // first of all learn the type of napi_value
  napi_valuetype napitype;
  status = napi_typeof(env, args[1], &napitype);
  
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }
  
  if(napitype == napi_boolean) {
    printf("%s is boolean\n", signalName);
  } else if(napitype == napi_string) {
    printf("%s is string\n", signalName);
  } else if(napitype == napi_object) {
    printf("%s is object\n", signalName);
  } else if(napitype == napi_number) {
    printf("%s is number\n", signalName);
  }

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
