#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0xF2, 0xD3, 0xFD, 0x8E, 0xE8, 0xD4, 0x44, 0xC8, 0xAA, 0xAE, 0x56, 0x98, 0x0F, 0x6E, 0xB5, 0x66 }
PBL_APP_INFO(MY_UUID,
             "Template App", "Your Company",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer utc_text_layer;
TextLayer nextpass_text_layer;

void handle_init(AppContextRef ctx) {

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);

  text_layer_init(&utc_text_layer, GRect(0, 25, 144, 50));
  text_layer_set_text(&utc_text_layer, "18:42:42");
  text_layer_set_font(&utc_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text_alignment(&utc_text_layer, GTextAlignmentCenter);

  text_layer_init(&nextpass_text_layer, GRect(0, 80, 144, 50));
  text_layer_set_text(&nextpass_text_layer, "00:10:22");
  text_layer_set_font(&nextpass_text_layer, fonts_get_system_font(FONT_KEY_BITHAM_34_MEDIUM_NUMBERS));
  text_layer_set_text_alignment(&nextpass_text_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(&window), (Layer*)&utc_text_layer);
  layer_add_child(window_get_root_layer(&window), (Layer*)&nextpass_text_layer);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
