#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<sstream>
#include<iostream>
#include<string>
#include<cmath>


using namespace std;

void create_window() {

	gWindow = SDL_CreateWindow("pritesh", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 650, SDL_WINDOW_SHOWN);

	if (gWindow == NULL) {
		cout << "tere is an error :" << SDL_GetError() << endl;
	}
	else {
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) {
			cout << "tere is an error in renderer :" << SDL_GetError() << endl;
		}
		else {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
}
void my_Init() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL could not inislize :" << SDL_GetError() << endl;
	}

}
void my_renderTree(int k) {
	for (int i = -k; i < 1400; i += 200) {
		renderQuad = { i, 365,100,200 };
		gTreeTexture.render(renderQuad);
	}
}
void my_render(int k) {
	SDL_SetRenderDrawColor(gRenderer, 135, 206, 235, 0xFF);
	SDL_RenderClear(gRenderer);

	renderQuad = { -k,562,1400,100 };
	gBackgroundTexture.render(renderQuad);

	renderQuad = { 1390 - k,562,1400,100 };
	gBackgroundTexture.render(renderQuad);

	renderQuad = { 650,50,50,50 };
	gSunTexture.render(renderQuad);

	renderQuad = { 10,10,100,50 };
	gTextTexture.render(renderQuad);
	

	my_renderTree(k);

	renderQuad = { x, 465,75,100 };
	gFooTexture.render(renderQuad);

	renderQuad = { 1300, 10,100,30 };
	gTimeTextTexture.render(renderQuad);

	renderQuad = { px, py,50,50 };
	gCoinTexture.render(renderQuad);

	renderQuad = { mox, 400,200,200 };
	gMonsterTexture.render(renderQuad);
}
bool detect_colision(int x, int y) {
	if (px <= -35) {
		return true;
	}
	if ((x + 50 >= px && x <= px + 50) && (y + 50 >= py && y <= py + 50)) {
		s += 10; 
		Mix_PlayChannel(-1, gMedium, 0);
		score = to_string(s);
		gTextTexture.loadFromRenderedText("SCORE :" + score, textColor);
		return true;
	}
	return false;
}
bool detect_mcolision(int x, int y) {
	if (x>mox){
		s -= 100;
		Mix_PlayChannel(-1, gLow, 0);
		score = to_string(s);
		gTextTexture.loadFromRenderedText("SCORE :" + score, textColor);
		activemon = false;
		mox = 1400;
		return true;
	}
	return false;
}