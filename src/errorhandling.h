#ifndef errorhandling_h
#define errorhandling_h

#include <stdio.h>
#include <node_api.h>

typedef enum _err_codes_t err_codes_t;

enum _err_codes_t {
  UNABLE_TO_WRAP_NATIVE,
  UNABLE_TO_POPULATE,
  FAILED_TO_PARSE_ARGUMENTS,
  SAME_SIGNAL,
  SIGNAL_NOT_EXIST,
  SIGNAL_NAME_SHOULD_CHAR
};

void
raiseError(napi_env env, err_codes_t code, char *p);

#endif /* errorhandling_h */
