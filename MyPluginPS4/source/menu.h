#pragma once
#include <stdint.h>

enum OptionType {
    OPTION_BUTTON,
    OPTION_TOGGLE
};

struct MenuOption {
    const char* name;
    OptionType type;
    bool* toggleValue;
    void (*callback)();
};

struct MenuPage {
    const char* title;
    MenuOption options[20];
    int size;
};

class BO3Menu {
private:
    MenuPage pages[10];
    int currentMenuID;
    int selectedIndex;
    bool isOpen;

public:
    void Init();
    void AddButton(int pageId, const char* name, void (*cb)());
    void AddToggle(int pageId, const char* name, bool* var, void (*cb)() = nullptr);
    
    void HandleInput();
    void Draw();
    
    bool IsOpen() const { return isOpen; }
};

extern BO3Menu g_Menu;