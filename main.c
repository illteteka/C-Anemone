#include "include.h"

float cameraX = 0;
float cameraY = 0;
float cameraZoom = 1;

float sleep = 0;

SDL_Window* win;
SDL_Renderer* renderer;

SDL_Texture* spr_font;
SDL_Texture* spr_sample_32;

int LEVEL_SWITCH = LEVEL_TEST_1;

void resetCamera()
{
	cameraX = 0;
	cameraY = 0;
	cameraZoom = 1;
}

void loadTextures(SDL_Renderer *renderer)
{
	spr_font = IMG_LoadTexture(renderer, "assets/font.png");
	gfxFontSetTexture(spr_font);
	gfxFontLoadRects();

	spr_sample_32 = IMG_LoadTexture(renderer, "assets/basic.png");
	guySetTexture(spr_sample_32);
}

void destroyTextures()
{
	SDL_DestroyTexture(spr_font);
	SDL_DestroyTexture(spr_sample_32);
}

void load()
{
	devInit();
	inputInit();
}

void updateGame(float dt)
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneUpdate(dt);
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoUpdate(dt);
}

void update(float dt)
{
	devUpdateDebugMenu(dt);

	inputUpdate(dt);

	if (sleep == 0)
		updateGame(dt);
	else
		sleep = fmax(sleep - dt, 0);
}

void drawGame()
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw();
}

void draw(SDL_Renderer *renderer, float fps)
{	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	drawGame();

	devDrawDebugMenu(fps);

	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	// Function implementation
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL2 could not be initialized!\n"
		"SDL2 Error: %s\n",
		SDL_GetError());
	}

	load();

	win = SDL_CreateWindow(
	"window",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	0);

	if (!win)
	{
		printf("Window could not be created!\n"
		"SDL_Error: %s\n",
		SDL_GetError());
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_RenderSetVSync(renderer, 1);
	gfxSetRenderer(renderer);

	loadTextures(renderer);
	
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneInit();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoInit();

	int frames_drawn = 0;
	uint fps_counter = 0;
	float fps = 0.0f;
	uint prev_ticks = SDL_GetTicks();

	int running = 1;
	SDL_Event e;
	while (running)
	{
		float dt = 59.0f/fmax(fps,1.0f);
		if (dt > 10)
		{
			dt = 1;
		}

		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
			}
		}

		update(dt);
		draw(renderer, fps);

		uint ticks_now = SDL_GetTicks();
		uint diff = ticks_now - prev_ticks;
		fps_counter += diff;
		prev_ticks = ticks_now;
		frames_drawn++;

		if(fps_counter >= 1000)
		{
			fps = (float)frames_drawn / (float)(fps_counter/1000.0f);
			frames_drawn = 0;
			fps_counter = 0;
		}
	}

	gfxFontFree();
	destroyTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}