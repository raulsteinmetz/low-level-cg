#ifndef APP_MANAGER_H
#define APP_MANAGER_H

// states
#define MENU 0
#define MAIN_APP 1

// functions
#define FUNCTION_NONE 0
#define FUNCTION_DRAW 1
#define BUTTON_DELAY 100
#define FUNCTION_MODIFY 2
#define FUNCTION_MOVE 3
// screen
#define SCREENHEIGHT 1536
#define SCREENWIDTH 1536

class AppManager {
public:
    // state
    static int app_state;
    // function
    static int current_function;
    // screen width
    static int screen_width;
    // screen height
    static int screen_height;
};

// initialization of static class members
int AppManager::app_state = MENU;
int AppManager::current_function = FUNCTION_NONE;
int AppManager::screen_width = SCREENWIDTH;
int AppManager::screen_height = SCREENHEIGHT;

#endif // APP_MANAGER_H