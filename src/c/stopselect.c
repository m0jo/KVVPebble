#include <pebble.h>
#include "stopselect.h"
#include "global.h"

static void show_progressbar(){
    Window* progress_window = window_create();
    Layer *window_layer = window_get_root_layer(progress_window);
    GRect bounds = layer_get_bounds(window_layer);
  
    s_progress_layer = progress_layer_create(GRect((bounds.size.w - PROGRESS_LAYER_WINDOW_WIDTH) / 2, 80, PROGRESS_LAYER_WINDOW_WIDTH, 6));
    progress_layer_set_progress(s_progress_layer, 0);
    progress_layer_set_corner_radius(s_progress_layer, 2);
    progress_layer_set_foreground_color(s_progress_layer, GColorBlack);
    progress_layer_set_background_color(s_progress_layer, GColorMalachite);
    layer_add_child(window_layer, s_progress_layer);
    window_stack_push(progress_window, true);
}

static void stop_select_draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context){
 
    switch(cell_index->row){
      case 0:
        menu_cell_basic_draw(ctx, cell_layer, "Durlacher Tor", "", NULL);
        break;
      case 1:
        menu_cell_basic_draw(ctx, cell_layer, "Hagsfeld", "", NULL);
        break;
      case 2:
        menu_cell_basic_draw(ctx, cell_layer, "Kronenplatz", "", NULL);
        break;
    }          
} 
static uint16_t stop_select_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context){
   return 3;
} 
static void stop_select_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context){
    show_progressbar();
    switch(cell_index->row){
      case 0:
        //Durlacher Tor
        trigger_fetch_data(3);
        break;
      
      case 1:
        //Hagsfeld
        trigger_fetch_data(3102);
        break;
      
      case 2:
        //Kronenplatz
        trigger_fetch_data(80);
        break;     

    }
}

void build_stop_select(){  

    Layer *window_layer = window_get_root_layer(s_window);
    GRect bounds = layer_get_bounds(window_layer);
    stop_select_menu = menu_layer_create(bounds);
    //Let it receive clicks
    menu_layer_set_click_config_onto_window(stop_select_menu, s_window);
 
    //Give it its callbacks
    MenuLayerCallbacks callbacks = {
        .draw_row = (MenuLayerDrawRowCallback) stop_select_draw_row_callback,
        .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) stop_select_num_rows_callback,
        .select_click = (MenuLayerSelectCallback) stop_select_select_click_callback
    };
    menu_layer_set_callbacks(stop_select_menu, NULL, callbacks);
    menu_layer_set_highlight_colors(stop_select_menu, GColorMalachite, GColorBlack);
    menu_layer_set_click_config_onto_window(stop_select_menu, s_window);
    //Add to Window
    layer_add_child(window_get_root_layer(s_window), menu_layer_get_layer(stop_select_menu));
}

