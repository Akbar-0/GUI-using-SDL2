#include "RoundCornerRect.h"
#include <cmath>

void DrawRoundedRect(SDL_Renderer* renderer, int x, int y, int w, int h, int radius) {
    // Draw the main rectangle
    SDL_Rect rect = { x + radius, y, w - 2 * radius, h };
    SDL_RenderFillRect(renderer, &rect);

    rect = { x, y + radius, w, h - 2 * radius };
    SDL_RenderFillRect(renderer, &rect);

    // Draw the four rounded corners
    for (int i = 0; i < 4; ++i) {
        // Determine the circles' center positions
        int cx = (i % 2 == 0) ? x + radius : x + w - radius;
        int cy = (i < 2) ? y + radius : y + h - radius;

        // Draw Quarter Circles
        for (int ya = (i < 2) ? -radius : 0; ya <= ((i < 2) ? 0 : radius); ++ya) {
            for (int xa = (i % 2 == 0) ? -radius : 0; xa <= ((i % 2 == 0) ? 0 : radius); ++xa) {
                if (xa*xa + ya*ya <= radius*radius) {
                    SDL_RenderDrawPoint(renderer, cx + xa, cy + ya);
                }
            }
        }
    }
}
