#include <pebble.h>
#include "global.h"
#include "stopsdisplay.h"


bool initialized = false;



static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context){
    if(!initialized)
      return;

    char route_and_destination[32];
    snprintf(route_and_destination,32,"%s %s",stops[cell_index->row].route, stops[cell_index->row].destination);

    if(!strcmp(stops[cell_index->row].time, "0"))
      strcpy(stops[cell_index->row].time,"Now");
  
    menu_cell_basic_draw(ctx, cell_layer, route_and_destination, stops[cell_index->row].time, NULL);
        
} 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
   return 10;
} 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
    trigger_fetch_data(last_selected_stop);
}


void display_stops(){
    initialized = true;
  
    Window* display_window = window_create();
    menu_layer_destroy(menu_layer);
  
    Layer *window_layer = window_get_root_layer(display_window);
    GRect bounds = layer_get_bounds(window_layer);
    menu_layer = menu_layer_create(bounds);
 
    menu_layer_set_click_config_onto_window(menu_layer, display_window);
 
    MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
        .select_click = (MenuLayerSelectCallback) select_click_callback
    };
    menu_layer_set_callbacks(menu_layer, NULL, callbacks);
 
    menu_layer_set_highlight_colors(menu_layer, GColorMalachite, GColorBlack);
    menu_layer_set_click_config_onto_window(menu_layer, display_window);
    layer_add_child(window_get_root_layer(display_window), menu_layer_get_layer(menu_layer));
  
    window_stack_push(display_window, true);


}