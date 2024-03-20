#pragma once

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 580;
const int BACKGROUND_WIDTH = 1280, BACKGROUND_HEIGHT = 1280;

enum Tabs {
    Menu = -1,
    InGame,
    Settings,
    Pause
};