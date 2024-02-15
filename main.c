#include "include.h"

float cameraX = 0;
float cameraY = 0;
float cameraZoom = 1;

float rest = 0;

SDL_Window* win;
SDL_Renderer* renderer;

SDL_Texture* spr_font;
SDL_Texture* spr_sample_32;

SDL_Texture *canvas_example;

int LEVEL_SWITCH = LEVEL_TEST_1;

void resetCamera(void)
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
	brushGuySetTexture(spr_sample_32);

	canvas_example = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 512, 512);

	// Clear the new canvas
	//gfxSetCanvas(&canvas_example);
	//gfxSetColor(0, 255, 0, 255); // note: clearing canvas color does nothing on the psp
	//gfxClear();
	//gfxResetCanvas();

	brushSetCanvasTexture(canvas_example);
	levelTestTwoSetCanvasTexture(canvas_example);
}

void destroyTextures(void)
{
	SDL_DestroyTexture(spr_font);
	SDL_DestroyTexture(spr_sample_32);
	SDL_DestroyTexture(canvas_example);
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

	inputUpdate();

	if (rest == 0)
	{
		updateGame(dt);
	}
	else
		rest = fmax(rest - dt, 0);
}

void drawGame(void)
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw();
}

void draw(SDL_Renderer *renderer, float fps)
{	
	gfxSetColor(255, 255, 255, 255);
	gfxClear();
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	drawGame();

	devDrawDebugMenu(fps);

	SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));
	
	// Function implementation
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL2 could not be initialized!\n"
		"SDL2 Error: %s\n",
		SDL_GetError());
	}

	#if defined(__APPLE__) || defined(__linux__)
		SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");

		win = SDL_CreateWindow(
		"anemone alpha",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH * (GLOBAL_SCALE/2),
		SCREEN_HEIGHT * (GLOBAL_SCALE/2),
		SDL_WINDOW_ALLOW_HIGHDPI);
	#elif defined(_WIN64)
		win = SDL_CreateWindow(
		"anemone alpha",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH * GLOBAL_SCALE,
		SCREEN_HEIGHT * GLOBAL_SCALE,
		0);
	#else
		win = SDL_CreateWindow(
		"anemone alpha",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0);
	#endif

	if (!win)
	{
		printf("Window could not be created!\n"
		"SDL_Error: %s\n",
		SDL_GetError());
	}

	devInit();
	inputInit();

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_RenderSetVSync(renderer, 1);
	gfxSetRenderer(renderer);

	loadTextures(renderer);

	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneInit();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoInit();

	int frames_drawn = 0;
	unsigned int fps_counter = 0;
	float fps = 0.0f;
	Uint64 prev_ticks = SDL_GetTicks64();

	int running = 1;
	SDL_Event e;
	while (running)
	{
		float dt = 60.0f/fmax(fps,1.0f);
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

		Uint64 ticks_now = SDL_GetTicks64();
		Uint64 diff = ticks_now - prev_ticks;
		fps_counter += diff;
		prev_ticks = ticks_now;
		frames_drawn++;

		if(fps_counter >= 1000)
		{
			fps = (float)frames_drawn;
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
