#pragma once
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <time.h>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Player.h"
#include "Enemy.h"
#include "Entity.h"
#include "Effect.h"
#include "defs.h"
#include <list>

class Game {
private:
	int bulletX, bulletY;  // Bullet's position
	int bulletSpeed;  // Bullet speed
	SDL_Texture* bulletTexture;  // Texture for the bullet (if using SDL)

	struct {
		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Texture* background;
		SDL_Texture* titleScreen, * endScreen;
		Mix_Chunk* sounds[soundChannel - 1];
		Mix_Music* music;
		bool running;
	}app;
	struct {
		std::vector <Entity> bullets;
		std::vector <Entity*> fighters;
		std::vector <Entity> powerUp;
		std::vector <Entity> debrises;
		std::vector <std::vector <Effect> > effects;
	}Entities;
	TTF_Font* font;
	std::stringstream healthText, scoreText, hiScoreText;
	std::fstream file;
	Player player;
	Entity playerBullet, enemyBullet, powerUp,debris;
	Enemy* enemy;
	Effect explosion;
	void loadTextures();
	int enemySpawnTimer, enemyFire;
	int lastY;
	int gameTicks;
	void initGameObjects();
	void initSDLTTF();
	void updateScene();
	void updateGameTimers();
	void updateGameTexts();
	bool shouldEndGame() const;
	void endGame();
	void clearEntities();
	void updateHighScore();
	void resetGameScore();
	void initSDLMixer();
	void prepareScene();
	int backgroundX;
	void initSDLImage();
	int score, highScore;
	void createWindowAndRenderer();
	void initSDL();
	void playBackgroundMusic();
	void initGame();
	void initPlayer();
	void titleScreen();
	void endScreen();
	void updateEntities();
	void enterAnimation();
	void getInput();
	void drawBackground();
	void addExplosion(int, int);
	void updateHUD();
	void draw(SDL_Texture*, int, int);
	SDL_Texture* loadTexture(std::string);
	bool detectCollision(int, int, int, int, int, int, int, int);
public:
	void start();
};