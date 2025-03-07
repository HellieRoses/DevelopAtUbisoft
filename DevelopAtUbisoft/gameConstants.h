#pragma once
#include <string>
static const std::string SPRITES_PATH = "assets/sprites/";

static constexpr float MIN_SCALE = 3.f;
static constexpr int MINI_BASE_TILE_SIZE = 16;
static constexpr float MINI_TILE_SIZE = MINI_BASE_TILE_SIZE * MIN_SCALE;
static constexpr float MINI_ORIGIN = MINI_BASE_TILE_SIZE / 2;

static constexpr int MAX_BASE_TILE_SIZE = 64;
static constexpr float MAX_SCALE = MINI_TILE_SIZE / MAX_BASE_TILE_SIZE;
static constexpr float MAX_TILE_SIZE = MINI_BASE_TILE_SIZE * MAX_SCALE;
static constexpr float MAX_ORIGIN = MAX_BASE_TILE_SIZE / 2;

static constexpr float THIEF_SCALE = MIN_SCALE / 2;
static constexpr float THIEF_SPEED = MINI_TILE_SIZE * 1.5f;

static constexpr float MISSILE_SPEED = MINI_TILE_SIZE * 3.f;

static constexpr float PLAYER_MONEY = 200.f;
