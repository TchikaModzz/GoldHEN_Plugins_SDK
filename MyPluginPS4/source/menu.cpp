#include "menu.h"

BO3Menu g_Menu;

// Exemples de variables pour tes triches BO3
bool g_GodMode = false;
bool g_InfiniteAmmo = false;

void ToggleGodMode() {
    // Ici, tu appliqueras ton écriture mémoire ou l'appel de fonction BO3 pour le God Mode
}

void BO3Menu::Init() {
    isOpen = false;
    currentMenuID = 0;
    selectedIndex = 0;

    // Page 0 : Menu Principal
    pages[0].title = "BO3 MAIN MENU";
    pages[0].size = 0;

    AddToggle(0, "God Mode", &g_GodMode, ToggleGodMode);
    AddToggle(0, "Infinite Ammo", &g_InfiniteAmmo);
    
    // Tu ajouteras tes sous-menus (Match Privé, Zombies, etc.) de la même manière
}

void BO3Menu::AddButton(int pageId, const char* name, void (*cb)()) {
    int idx = pages[pageId].size;
    pages[pageId].options[idx] = { name, OPTION_BUTTON, nullptr, cb };
    pages[pageId].size++;
}

void BO3Menu::AddToggle(int pageId, const char* name, bool* var, void (*cb)()) {
    int idx = pages[pageId].size;
    pages[pageId].options[idx] = { name, OPTION_TOGGLE, var, cb };
    pages[pageId].size++;
}

void BO3Menu::HandleInput() {
    // Logique de capture de touches générique (à lier avec les structures de touches BO3 ou les Syscalls de la manette)
    // Exemple d'interrupteur d'ouverture :
    
    /* if (Touches_Pressees(BO3_L1) && Touches_Pressees(BO3_DPAD_LEFT)) {
        isOpen = !isOpen;
    }
    */

    if (!isOpen) return;

    // Déplacement Haut / Bas
    /*
    if (Touches_Just_Pressees(BO3_DPAD_UP)) {
        selectedIndex = (selectedIndex <= 0) ? pages[currentMenuID].size - 1 : selectedIndex - 1;
    }
    if (Touches_Just_Pressees(BO3_DPAD_DOWN)) {
        selectedIndex = (selectedIndex >= pages[currentMenuID].size - 1) ? 0 : selectedIndex + 1;
    }
    */

    // Validation (Touche X)
    /*
    if (Touches_Just_Pressees(BO3_BUTTON_X)) {
        MenuOption& opt = pages[currentMenuID].options[selectedIndex];
        if (opt.type == OPTION_TOGGLE && opt.toggleValue) {
            *opt.toggleValue = !(*opt.toggleValue);
        }
        if (opt.callback) {
            opt.callback();
        }
    }
    */
}

void BO3Menu::Draw() {
    if (!isOpen) return;

    // C'est ici que tu appelleras tes fonctions de dessin (ex: R_RegisterFont, UI_DrawText, ou CG_DrawEngineText)
    // à l'aide des patterns/offsets trouvés sur BO3 PS4.
}