#include <pebble.h>
#include "global.h"
#include "stopselect.h"
#include "stopsdisplay.h"


static int msgsize = 1024*10;
static char messagebuffer[1024*10];


int index = 0;


static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
    printf("inbox_received_callback");
    Tuple *t = dict_find(iterator, MESSAGE_KEY_route);
    strcpy(stops[index].route, t->value->cstring);
  
    t = dict_find(iterator, MESSAGE_KEY_destination);
    strcpy(stops[index].destination, t->value->cstring);
  
    t = dict_find(iterator, MESSAGE_KEY_direction);
    stops[index].direction = t->value->int32;
  
    t = dict_find(iterator, MESSAGE_KEY_time);
    strcpy(stops[index].time, t->value->cstring);
  
    progress_layer_set_progress(s_progress_layer, 10*index);
  
    index++;
    if(index == 10){
      window_stack_pop(true);
      index = 0;
      display_stops();
    }
 
}
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {

}
static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}


static void init(void) {
  s_window = window_create();
  
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);

  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  const int inbox_size = msgsize;
  const int outbox_size = msgsize;
  app_message_open(inbox_size, outbox_size);
  
  window_stack_push(s_window, true);
  build_stop_select();

}


static void deinit(void) {
	menu_layer_destroy(menu_layer);
  menu_layer_destroy(stop_select_menu);

	window_destroy(s_window);
}
int main(void) {
	init();
	app_event_loop();
	deinit();
}
