#include <SDL2/SDL.h>
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
uint8_t buffbank = 0;

uint8_t palette[256][3] = {
	{0, 0, 0},
	{0, 0, 128},
	{0, 128, 0},
	{0, 128, 128},
	{128, 0, 0},
	{128, 0, 128},
	{128, 128, 0},
	{128, 128, 128},
	{64, 64, 64},
	{0, 0, 255},
	{0, 255, 0},
	{0, 255, 255},
	{255, 0, 0},
	{255, 0, 255},
	{255, 255, 0},
	{255, 255, 255},
};

#include "font.h"

uint32_t raw_video_out[SCREEN_WIDTH*SCREEN_HEIGHT];

void draw_char(int _x, int _y, uint8_t c, uint8_t col) {
	uint8_t *char_bitmap = &console_font_8x8[c * 8];

	for (int py = 0; py < 8; ++py) {
		for (int px = 0; px < 8; ++px) {
			int x = _x  + px;
			int y = _y  + py;
			uint32_t color;

			// Set color for the pixel: 1 is foreground, 0 is background
			if (char_bitmap[py] & (1 << (7 - px))) {
				color = 0xFF000000 | (palette[col & 0xF][2] << 16) | (palette[col & 0xF][1] << 8) | palette[col & 0xF][0];
			} else {
				color = 0xFF000000 | (palette[(col >> 4) & 0xF][2] << 16) | (palette[(col >> 4) & 0xF][1] << 8) | palette[(col >> 4) & 0xF][0];
			}

			raw_video_out[y * SCREEN_WIDTH + x] = color;
		}
	}
}

void draw_buffer() {
	int i = 0;
	for (int y = 0; y < SCREEN_HEIGHT; y += 8) {
		for (int x = 0; x < SCREEN_WIDTH; x += 8) {
			uint8_t c = video_ram[i++];
			uint8_t col = video_ram[i++];
			draw_char(x, y, c, col);
		}
	}

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(raw_video_out, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SCREEN_WIDTH * 4, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
	if (surface == NULL) {
		fprintf(stderr, "SDL_CreateRGBSurfaceFrom failed: %s\n", SDL_GetError());
		return;
	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, surface);
	if (text == NULL) {
		fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, text, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(text);
}
