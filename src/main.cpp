#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "cpu.h"
#include<fcntl.h>
#include<termios.h>
#include<unistd.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

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

void draw_char(int x, int y, uint8_t c) {
	// c is the character code in video_ram, which maps to an index in the console_font_8x8 array
	uint8_t *char_bitmap = &console_font_8x8[c * 8];

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int py = 0; py < 8; ++py) {
		for (int px = 0; px < 8; ++px) {
			if (char_bitmap[py] & (1 << (7 - px))) {
				SDL_RenderDrawPoint(renderer, x + px, y + py);
			}
		}
	}
}

void draw_buffer() {
	int i = 0;
	for (int y = 0; y < SCREEN_HEIGHT; y += 8) {
		for (int x = 0; x < SCREEN_WIDTH; x += 8) {
			uint8_t c = video_ram[i++];
			draw_char(x, y, c);
		}
	}

	SDL_RenderPresent(renderer);
}

// Enable raw mode (non-canonical, no echo)
void enable_raw_mode() {
	struct termios termios_p;
	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
}

// Function to reset terminal back to normal mode
void disable_raw_mode() {
	struct termios termios_p;
	tcgetattr(STDIN_FILENO, &termios_p); // Get current terminal settings
	termios_p.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p); // Apply settings
}

// Make stdin non-blocking
void set_nonblocking_mode() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // Set non-blocking flag
}

// Reset stdin to blocking mode
void set_blocking_mode() {
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK); // Clear non-blocking flag
}

int main(int argc, char* argv[]) {
	VOP cpu(0, 512);
	if (argc == 2)
	{
		cpu.load_from_file(argv[1], 512);
	}
	else {exit(-1);}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"VOP CPU",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH*SCREEN_SCALE, SCREEN_HEIGHT*SCREEN_SCALE, SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	if (screenSurface == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "could not create surface: %s\n", SDL_GetError());
  		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		printf("Renderer could not be created!\nSDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	bool quit = false;
	SDL_Event event;

	enable_raw_mode();
	set_nonblocking_mode();

	char c;
	while (quit == false && cpu.IO[POWER_OFF_IO] == 0x00) {
		int n = 0;
		n = read(STDIN_FILENO, &c, 1);
		
		if (n == 1) {
			cpu.IO[TERMINAL_I] = c;
		}

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);	
		cpu.executeNext();
		draw_buffer();
		
		if (cpu.IO[SWAP_BUFFERS] == 0x01) {
			buffbank = !buffbank;
			cpu.IO[SWAP_BUFFERS] = 0;
		} if (cpu.IO[TERMINAL])
		{
			std::cout << (char)cpu.IO[TERMINAL];
			cpu.IO[TERMINAL] = 0;
		}
	}

	disable_raw_mode();
	set_blocking_mode();

	cpu.display();
	return 0;
}
