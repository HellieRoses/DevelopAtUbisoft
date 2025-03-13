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
static constexpr int TILE_X_MAX = 34;
static constexpr int TILE_Y_MAX = 19;

static constexpr int THIEF_BASE_SPRITE_SIZE = 32;
static constexpr float THIEF_SCALE = (MINI_TILE_SIZE / THIEF_BASE_SPRITE_SIZE);
static constexpr float THIEF_SPRITE_SIZE = THIEF_BASE_SPRITE_SIZE * THIEF_SCALE;
static constexpr float THIEF_ORIGIN_X = 32.f;
static constexpr float THIEF_ORIGIN_Y = 8.f;
static constexpr uint TILE_THIEF_START_X = 34;
static constexpr uint TILE_THIEF_START_Y = 17;
static constexpr uint TILE_THIEF_END_X = 1;
static constexpr uint TILE_THIEF_END_Y = 0;
static constexpr float THIEF_SPEED = MINI_TILE_SIZE * 1.5f;

static constexpr uint NB_THIEFS_MAX = 6;
static constexpr uint NB_THIEFS_CURRENT = 0;
static constexpr int PV_LOST_ON_SHOT = 3;

static constexpr float MISSILE_SPEED = MINI_TILE_SIZE * 3.f;

static constexpr float PLAYER_MONEY = 200.f;
static constexpr float MONEYOUT_LOOSE = 100.f;

static constexpr uint FRAME_LIMIT = 60;
static constexpr float WINDOW_SIZE_X = MINI_TILE_SIZE * TILE_X_MAX;
static constexpr float WINDOW_SIZE_Y = MINI_TILE_SIZE * TILE_Y_MAX;

