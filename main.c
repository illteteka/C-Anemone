#include "include.h"

float cameraX = 0;
float cameraY = 0;
float cameraZoom = 1;

float rest = 0;

SDL_Window* win;
SDL_Renderer* renderer;

SDL_Texture* spr_font;
SDL_Texture* spr_sample_32;

SDL_Texture* canvas_example;
SDL_Texture* canvas_eraser;

#ifdef __PSP__

#else
	SDL_Texture* canvas_scale;
#endif

int LEVEL_SWITCH = LEVEL_TEST_1;

void resetCamera(void)
{
	cameraX = 0;
	cameraY = 0;
	cameraZoom = 1;
}

void loadTextures(void)
{
	spr_font = IMG_LoadTexture(renderer, "assets/font.png");
	gfxFontSetTexture(spr_font);
	gfxFontLoadRects();

	spr_sample_32 = IMG_LoadTexture(renderer, "assets/basic.png");
	guySetTexture(spr_sample_32);
	brushGuySetTexture(spr_sample_32);

	canvas_example = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 512);
	gfxNewCanvas(canvas_example);

	canvas_eraser = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 512);
	gfxNewCanvas(canvas_eraser);

	#ifdef __PSP__

	#else
		canvas_scale = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 512);
		gfxNewCanvas(canvas_scale);
	#endif
}

void destroyTextures(void)
{
	SDL_DestroyTexture(spr_font);
	SDL_DestroyTexture(spr_sample_32);
	SDL_DestroyTexture(canvas_example);
	SDL_DestroyTexture(canvas_eraser);

	#ifdef __PSP__

	#else
		SDL_DestroyTexture(canvas_scale);
	#endif
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
	bool example_canvas_visible = (LEVEL_SWITCH == LEVEL_TEST_2);

	// Shadow example
	gfxSetColor(0, 0, 0, 64);
	gfxDrawCanvas(canvas_example, 4, 4, example_canvas_visible);

	gfxSetColor(255, 255, 255, 255);
	gfxDrawCanvas(canvas_example, 0, 0, example_canvas_visible);

	gfxDrawCanvas(canvas_eraser, 0, 0, false);

	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw();
}

void draw(float fps)
{	
	#ifdef __PSP__

	#else
		gfxSetCanvas(canvas_scale);
	#endif

	// Clear
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	drawGame();

	devDrawDebugMenu(fps);

	#ifdef __PSP__

	#else
		gfxResetCanvas();
		gfxDrawImage(canvas_scale, 0, 0, 512 * GLOBAL_SCALE, 512 * GLOBAL_SCALE);
	#endif

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

	renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_RenderSetVSync(renderer, 1);

	loadTextures();

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
		draw(fps);

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
