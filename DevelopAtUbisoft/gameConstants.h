#pragma once
#include <string>
#include "core.h"
static const std::string SPRITES_PATH = "assets/sprites/";

static constexpr float MIN_SCALE = 3.f;
static constexpr int MINI_BASE_TILE_SIZE = 16;
static constexpr float MINI_TILE_SIZE = MINI_BASE_TILE_SIZE * MIN_SCALE;
static constexpr float MINI_ORIGIN = MINI_BASE_TILE_SIZE /2.f;

static constexpr int MAX_BASE_TILE_SIZE = 64;
static constexpr float MAX_SCALE = MINI_TILE_SIZE / MAX_BASE_TILE_SIZE;
static constexpr float MAX_TILE_SIZE = MINI_BASE_TILE_SIZE * MAX_SCALE;
static constexpr float MAX_ORIGIN = MAX_BASE_TILE_SIZE / 2;

static constexpr float TILE_ORIGIN_X = 16.f;
static constexpr float TILE_ORIGIN_Y = 0.f;
static constexpr int TILE_X_MAX = 29;
static constexpr int TILE_Y_MAX = 18;

static constexpr int THIEF_BASE_SPRITE_SIZE = 32;
static constexpr float THIEF_SCALE = (MINI_TILE_SIZE / THIEF_BASE_SPRITE_SIZE);
static constexpr float THIEF_SPRITE_SIZE = THIEF_BASE_SPRITE_SIZE * THIEF_SCALE;
static constexpr float THIEF_ORIGIN_X = 16.f;
static constexpr float THIEF_ORIGIN_Y = 48.f;
static constexpr uint TILE_THIEF_START_X = 29;
static constexpr uint TILE_THIEF_START_Y = TILE_Y_MAX -2;
static constexpr uint TILE_THIEF_END_X = 1;
static constexpr uint TILE_THIEF_END_Y = 0;
static constexpr float THIEF_SPEED = MINI_TILE_SIZE * 1.5f ;

static constexpr uint NB_THIEFS_MAX = 6;
static constexpr uint NB_THIEFS_CURRENT = 0;
static constexpr int PV_LOST_ON_SHOT = 3;

static constexpr float MISSILE_SPEED = MINI_TILE_SIZE * 3.f;

static constexpr float PLAYER_MONEY = 50.0f;
static constexpr float MONEY_STOLEN = 10.f;
static constexpr float MONEYOUT_LOOSE = 100.f;

static constexpr uint FRAME_LIMIT = 60;
static constexpr float WINDOW_SIZE_X = MINI_TILE_SIZE * 34;
static constexpr float WINDOW_SIZE_Y = MINI_TILE_SIZE * 19;

static constexpr int PANEL_SIZE_X = 240;
static constexpr int PANEL_SIZE_Y = 192;
static constexpr float PANEL_POS_X = MINI_TILE_SIZE * TILE_X_MAX;
static constexpr float PANEL_POS_Y = (MINI_TILE_SIZE * TILE_Y_MAX)/2 -PANEL_SIZE_X/2 ;
static constexpr int MINI_PANEL_SIZE_X = 190;
static constexpr int MINI_PANEL_SIZE_Y = 45;
static constexpr float MINI_PANEL_SCALE_X = 1.1f;
static constexpr float MINI_PANEL_SCALE_Y = 1.f;
static constexpr float MINI_PANEL_POS_X_1 = WINDOW_SIZE_X/2 - (MINI_PANEL_SIZE_X * MINI_PANEL_SCALE_X) -10;
static constexpr float MINI_PANEL_POS_X_2 = WINDOW_SIZE_X / 2 +10;
static constexpr float MINI_PANEL_POS_Y = WINDOW_SIZE_Y - MINI_PANEL_SIZE_Y* MINI_PANEL_SCALE_Y;

static constexpr float TURRET_PRICE = 150.f;

static constexpr int BACKGROUND_SIZE_X = 256;
static constexpr int BACKGROUND_SIZE_Y = 143;
static constexpr float BACKGROUND_SCALE = 6.375f;
static constexpr float BACKGROUND_REAL_SIZE_X = BACKGROUND_SIZE_X * BACKGROUND_SCALE;
static constexpr float BACKGROUND_REAL_SIZE_Y = BACKGROUND_SIZE_Y * BACKGROUND_SCALE;