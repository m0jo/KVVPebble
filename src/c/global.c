#include <pebble.h>
#include "global.h"
void trigger_fetch_data(int stopid){
  last_selected_stop = stopid;
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_int(iter, 0, &stopid, 4, true);
  app_message_outbox_send();
}