#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_set>

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
const std::string Upgrade[2]{"res/gfx/ui_menu_upgrade_window/ui_menu_upgrade_window_0.png", "res/gfx/ui_menu_upgrade_window/ui_menu_upgrade_window_selected_0.png"};
const std::string OptionCase{"res/gfx/hud_optionIconCase.png"};
const std::string Special_Bar[4]{"res/gfx/ui_SP_Bar_bg.png","res/gfx/ui_SP_Bar_fill.png","res/gfx/ui_SP_Bar_fill_rainbow.png","res/gfx/ui_SP_Bar_frame.png"};
const std::string EmptyWeaponSlot{"res/gfx/ui_empty_slot_weapon.png"};

#pragma endregion

#pragma region Player

const std::string PlayerArrow{"res/gfx/spr_Arrow/spr_Arrow_0.png"};

const std::string Portrait_Suisei{"res/gfx/character_sprites/spr_SuiseiPortrait.png"};
const std::string Title_Suisei{"res/gfx/character_sprites/spr_Title_Suisei.png"};
const std::string IdleAnimation_Suisei[4] = {"res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_0.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_1.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_2.png", "res/gfx/character_sprites/spr_Suisei_idle/spr_Suisei_idle_3.png"};
const std::string RunAnimation_Suisei[6] = {"res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_0.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_1.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_2.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_3.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_4.png", "res/gfx/character_sprites/spr_Suisei_run/spr_Suisei_run_5.png"};
const std::string SuiseiSpecial{"res/gfx/spr_SuiseiSpecial.png"};

#pragma endregion

#pragma region WeaponSprite

const std::string FanBeam_Animation[10] = {"res/gfx/spr_HoloBeam/spr_HoloBeam_0.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_1.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_2.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_3.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_4.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_5.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_6.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_7.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_8.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_9.png"};
const std::string FanBeam_Icon{"res/gfx/spr_HoloBeamIcon.png"};
const std::string BLBook_Animation = {"res/gfx/spr_BLBook.png"};
const std::string BLBook_Icon{"res/gfx/spr_BLBookIcon.png"};
const std::string PsychoAxe_Animation[8] = {"res/gfx/spr_PsychoAxe/spr_PsychoAxe_0.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_1.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_2.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_3.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_4.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_5.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_6.png", "res/gfx/spr_PsychoAxe/spr_PsychoAxe_7.png"};
const std::string PsychoAxe_Icon{"res/gfx/spr_PsychoAxeIcon.png"};
const std::string IdolSong_Animation = {"res/gfx/spr_MusicalNote/spr_MusicalNote_0.png"};
const std::string IdolSong_Icon = {"res/gfx/spr_MusicNoteIcon.png"};
const std::string FubuBeam_Animation[9] = {"res/gfx/spr_HoloBeam/spr_HoloBeam_1.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_2.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_3.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_4.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_5.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_6.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_7.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_8.png", "res/gfx/spr_HoloBeam/spr_HoloBeam_9.png"};
const std::string LavaPoolStart_Animation[9] = {"res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_0.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_1.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_2.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_3.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_4.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_5.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_6.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_7.png","res/gfx/spr_LavaPoolStart/spr_LavaPoolStart_8.png"};
const std::string LavaPool = {"res/gfx/spr_LavaPoolLoop/spr_LavaPoolLoop_0.png"};
const std::string LavaPoolEnd_Animation[6] = {"res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_0.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_1.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_2.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_3.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_4.png","res/gfx/spr_LavaPoolEnd/spr_LavaPoolEnd_5.png"};
const std::string LavaPool_Icon {"res/gfx/spr_elitelava.png"};
const std::string SuiseiFallingBlocks[12]{"res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_0.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_1.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_2.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_3.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_4.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_5.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_6.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_7.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_8.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_9.png", "res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_10.png","res/gfx/spr_SuiseiFallingBlocks/spr_SuiseiFallingBlocks_11.png"};
const std::string SuiseiWeapon_Icon[2]{"res/gfx/spr_SuiseiWeapon.png","res/gfx/spr_SuiseiMaxedWeapon.png"};
const std::string SpiderCooking_Icon{"res/gfx/spr_SpiderCookingIcon.png"};
const std::string CEOTears_Icon{"res/gfx/spr_CEOTearsIcon.png"};
#pragma endregion

#pragma region WeaponDescription

const std::string SuiseiWeaponDescription[7]{"Swing a bloody axe in an arc in front.","Increase damage by 30%.","Increase attack area by 20%.", "Reduce time between attacks by 10%.", "Increase damage by 30%.", "Increase attack area by 20%.", "Deal 3x damage"};
const std::string SpiderCookingDescription[7]{"Create an area of miasma around, dealing slow damage to enemies inside.", "Increase area by 15%.", "Increase damage by 30%.", "Increase area by 25%.", "Increase frequency of hits by 20%.", "Increase damage by 60%.", "Add small knockback on hit"};
const std::string EliteLavaDescription[7]{"Drop lava on the ground, burning targets slowly.", "Increase lava area by 20%.", "Throw 2 lava buckets.", "Increase damage by 30%% and increase duration of lava by 1 second.", "Increase damage by 30%.", "Throw 3 lava buckets.", "Throw 4 lava buckets and increase lava size by 20%."};
const std::string PsychoAxeDescription[7]{"Throw an axe that spirals outward from the player.", "Increase size of axe by 20%. Increase damage by 20%.", "Reduce time between attacks by 20%.", "Increase damage by 33%, and size by 20%.", "Remove hit limit, and lasts 1 second longer.", "Increase attack size by 50%.", "Increase damage by 50%."};
const std::string BLBookDescription[7]{"Repels targets with orbiting BL Books.", "Add 1 additional book.", "Increase damage by 30%% and increase duration by 1 second.", "Add 1 additional book.", "Increase radius and spinning speed by 25%.", "Add 1 additional book.", "Increase damage by 40%."};
const std::string IdolSongDescription[7]{"Magical music notes that float vertically in both directions.", "Increase damage by 25%.", "Increase speed and travel width.", "Increase music note size by 25%.", "Reduce the time between attacks by 20%.", "Increase music note size by 25%.", "Increase damage by 50%."};
const std::string FanBeamDescription[7]{"Shoot a powerful laser beam from the microphone. Horizontal only.", "Increase size by 30%.", "Reduce attack cooldown by 0.5 second.", "Increase damage by 50%.", "Reduce attack cooldown by 0.5 second.", "Increase beam size by 50%.", "Fire an additional beam behind."};
const std::string CeoTearsDescription[7]{"Fires rapid tears at random targets.", "Increase damage by 20%.", "Shoot 2 tears.", "Reduce the time between attacks by 33%.", "Tears are 25%% faster and increase damage by 20%.", "Reduce the time between attacks by 50%.", "Shoot 4 tears."};

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
    Pause,
    Level_Up
};