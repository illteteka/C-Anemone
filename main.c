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

#ifdef __PSP__

#else
	SDL_Texture *canvas_scale;
#endif

int LEVEL_SWITCH = LEVEL_TEST_1;

int test_x = 0;
int test_y = 0;
int test_w = 0;
int test_h = 0;

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

	// create canvas
	/*
	[0] = SDL_PIXELFORMAT_ABGR8888, //first
    [1] = SDL_PIXELFORMAT_ARGB8888,
            */
	canvas_example = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 512);

	// clear this canvas
	//SDL_SetColorKey(canvas_example, SDL_TRUE, SDL_MapRGB(canvas_example->format, 255, 0, 0));
	
	SDL_SetTextureBlendMode(canvas_example, SDL_BLENDMODE_BLEND);

	SDL_SetRenderTarget(renderer, canvas_example);

	//SDL_SetTextureBlendMode(canvas_example, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureAlphaMod(canvas_example, 255);


	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);

	// Clear the new canvas
	//gfxSetCanvas(&canvas_example);
	//gfxSetColor(0, 255, 0, 255); // note: clearing canvas color does nothing on the psp
	//gfxClear();
	//gfxResetCanvas();

	//brushSetCanvasTexture(canvas_example);
	//levelTestTwoSetCanvasTexture(canvas_example);

	#ifdef __PSP__

	#else
		canvas_scale = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 512, 512);
		SDL_SetRenderTarget(renderer, canvas_scale);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, NULL);
	#endif
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
	gfxSetColor(0, 0, 255, 255);
	gfxRectangle(10, 10, 100, 100);
	gfxDrawImage(canvas_example, test_x, test_y, test_w, test_h);

	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw();
}

void draw(float fps)
{	
	#ifdef __PSP__

	#else
		SDL_SetRenderTarget(renderer, canvas_scale);
	#endif

	//gfxSetColor(255, 255, 255, 255);
	//gfxClear();
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Clear
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	drawGame();

	devDrawDebugMenu(fps);

	#ifdef __PSP__

	#else
		SDL_SetRenderTarget(renderer, NULL);
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
