#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xF2, 0xD3, 0xFD, 0x8E, 0xE8, 0xD4, 0x44, 0xC8, 0xAA, 0xAE, 0x56, 0x98, 0x0F, 0x6E, 0xB5, 0x66 }
PBL_APP_INFO(MY_UUID,
             "ISS Tracker", "Pebble Examples",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
BmpContainer background_image;
TextLayer time_text_layer;
TextLayer nextpass_text_layer;
time_t nextpass_time = 1380853200;

void handle_init(AppContextRef ctx) {

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_fullscreen(&window, true);

  resource_init_current_app(&APP_RESOURCES);
  bmp_init_container(RESOURCE_ID_BACKGROUND_IMAGE, &background_image);
  layer_add_child(&window.layer, &background_image.layer.layer);

  text_layer_init(&time_text_layer, GRect(37, 1, 70, 24));
  text_layer_set_text(&time_text_layer, "18:42:42");
  text_layer_set_font(&time_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(&time_text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(&time_text_layer, GColorClear);

  text_layer_init(&nextpass_text_layer, GRect(0, 126, 144, 34));
  text_layer_set_text(&nextpass_text_layer, "00:10:22");
  text_layer_set_font(&nextpass_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS));
  text_layer_set_text_alignment(&nextpass_text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(&nextpass_text_layer, GColorClear);

  layer_add_child(window_get_root_layer(&window), (Layer*)&time_text_layer);
  layer_add_child(window_get_root_layer(&window), (Layer*)&nextpass_text_layer);
}

static char time_text[10];
static char nextpass_text[10];

void handle_tick(AppContextRef app_ctx, PebbleTickEvent *t) {

  string_format_time(time_text, sizeof(time_text), "%H:%M:%S", t->tick_time);
  text_layer_set_text(&time_text_layer, time_text);

  int nextpass = nextpass_time - time(NULL);
  if (nextpass > 0) {
    int nextpass_hours = nextpass / 3600;
    nextpass %= 3600;
    int nextpass_minutes = nextpass / 60;
    nextpass %= 60;

    snprintf(nextpass_text, sizeof(nextpass_text), "%i:%02i:%02i", nextpass_hours, nextpass_minutes, nextpass);
  }
  else {
    snprintf(nextpass_text, sizeof(nextpass_text), "--:--:--");
  }

  text_layer_set_text(&nextpass_text_layer, nextpass_text);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = SECOND_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
