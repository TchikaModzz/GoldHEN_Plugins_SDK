#include <stdio.h>
#include "../include/GoldHEN.h"
#include <orbis/libkernel.h>
#include <stdint.h>
#include <stddef.h>
#include "menu.h"

extern "C" int sceSysUtilSendSystemNotificationWithText(int messageType, const char *message);
extern "C" __attribute__((visibility("default"))) const char *g_pluginName = "BO3 Modern Base";
extern "C" __attribute__((visibility("default"))) const char *g_pluginDesc = "Menu by TM";
extern "C" __attribute__((visibility("default"))) const char *g_pluginAuth = "RaiDougie";
extern "C" __attribute__((visibility("default"))) uint32_t g_pluginVersion = 0x100; // v1.0.0

// Thread de fond pour la logique du menu
void* menu_thread(void* arg) {
    // Initialisation de notre structure de menu
    g_Menu.Init();

    while (true) {
        // 1. Lire les inputs de la manette
        g_Menu.HandleInput();

        // 2. Pause de 16ms (~60 FPS) pour ne pas saturer le processeur de la PS4
        sceKernelUsleep(16 * 1000); 
    }
    return nullptr;
}

extern "C" {
    // Points d'entrée invisibles depuis l'extérieur du module
    __attribute__((visibility("hidden"))) int module_start(size_t argc, const void *args) {
        // Notification sur la PS4 au chargement du plugin via GoldHEN
        sceSysUtilSendSystemNotificationWithText(222, "BO3 Base Loaded\nMenu Initialized");

        // Création du thread principal via l'API OpenOrbis
        OrbisPthread thread;
        scePthreadCreate(&thread, NULL, menu_thread, NULL, "bo3_menu_thread");

        return 0;
    }

    __attribute__((visibility("hidden"))) int module_stop(size_t argc, const void *args) {
        return 0;
    }
}
