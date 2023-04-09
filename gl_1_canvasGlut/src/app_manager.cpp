#include "app_manager.h"


AppManager::AppManager() {
    this->app_state = MENU;
    this->current_function = FUNCTION_NONE;
    this->screen_height = SCREENHEIGHT;
    this->screen_width = SCREENWIDTH;
}
