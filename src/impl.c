#include "./impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

signal_database_t *signal_database;

void
allocateTable(void)
{
  signal_database = calloc(1, sizeof(signal_table_t)); // we have create one signal database to be filled up later.
}

// MARK: - Usefull methods for NAPI values. converting js to C or C to js etc.
size_t
getUTF8StringLength(napi_env env, napi_value arg)
{
  size_t signal_name_size;
  napi_get_value_string_utf8(env, arg, NULL, 0, &signal_name_size); // If NULL is passed in, the length of the string (in bytes) is returned into "str_size parameter".
  return signal_name_size;
}

char *
getUTFString(napi_env env, napi_value arg)
{
  char *signalName;
  // for utf8 parameter values see => https://nodejs.org/api/n-api.html#n_api_napi_get_value_string_utf8
  size_t signal_name_size = getUTF8StringLength(env, arg);
  size_t signal_name_size_read;
  signalName = (char*)calloc(signal_name_size + 1, sizeof(char)); // create the buffer size.
  signal_name_size = signal_name_size + 1;
  napi_get_value_string_utf8(env, arg, signalName, signal_name_size, &signal_name_size_read);
  
  return signalName;
}

napi_valuetype
typeOfNapValue(napi_env env, napi_value arg)
{
  napi_status status;
  napi_valuetype valType;
  status = napi_typeof(env, arg, &valType);
  
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }
  
  return valType;
}


// MARK: - Table and database methods
bool
checkExistenceOfDatabase()
{
  if(signal_database) return true;
  return false;
}

bool
sameTableExist()
{
  return false;
}

void
createSignalTableWithValue(napi_env env, char *name, napi_value val)
{
  assert(checkExistenceOfDatabase());
  
  signal_table_t *table = calloc(1, sizeof(signal_table_t));
  signal_table_t *head = signal_database->head;
  if(head) {
    // this means database already has table or tables in it.
    table->name = name;
    table->val = val;
    table->slot_count = 0;
    table->prev = head;
    
    signal_database->head = table;
    signal_database->table_count++;
  } else {
    // When this is the first table for database.
    table->name = name;
    table->val = val;
    table->slot_count = 0;
    
    signal_database->head = table;
    signal_database->table_count++;
  }
}

// MARK: - Native Methods
napi_value 
initValue(napi_env env, napi_callback_info info) 
{
  napi_status status;
  size_t argc = 2;

  char *signalName;

  // MARK: Take all parameters and set them to args.
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  // MARK: Signal name will always be string.
  // for utf8 parameter values see => https://nodejs.org/api/n-api.html#n_api_napi_get_value_string_utf8
  signalName = getUTFString(env, args[0]);

  createSignalTableWithValue(env, signalName, args[1]);

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
