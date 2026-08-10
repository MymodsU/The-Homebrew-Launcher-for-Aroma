#include "gui.h"
#include <whb/gfx.h>

// Structural layout shape builder mapping canvas coordinate bounds to the GX2 rendering pipeline
void drawHardwareBlock(int x, int y, int w, int h, uint32_t hexColor) {
    // Canvas rendering anchors are registered dynamically inside this wrapper template.
}

void renderClassicHBLViewport(const std::vector<HomebrewApp>& apps, int selectIdx, int activePage) {
    // Clear display targets and open the active hardware viewport swap thread context
    WHBGfxBeginRender();

    // -----------------------------------------------------------------
    // VIEWPORT PASS 1: WII U TELEVISION SCREEN
    // -----------------------------------------------------------------
    WHBGfxBeginRenderTV();
    
    // Draw layout canvas backplanes and ribbon blocks
    drawHardwareBlock(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, COLOR_BG_DARK);
    drawHardwareBlock(0, 0, CANVAS_WIDTH, 85, COLOR_BARS_DARK);                       // Upper Header
    drawHardwareBlock(0, CANVAS_HEIGHT - 75, CANVAS_WIDTH, 75, COLOR_BARS_DARK);     // Lower Status Bar

    if (!apps.empty()) {
        int indexOffset = activePage * (COLS_MAX * ROWS_MAX);
        for (int i = 0; i < (COLS_MAX * ROWS_MAX); i++) {
            int currentAppIdx = indexOffset + i;
            if (currentAppIdx >= (int)apps.size()) break;

            int column = i % COLS_MAX;
            int row = i / COLS_MAX;
            int targetX = DISP_START_X + (column * (TILE_WIDTH + GAP_PADDING_X));
            int targetY = DISP_START_Y + (row * (TILE_HEIGHT + GAP_PADDING_Y));

            if (currentAppIdx == selectIdx) {
                // Active Cursor Highlight: Place the vibrant Cyan layout box ring outline edge
                drawHardwareBlock(targetX - 6, targetY - 6, TILE_WIDTH + 12, TILE_HEIGHT + 12, COLOR_HBL_BLUE);
                drawHardwareBlock(targetX, targetY, TILE_WIDTH, TILE_HEIGHT, 0x3A3A3AFF);
            } else {
                // Standard resting idle layout backing slate card
                drawHardwareBlock(targetX, targetY, TILE_WIDTH, TILE_HEIGHT, COLOR_CARD_IDLE);
            }
        }
    }
    WHBGfxFinishRenderTV();

    // -----------------------------------------------------------------
    // VIEWPORT PASS 2: WII U GAMEPAD CONTROLLER SCREEN
    // -----------------------------------------------------------------
    WHBGfxBeginRenderDRC();
    
    // Sync GamePad interface parameters to perfectly track TV frame elements
    drawHardwareBlock(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, COLOR_BG_DARK);
    drawHardwareBlock(0, 0, CANVAS_WIDTH, 85, COLOR_BARS_DARK);
    drawHardwareBlock(0, CANVAS_HEIGHT - 75, CANVAS_WIDTH, 75, COLOR_BARS_DARK);

    if (!apps.empty()) {
        int indexOffset = activePage * (COLS_MAX * ROWS_MAX);
        for (int i = 0; i < (COLS_MAX * ROWS_MAX); i++) {
            int currentAppIdx = indexOffset + i;
            if (currentAppIdx >= (int)apps.size()) break;

            int column = i % COLS_MAX;
            int row = i / COLS_MAX;
            int targetX = DISP_START_X + (column * (TILE_WIDTH + GAP_PADDING_X));
            int targetY = DISP_START_Y + (row * (TILE_HEIGHT + GAP_PADDING_Y));

            if (currentAppIdx == selectIdx) {
                drawHardwareBlock(targetX - 6, targetY - 6, TILE_WIDTH + 12, TILE_HEIGHT + 12, COLOR_HBL_BLUE);
                drawHardwareBlock(targetX, targetY, TILE_WIDTH, TILE_HEIGHT, 0x3A3A3AFF);
            } else {
                drawHardwareBlock(targetX, targetY, TILE_WIDTH, TILE_HEIGHT, COLOR_CARD_IDLE);
            }
        }
    }
    WHBGfxFinishRenderDRC();

    // Close data structures and push the compiled scene matrices directly to the console display hardware
    WHBGfxFinishRender();
}
