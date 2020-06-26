#include "errorhandling.h"
#include <string.h>
#include <stdlib.h>

void
raiseError(napi_env env, err_codes_t code, char *p)
{
  char text[150];

  switch (code) {
    case UNABLE_TO_WRAP_NATIVE:
      napi_throw_error(env, NULL, "[-] Unable to wrap native function!");
      break;
      
    case UNABLE_TO_POPULATE:
      napi_throw_error(env, NULL, "[-] Unable to populate exports!");
      break;
      
    case FAILED_TO_PARSE_ARGUMENTS:
      napi_throw_error(env, NULL, "[-] Failed to parse arguments!");
      break;
      
    case SAME_SIGNAL:
      strcpy(text, "[-] You already registered the signal name: ");
      strcat(text, p);
      napi_throw_error(env, NULL, text);
      break;
      
    case SIGNAL_NOT_EXIST:
      strcpy(text, "[-] Signal name does not exist: ");
      strcat(text, p);
      napi_throw_error(env, NULL, text);
      break;
      
    case SIGNAL_NAME_SHOULD_CHAR:
      napi_throw_error(env, NULL, "[-] Signal name always be string.");
      break;
      
    case SIGNAL_DB_EMPTY:
      napi_throw_error(env, NULL, "[-] You haven't registered any signal yet.");
      break;
      
    case SLOT_VAL_SHOULD_A_FUNC:
      napi_throw_error(env, NULL, "[-] Slot value should be function.");
      break;
    
    default:
      break;
  }
}
