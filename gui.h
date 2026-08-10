#pragma once

#include <wut.h>
#include <vector>
#include "../launcher.h"

// Screen viewport canvas limits (720p scaling framework coordinates)
#define CANVAS_WIDTH       1280
#define CANVAS_HEIGHT      720

// Color variables (Hexadecimal RGBA matrices)
#define COLOR_HBL_BLUE     0x00A2E8FF  // Iconic active neon selector outline ring
#define COLOR_BG_DARK      0x1A1A1AFF  // Smooth slate background workspace canvas theme
#define COLOR_CARD_IDLE    0x232323FF  // Unselected flat dark charcoal menu item tile backing
#define COLOR_BARS_DARK    0x111111FF  // Solid upper and lower system menu header panels

// Grid calculation constraints matching classic HBL row offsets
const int COLS_MAX         = 3;
const int ROWS_MAX         = 2;
const int TILE_WIDTH       = 256;
const int TILE_HEIGHT      = 96;
const int GAP_PADDING_X    = 40;
const int GAP_PADDING_Y    = 35;
const int DISP_START_X     = 180;
const int DISP_START_Y     = 170;

/**
 * @brief Renders the classic Homebrew Launcher graphical interface matrix viewport.
 * @param apps The vector collection of parsed homebrew paths and plugins.
 * @param selectIdx Index parameter tracking the currently highlighted active item card.
 * @param activePage The visible structural grid page offset boundary marker.
 */
void renderClassicHBLViewport(const std::vector<HomebrewApp>& apps, int selectIdx, int activePage);
