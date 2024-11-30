#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "cpu.h"
#include "video.h"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

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
	PC = 1024;
	if (argc == 2)
	{
		load_from_file(argv[1], 1024);
	}
	else {exit(-1);}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"VOP CPU (C)",
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

	bool upper = false;
	int counter = 128;
	while (quit == false && IO[POWER_OFF_IO] == 0x00) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}

			if (event.type == SDL_KEYDOWN) {
				SDL_Keycode key = event.key.keysym.sym;
				if (strncmp(SDL_GetKeyName(key), "Left Shift", 1000) == 0) {
					upper = true;
				} else {
					if (upper) {
						switch (key) {
							case '1':
								key = '!';
								break;
							case '2':
								key = '"';
								break;
							case '3':
								key = '#';
								break;
							case '4':
								key = '$';
								break;
							case '5':
								key = '%';
								break;
							case '6':
								key = '^';
								break;
							case '7':
								key = '&';
								break;
							case '8':
								key = '*';
								break;
							case '9':
								key = '(';
								break;
							case '0':
								key = ')';
								break;
							case '-':
								key = '_';
								break;
							case '=':
								key = '+';
								break;
							default:
								key = toupper(key);
						}
						IO[TERMINAL_I] = key;
					}
					else
						IO[TERMINAL_I] = key;
					upper = false;
				}
			}
		}
		
		executeNext();
		
		if (--counter == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);	
			draw_buffer();
			counter = 128;
		}

		if (IO[SWAP_BUFFERS] == 0x01) {
			buffbank = !buffbank;
			IO[SWAP_BUFFERS] = 0;
		} if (IO[TERMINAL]) {
			printf("%c", (char)IO[TERMINAL]);
			fflush(stdout);
			IO[TERMINAL] = 0;
		}
	}

	disable_raw_mode();
	set_blocking_mode();

	display();
	return 0;
}
