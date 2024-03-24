#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 576;
const int BACKGROUND_WIDTH = 1280, BACKGROUND_HEIGHT = 1280;

// SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

const std::string BG_Title {"res/gfx/rm_Title.png"};
const std::string BG_Room1 {"res/gfx/BG_newgrass.png"};
const std::string HUD_expBarBase {"res/gfx/hud_expbar_bg.png"};
const std::string HUD_expBarTop {"res/gfx/hud_expbar_anim_89.png"};
const std::string EXP_Drop {"res/gfx/spr_EXP/spr_EXP_0.png"};

#pragma region Portrait

const std::string Portrait_Suisei {"res/gfx/character_sprites/spr_SuiseiPortrait.png"};

#pragma endregion

#pragma region Enemy

const std::string Deadbeat_Animation[3] {"res/gfx/spr_Deadbeat/spr_Deadbeat_0.png","res/gfx/spr_Deadbeat/spr_Deadbeat_1.png","res/gfx/spr_Deadbeat/spr_Deadbeat_2.png"};
const std::string Shrimp_Animation[3] {"res/gfx/spr_Shrimp/spr_Shrimp_0.png","res/gfx/spr_Shrimp/spr_Shrimp_1.png","res/gfx/spr_Shrimp/spr_Shrimp_2.png"};

#pragma endregion

const std::string font_8bitPLus {"res/gfx/font/8bitOperatorPlus8-Regular.ttf"};

// int expForNextLevel = 100;

const int MAX_WEAPON = 6;

enum Tabs {
    Title = -1,
    Room1,
    InGame,
    Settings,
    Pause
};