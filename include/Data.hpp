#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 576;
const int BACKGROUND_WIDTH = 1280, BACKGROUND_HEIGHT = 1280;
// SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

#pragma region HUD

const std::string BG_Title{"res/gfx/rm_Title.png"};
const std::string BG_Room1{"res/gfx/BG_newgrass.png"};
const std::string HUD_expBarBase{"res/gfx/hud_expbar_bg.png"};
const std::string HUD_expBarTop{"res/gfx/hud_expbar_anim_89.png"};
const std::string EXP_Drop[6]{"res/gfx/spr_EXP/spr_EXP_0.png", "res/gfx/spr_EXP/spr_EXP2_0.png", "res/gfx/spr_EXP/spr_EXP3_0.png", "res/gfx/spr_EXP/spr_EXP4_0.png", "res/gfx/spr_EXP/spr_EXP5_0.png", "res/gfx/spr_EXP/spr_EXP6_0.png"};
const std::string Black_Screen{"res/gfx/rm_PauseRoom.png"};
const std::string Pause_Menu{"res/gfx/hud_pausemenu.png"};
const std::string HealthBar[2]{"res/gfx/hud_HUD_HP_green_1.png", "res/gfx/hud_HUD_HP_green_0.png"};
const std::string Button[2]{"res/gfx/hud_initButtons/hud_initButtons_0.png", "res/gfx/hud_initButtons/hud_initButtons_1.png"};

#pragma endregion

#pragma region Player

const std::string PlayerArrow{"res/gfx/spr_Arrow/spr_Arrow_0.png"};

const std::string Portrait_Suisei{"res/gfx/character_sprites/spr_SuiseiPortrait.png"};
const std::string Title_Suisei{"res/gfx/character_sprites/spr_Title_Suisei.png"};
const std::string IdleAnimation_Suisei[4] = {"res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_0.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_1.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_2.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_3.png"};
const std::string RunAnimation_Suisei[6] = {"res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_0.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_1.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_2.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_3.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_4.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_5.png"};

#pragma endregion

#pragma region Weapon

const std::string FanBeam_Animation[10] = {"res/gfx/spr_HoloBeam/spr_HoloBeam_0.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_1.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_2.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_3.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_4.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_5.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_6.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_7.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_8.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_9.png"};
const std::string BLBook_Animation = {"res/gfx/spr_BLBook.png"};
const std::string PsychoAxe_Animation[8] = {"res/gfx/spr_PsychoAxe/spr_PsychoAxe_0.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_1.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_2.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_3.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_4.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_5.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_6.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_7.png"};
const std::string IdolSong_Animation = {"res/gfx/spr_MusicalNote/spr_MusicalNote_0.png"};
const std::string FubuBeam_Animation[9] = {"res/gfx/spr_HoloBeam/spr_HoloBeam_1.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_2.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_3.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_4.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_5.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_6.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_7.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_8.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_9.png"};
const std::string LavaPoolStart_Animation[9] = {"res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_0.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_1.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_2.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_3.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_4.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_5.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_6.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_7.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_8.png"};
const std::string LavaPool = {"res/gfx/spr_LavaPoolLoop/spr_LavaPoolLoop_0.png"};
const std::string LavaPoolEnd_Animation[6] = {"res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_0.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_1.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_2.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_3.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_4.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_5.png"};
const std::string SuiseiFallingBlocks[4]{"res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_0.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_1.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_2.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_3.png"};

#pragma endregion

#pragma region Enemy

const float EnemyCD = 0.5f;

const std::string Deadbeat_Animation[3]{"res/gfx/spr_Deadbeat/spr_Deadbeat_0.png", "res/gfx/spr_Deadbeat/spr_Deadbeat_1.png", "res/gfx/spr_Deadbeat/spr_Deadbeat_2.png"};
const std::string Shrimp_Animation[3]{"res/gfx/spr_Shrimp/spr_Shrimp_0.png", "res/gfx/spr_Shrimp/spr_Shrimp_1.png", "res/gfx/spr_Shrimp/spr_Shrimp_2.png"};
const std::string Takodachi_Animation[3]{"res/gfx/spr_takodachi/spr_takodachi_0.png", "res/gfx/spr_takodachi/spr_takodachi_1.png", "res/gfx/spr_takodachi/spr_takodachi_2.png"};
const std::string KFP_Animation[3]{"res/gfx/spr_KFP/spr_KFP_0.png", "res/gfx/spr_KFP/spr_KFP_1.png", "res/gfx/spr_KFP/spr_KFP_2.png"};
const std::string DarkShrimp_Animation[3]{"res/gfx/spr_Shrimp2/spr_Shrimp2_0.png", "res/gfx/spr_Shrimp2/spr_Shrimp2_1.png", "res/gfx/spr_Shrimp2/spr_Shrimp2_2.png"};
const std::string Bloom_Animation[3]{"res/gfx/spr_AngelFairy/spr_AngelFairy_0.png","res/gfx/spr_AngelFairy/spr_AngelFairy_1.png","res/gfx/spr_AngelFairy/spr_AngelFairy_2.png"};
const std::string Gloom_Animation[3]{"res/gfx/spr_DevilFairy/spr_DevilFairy_0.png","res/gfx/spr_DevilFairy/spr_DevilFairy_1.png","res/gfx/spr_DevilFairy/spr_DevilFairy_2.png"};
const std::string Fubuzilla_Animation[12]{"res/gfx/spr_fubuzilla/spr_fubuzilla_0.png","res/gfx/spr_fubuzilla/spr_fubuzilla_1.png","res/gfx/spr_fubuzilla/spr_fubuzilla_2.png","res/gfx/spr_fubuzilla/spr_fubuzilla_3.png","res/gfx/spr_fubuzilla/spr_fubuzilla_4.png","res/gfx/spr_fubuzilla/spr_fubuzilla_5.png","res/gfx/spr_fubuzilla/spr_fubuzilla_6.png","res/gfx/spr_fubuzilla/spr_fubuzilla_7.png","res/gfx/spr_fubuzilla/spr_fubuzilla_8.png","res/gfx/spr_fubuzilla/spr_fubuzilla_9.png","res/gfx/spr_fubuzilla/spr_fubuzilla_10.png","res/gfx/spr_fubuzilla/spr_fubuzilla_11.png"};

#pragma endregion

const std::string font_8bitPLus{"res/gfx/font/8bitOperatorPlus8-Regular.ttf"};
const std::string font_munro{"res/gfx/font/munro.ttf"};
const std::string font_ModernDOS8x8{"res/gfx/font/ModernDOS8x8.ttf"};

const float spriteFrameTime{0.03};
const float enemyFrameTime{0.2};
const float SPAWN_CD{5};

const int MAX_WEAPON = 6;

enum Tabs
{
    Title = -1,
    Room1,
    InGame,
    Settings,
    Pause
};