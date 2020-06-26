#include "./impl.h"
#include "./errorhandling.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// MARK: - Allocation
signal_database_t *signal_database;

void
allocateTable(void)
{
  signal_database = calloc(1, sizeof(signal_table_t)); // we have create one signal database to be filled up later.
  signal_database->signal_names = (char**)malloc(MAX_SIGNAL_SIZE * sizeof(char)); // allocate 2 dimensional array
}

void
deallocateTable(void)
{
  free(signal_database->signal_names);
  free(signal_database);
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
getUTF8AsChar(napi_env env, napi_value arg)
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
typeOfNapiValue(napi_env env, napi_value arg)
{
  napi_status status;
  napi_valuetype valType;
  status = napi_typeof(env, arg, &valType);
  
  if (status != napi_ok) {
    raiseError(env, FAILED_TO_PARSE_ARGUMENTS, NULL);
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
checkSignalExist(char *name)
{
  // Check for same signal name. There can not be same signal name twice.
  if (signal_database->table_count > 0) {
    for (int i = 0; i <= signal_database->table_count; i++) {
      if(strcmp(name, signal_database->signal_names[i]) == 0) {
        return true;
      }
    }
  }
  return false;
}

void
registerSlotIntoSignalTable(napi_env env, char *signal_name, napi_value fn)
{
  if (signal_database->table_count > 0) {
    
    signal_table_t *table = NULL;
    signal_table_t *signal_table_head = signal_database->head; // take the last registered signal_table
    slots_t *slot = malloc(sizeof(slots_t));
    
    // first of all find the relevant signal table for slot registration
    while (signal_table_head) {
      if(strcmp(signal_table_head->name, signal_name) == 0) {
        table = signal_table_head;
      }
      signal_table_head = signal_table_head->prev;
    }
    
    // If the signal table not exist then raise error.
    if(!table) {
      raiseError(env, SIGNAL_NOT_EXIST, signal_name);
    } else {
      // check if slot is a function ? slots should be function...
      if(typeOfNapiValue(env, fn) == napi_function) {
        slot->fn = fn;
      } else {
        raiseError(env, SLOT_VAL_SHOULD_A_FUNC, NULL);
      }

      if(table->slot_head) {
        // if there is alread registered slots...
        slot->prev = table->slot_head;
      } else {
        // if there are no any registered slots...
        slot->prev = NULL;
      }
      table->slot_head = slot;
      table->slots = slot;
      table->slot_count++;
    }
    
  } else {
    raiseError(env, SIGNAL_DB_EMPTY, NULL);
  }
  
}

void
registerSignalNamesIntoDatabase(napi_env env, char *name)
{
  signal_database->signal_names[signal_database->table_count] = (char*)malloc(strlen(name) * sizeof(char)); // allocate the space in 2 dim.arr. for string.
  if(checkSignalExist(name)) {
    raiseError(env, SAME_SIGNAL, name);
  }
  signal_database->signal_names[signal_database->table_count] = name;
}

void
createSignalTableWithNapiValue(napi_env env, char *name, napi_value val)
{
  assert(checkExistenceOfDatabase());
  registerSignalNamesIntoDatabase(env, name); // Check this at the top. Because inside the function we are checking if table_count > 0.
  
  signal_table_t *table = calloc(1, sizeof(signal_table_t));
  signal_table_t *head = signal_database->head;
  if(head) {
    // this means database already has table or tables in it.
    table->name = name;
    table->val = val;
    table->slot_count = 0;
    table->prev = head;
  } else {
    // When this is the first table for database.
    table->name = name;
    table->val = val;
    table->slot_count = 0;
  }
  
  //addSignalNamesEndToEnd(name);
  signal_database->head = table;
  signal_database->table_count++;
}

// MARK: - Native Methods
napi_value 
initValue(napi_env env, napi_callback_info info) 
{
  napi_status status;
  size_t argc = 2;
  napi_value args[argc];
  char *signalName;

  // MARK: Parse all javascript arguments into args.
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    raiseError(env, FAILED_TO_PARSE_ARGUMENTS, NULL);
  }

  // MARK: Signal name will always be string.
  if(typeOfNapiValue(env, args[0]) != napi_string) {
    raiseError(env, SIGNAL_NAME_SHOULD_CHAR, NULL);
  }
  
  // for utf8 parameter values see => https://nodejs.org/api/n-api.html#n_api_napi_get_value_string_utf8
  signalName = getUTF8AsChar(env, args[0]);
  createSignalTableWithNapiValue(env, signalName, args[1]);

  return NULL;
}

napi_value 
insertSlot(napi_env env, napi_callback_info info) 
{
  napi_status status;
  size_t argc = 2;
  napi_value args[argc];
  char *signalName;

  // MARK: Parse all javascript arguments into args.
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  if (status != napi_ok) {
    raiseError(env, FAILED_TO_PARSE_ARGUMENTS, NULL);
  }
  
  // MARK: Signal name will always be string.
  if(typeOfNapiValue(env, args[0]) != napi_string) {
    raiseError(env, SIGNAL_NAME_SHOULD_CHAR, NULL);
  }
  
  // for utf8 parameter values see => https://nodejs.org/api/n-api.html#n_api_napi_get_value_string_utf8
  signalName = getUTF8AsChar(env, args[0]);
  registerSlotIntoSignalTable(env, signalName, args[1]);
  
  return NULL;
}

napi_value 
emitSignal(napi_env env, napi_callback_info info) 
{
  
  return NULL;
}
