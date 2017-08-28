#pragma once
#include <pebble.h>
#include "progress_layer.h"

#define PROGRESS_LAYER_WINDOW_DELTA 33
#define PROGRESS_LAYER_WINDOW_WIDTH 80
Window *s_window;
MenuLayer *stop_select_menu;
MenuLayer *menu_layer;
ProgressLayer *s_progress_layer;
struct stop{
  char route[3];
  char destination[32];
  int direction;
  char time[8];
};

struct stop stops[10];

int last_selected_stop;

void trigger_fetch_data(int stopid);
