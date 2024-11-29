#include "Game.h"
using namespace std;
int frameCount = 0;
float fps = 0.0f;
Uint32 lastTime = 0, currentTime;


void Game::start() {
	initGame();
	while (true) {
		titleScreen();
		while (app.running) {
			if (player.enterStatus() == false) {
				enterAnimation();
				continue;
			}
			prepareScene();
			drawBackground();
			if (player.getHP() > 0) {
				getInput();
			}
			updateEntities();
			updateHUD();
			updateScene();
		}
	}
}

void Game::titleScreen() {
	SDL_Event e;
	while (true) {
		app.music = Mix_LoadMUS(bgSound);
		drawBackground();
		draw(app.titleScreen, 0, 0);
		updateScene();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					initPlayer();
					app.running = true;
					Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
					exit(0);
				}

			}
		}
	}
}

void Game::endScreen() {
	SDL_Event e;
	bool input = true;
	scoreText << "Puntaje  : " << score;
	while (true) {
		drawBackground();
		draw(app.endScreen, 0, 0);
		SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), { 255, 255, 255, 0 });
		SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);
		draw(scoreTXT, 0, 0);
		updateScene();
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					initPlayer();
					app.running = true;
					Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
					return;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					Mix_PlayChannel(CH_MENU, app.sounds[SOUND_BUTTON], 0);
					return;
				}
				break;
			}
		}
	}
}

void Game::enterAnimation() {
	prepareScene();
	drawBackground();
	player.setX(player.getX() - 15);
	draw(player.getTexture(), player.getX(), player.getY());
	if (player.getX() < 150) {
		player.setEnterStatus(true);
	}
	updateScene();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void Game::initGame() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "No se inicializo SDL: " << SDL_GetError() << endl;
		exit(-1);
	}
	app.window = SDL_CreateWindow("ROGUECHNO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!app.window) {
		cout << "No se creo la ventana : " << SDL_GetError() << endl;
		exit(-1);
	}
	SDL_Surface* sf = IMG_Load(icon);
	SDL_SetWindowIcon(app.window, sf);
	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	if (!app.renderer) {
		cout << "No nse posible crear el render : " << SDL_GetError() << endl;
		exit(-1);
	}
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
		cout << "No se inicializo SDL Image : " << SDL_GetError() << endl;
		exit(-1);
	}
	if (TTF_Init() != 0) {
		cout << "No se inicializo SDL TTF : " << TTF_GetError() << endl;
		exit(-1);
	}
	font = TTF_OpenFont("resources/fonts/myriadProRegular.ttf", 22);
	score = 0;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
		cout << "No se inicializo SDL Mixer : " << Mix_GetError() << endl;
		exit(-1);
	}
	Mix_AllocateChannels(soundChannel);
	app.music = Mix_LoadMUS(bgSound);
	app.sounds[SOUND_FIRE] = Mix_LoadWAV(fireSound);
	app.sounds[SOUND_EXPLOSION] = Mix_LoadWAV(explosionSound);
	app.sounds[SOUND_BUTTON] = Mix_LoadWAV(btSound);

	app.background = loadTexture(backgroundTexture);
	backgroundX = 0;
	app.titleScreen = loadTexture(titleScreenTexture);
	app.endScreen = loadTexture(endScreenTexture);

	app.running = false;

	file.open("resources/docs/scores.txt", ios::in);
	file >> highScore;

	enemySpawnTimer = 60;

	player.setIdentity(pPlane);
	player.setTexture(loadTexture(playerTexture));

	playerBullet.setDX(playerBulletSpeed);
	playerBullet.updateHP(bulletHP);
	playerBullet.setIdentity(normalBullet);
	playerBullet.setTexture(loadTexture(shootGunBulletTexture));

	enemyBullet.setDX(enemyBulletSpeed);
	enemyBullet.setHP(1);
	enemyBullet.setIdentity(eBullet);
	enemyBullet.setTexture(loadTexture(enemyBulletTexture));
	enemyFire = 0;

	debris.setHP(1);

	explosion.setTexture(loadTexture(explosionTexture));

	Mix_PlayMusic(app.music, -1);
	gameTicks = 0;
}
*/

//////////////////////////////////////////////Refactorizado//////////////////////////////////////////////

void Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Error al inicializar SDL: " << SDL_GetError() << endl;
        exit(-1);
    }
}

void Game::createWindowAndRenderer() {
    app.window = SDL_CreateWindow("ROGUECHNO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!app.window) {
        cerr << "Error al crear la ventana: " << SDL_GetError() << endl;
        exit(-1);
    }
    SDL_Surface* sf = IMG_Load(icon);
    SDL_SetWindowIcon(app.window, sf);

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
    if (!app.renderer) {
        cerr << "Error al crear el renderizador: " << SDL_GetError() << endl;
        exit(-1);
    }
}

void Game::initSDLImage() {
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))) {
        cerr << "Error al inicializar SDL Image: " << IMG_GetError() << endl;
        exit(-1);
    }
}

void Game::initSDLTTF() {
    if (TTF_Init() != 0) {
        cerr << "Error al inicializar SDL TTF: " << TTF_GetError() << endl;
        exit(-1);
    }
    font = TTF_OpenFont("resources/fonts/myriadProRegular.ttf", 22);
    if (!font) {
        cerr << "Error al cargar la fuente: " << TTF_GetError() << endl;
        exit(-1);
    }
}

void Game::initSDLMixer() {
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
        cerr << "Error al inicializar SDL Mixer: " << Mix_GetError() << endl;
        exit(-1);
    }
    Mix_AllocateChannels(soundChannel);

    app.music = Mix_LoadMUS(bgSound);
    app.sounds[SOUND_FIRE] = Mix_LoadWAV(fireSound);
    app.sounds[SOUND_EXPLOSION] = Mix_LoadWAV(explosionSound);
	int volumeExplosion = 40;
	Mix_VolumeChunk(app.sounds[SOUND_EXPLOSION], volumeExplosion);
    app.sounds[SOUND_BUTTON] = Mix_LoadWAV(btSound);
}

void Game::loadTextures() {
    app.background = loadTexture(backgroundTexture);
    app.titleScreen = loadTexture(titleScreenTexture);
    app.endScreen = loadTexture(endScreenTexture);

    player.setTexture(loadTexture(playerTexture));
    playerBullet.setTexture(loadTexture(shootGunBulletTexture));
    enemyBullet.setTexture(loadTexture(enemyBulletTexture));
    explosion.setTexture(loadTexture(explosionTexture));
}

void Game::initGameObjects() {
    score = 0;
    enemySpawnTimer = 60;

    player.setIdentity(pPlane);
    playerBullet.setDX(playerBulletSpeed);
    playerBullet.updateHP(bulletHP);
    playerBullet.setIdentity(normalBullet);

    enemyBullet.setDX(enemyBulletSpeed);
    enemyBullet.setHP(1);
    enemyBullet.setIdentity(eBullet);

    debris.setHP(1);

    app.running = false;

    file.open("resources/docs/scores.txt", ios::in);
    file >> highScore;
}

void Game::playBackgroundMusic() {
    if (Mix_PlayMusic(app.music, -1) == -1) {
        cerr << "Error al reproducir música de fondo: " << Mix_GetError() << endl;
    }
}

void Game::initGame() {
    initSDL();
    createWindowAndRenderer();
    initSDLImage();
    initSDLTTF();
    initSDLMixer();
    loadTextures();
    initGameObjects();
    playBackgroundMusic();
    gameTicks = 0;
}
//////////////se separaron en funciones mas pequenias para que cada una realice una tarea en especifico

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::initPlayer() {
	player.setX(WIDTH / 2);
	player.setY(HEIGHT / 2 - 50);
	player.setHP(10);
	player.setDieStatus(false);
	player.setEnterStatus(false);
	player.setBulletType(normalBullet);
	player.resetInput();
}

void Game::getInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYUP:
			player.keyUp(&e.key);
			break;
		case SDL_KEYDOWN:
			player.keyDown(&e.key);
			break;
		}
	}
}

void Game::updateEntities() {
	if (player.getHP() > 0) {
		player.move();
		draw(player.getTexture(), player.getX(), player.getY());
	}

	if (player.fireStatus() == true && player.getReload() == 0) {
		if (player.getAmmo() == 0) {
			player.setBulletType(normalBullet);
		}
		switch (player.getBulletType()) {
		case normalBullet:
			playerBullet.setIdentity(normalBullet);
			playerBullet.setTexture(loadTexture(normalBulletTexture));
			playerBullet.setX(player.getX() + 50);
			playerBullet.setY(player.getY() + 45);
			playerBullet.setDX(playerBulletSpeed);
			player.setReload(5);
			Entities.bullets.push_back(playerBullet);
			break;
		case shootGunBullet:
			for (int i = 0; i < 5; ++i) {
				playerBullet.setIdentity(shootGunBullet);
				playerBullet.setTexture(loadTexture(shootGunBulletTexture));
				playerBullet.setX(player.getX() + 50);
				playerBullet.setY(player.getY() + 45 + (i - 2) * 10);
				playerBullet.setDX(playerBulletSpeed);
				Entities.bullets.push_back(playerBullet);
			}
			player.setReload(15);
			if (player.getAmmo() == 0) {
				player.updateAmmo(10);
				player.setBulletType(normalBullet);
				player.setReload(5);
			}
			else {
				player.updateAmmo(-1);
			}
			break;
		}
		Mix_PlayChannel(CH_PLAYER, app.sounds[SOUND_FIRE], 0);
	}

	if (enemySpawnTimer == 0) {
		enemy = new Enemy();
		enemy->setX(WIDTH - 80);
		enemy->setDX(enemySpeed);
		enemy->setTexture(loadTexture(enemyTexture));
		enemy->setHP(gameTicks / 1000 + 5);
		enemyBullet.setHP(1);
		enemySpawnTimer = 40;
		srand(time(NULL));
		if (rand() % 100 < 30) {
			cout << "Enemigo Normal" << endl;
			enemy->setIdentity(ePlane);
		}
		else {
			cout << "Enemigo Shootgun" << endl;
			enemy->setIdentity(ePlane2);
		}
		int y = rand() % HEIGHT;
		while (abs(y - lastY) < 200 || y + 105 > HEIGHT) {
			y = rand() % HEIGHT;
		}
		lastY = y;
		enemy->setY(y);
		Entities.fighters.push_back(enemy);
	}

	for (auto i = Entities.bullets.begin(); i != Entities.bullets.end(); ) {
		if (i->getX() > WIDTH || i->getX() < 0 || i->getHP() <= 0) {
			i = Entities.bullets.erase(i);
			continue;
		}

		switch (i->getIdentity()) {
		case shootGunBullet:
			i->setDY(15 * sin(gameTicks * 0.5 * 3.14 / 5));
			break;
		}

		i->move();

		if (i != Entities.bullets.end()) {
			draw(i->getTexture(), i->getX(), i->getY());
		}

		i++;
	}

	for (auto i = Entities.fighters.begin(); i != Entities.fighters.end(); ) {
		if ((*i)->getX() <= 0) {
			i = Entities.fighters.erase(i);
		}
		else if ((*i)->getHP() <= 0) {
			Mix_PlayChannel(CH_OTHER, app.sounds[SOUND_EXPLOSION], 0);
			addExplosion((*i)->getX(), ((*i)->getY()));

			(*i)->move();

			srand(time(NULL));
			int drop = rand() % 100;
			if (drop < 40) {
				int type = rand() % 2;
				switch (type) {
				case 0:
					powerUp.setIdentity(bonusHP);
					powerUp.setTexture(loadTexture(bonusHPTexture));
					break;
				case 1:
					powerUp.setIdentity(shootGunBullet);
					powerUp.setTexture(loadTexture(enchanceAttackTexture));
					break;
				}
				powerUp.setX((*i)->getX());
				powerUp.setY((*i)->getY());
				powerUp.setDX(rand() % 2 == 1 ? powerUpSPD : -powerUpSPD);
				powerUp.setDY(rand() % 2 == 1 ? powerUpSPD : -powerUpSPD);
				Entities.powerUp.push_back(powerUp);
			}
			score += 5 + gameTicks / 500;
			i = Entities.fighters.erase(i);
		}
		else {
			int w, h, wP, hP;
			Enemy* p = dynamic_cast<Enemy*>(*i);
			SDL_QueryTexture((*i)->getTexture(), NULL, NULL, &w, &h);
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);
			if (detectCollision((*i)->getX(), (*i)->getY(), w, h, player.getX(), player.getY(), wP, hP)) {
				player.updateHP(-2);
				(*i)->updateHP(-5);
			}

			int num = rand() % 200;
			p->updateTicks();
			if (num < 5 && p->getChangeMovement() == false) {
				if (p->getIdentity() == ePlane) {
					p->setIdentity(ePlane2);
				}
				else {
					p->setIdentity(ePlane);
				}
				p->setChangeMovement(true);
			}
			if (p->getIdentity() == ePlane2) {
				p->setDY(5 * sin(p->getTIcks() * 0.5 * 3.14 / 15));
			}
			else {
				p->setDY(0);
			}
			(*i)->move();
			if (p->getReload() == 0) {
				p->setReload((75 - gameTicks / 1000 < 30 ? 30 : 75 - gameTicks / 1000));
				enemyBullet.setX((*i)->getX() - 50);
				enemyBullet.setY((*i)->getY() + 35);

				switch (p->getIdentity()) {
				case ePlane:
					Entities.bullets.push_back(enemyBullet);
					break;

				case ePlane2:
					for (int offset = -15; offset <= 15; offset += 15) {
						enemyBullet.setY((*i)->getY() + 35 + offset);
						Entities.bullets.push_back(enemyBullet);
					}
					break;
				}
			}
			else {
				p->setReload(p->getReload() - 1);
			}
			draw((*i)->getTexture(), (*i)->getX(), (*i)->getY());
			i++;
		}
	}

	for (auto i = Entities.powerUp.begin(); i != Entities.powerUp.end(); ) {
		int powerUpW, powerUpH, playerW, playerH;
		SDL_QueryTexture(i->getTexture(), NULL, NULL, &powerUpW, &powerUpH);
		SDL_QueryTexture(player.getTexture(), NULL, NULL, &playerW, &playerH);
		if (detectCollision(i->getX(), i->getY(), powerUpW, powerUpH, player.getX(), player.getY(), playerW, playerH)) {
			switch (i->getIdentity()) {
			case bonusHP:
				player.updateHP(1);
				break;
			case shootGunBullet:
				player.setBulletType(shootGunBullet);
				player.updateAmmo(5);
				break;
			}
			score += 25;
			i = Entities.powerUp.erase(i);
		}
		else {

			if (i->getX() <= 0) {
				i->setDX(powerUpSPD);
			}
			if (i->getX() >= WIDTH - powerUpW) {
				i->setDX(-powerUpSPD);
			}
			if (i->getY() <= 0) {
				i->setDY(powerUpSPD);
			}
			if (i->getY() >= HEIGHT - powerUpH) {
				i->setDY(-powerUpSPD);
			}
			i->move();
			draw(i->getTexture(), i->getX(), i->getY());
			i++;
		}
	}

	for (auto i = Entities.effects.begin(); i != Entities.effects.end(); ) {
		bool remove = false;
		for (auto j = i->begin(); j != i->end(); j++) {
			if (j->getA() <= 0) {
				remove = true;
				break;
			}
			SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
			SDL_SetTextureBlendMode(j->getTexture(), SDL_BLENDMODE_ADD);
			SDL_SetTextureColorMod(j->getTexture(), j->getR(), j->getG(), j->getB());
			SDL_SetTextureAlphaMod(j->getTexture(), j->getA());
			draw(j->getTexture(), j->getX(), j->getY());
			j->updateA(-15);
		}
		if (remove) {
			i = Entities.effects.erase(i);
		}
		else {
			i++;
		}
	}

	for (auto& bullet : Entities.bullets) {
		int w1, h1;
		SDL_QueryTexture(bullet.getTexture(), NULL, NULL, &w1, &h1);
		for (auto j = Entities.fighters.begin(); j != Entities.fighters.end(); j++) {
			if ((*j)->getHP() <= 0) {
				continue;
			}

			int w2, h2, wP, hP;
			SDL_QueryTexture((*j)->getTexture(), NULL, NULL, &w2, &h2);
			SDL_QueryTexture(player.getTexture(), NULL, NULL, &wP, &hP);

			if (detectCollision(bullet.getX(), bullet.getY(), w1, h1, (*j)->getX(), (*j)->getY(), w2, h2) && bullet.getDX() > 0) {
				bullet.updateHP(-1);
				(*j)->updateHP(-1);
			}


			if (detectCollision(bullet.getX(), bullet.getY(), w1, h1, player.getX(), player.getY(), wP, hP) && bullet.getIdentity() == eBullet) {
				player.updateHP(-1);
				bullet.setHP(0);
				break;

			}

		}
	}

	Entities.bullets.erase(
		std::remove_if(
			Entities.bullets.begin(),
			Entities.bullets.end(),
			[](const auto& b) { return b.getHP() <= 0; }
		),
		Entities.bullets.end()
	);


	if (player.getHP() <= 0 && !player.died()) {

		Mix_PlayChannel(CH_OTHER, app.sounds[SOUND_EXPLOSION], 0);
		addExplosion(player.getX(), player.getY());
		player.setDieStatus(true);
	}


}


void Game::drawBackground() {
	int w, h;
	SDL_QueryTexture(app.background, NULL, NULL, &w, &h);
	if (-w > --backgroundX) {
		backgroundX = 0;
	}
	draw(app.background, backgroundX, 0);
	draw(app.background, backgroundX + w, 0);
}

void Game::addExplosion(int x, int y) {
	explosion.setX(x - 20);
	explosion.setY(y);
	explosion.setDX(0);
	explosion.setDY(0);
	std::vector <Effect> temp;
	for (int j = 0; j < 15; j++) {
		switch (rand() % 4) {
		case 0:
			explosion.setRGBA(255, 255, 0, 200);
			break;
		case 1:
			explosion.setRGBA(255, 0, 0, 200);
			break;
		case 2:
			explosion.setRGBA(255, 128, 0, 200);
			break;
		case 3:
			explosion.setRGBA(255, 255, 255, 200);
			break;
		}
		temp.push_back(explosion);
	}
	Entities.effects.push_back(temp);
}

void Game::updateHUD() {
	healthText << "Salud : " << player.getHP();
	scoreText << "Puntaje   : " << score;
	hiScoreText << "Mejor Puntaje : " << highScore;
	SDL_Surface* lifeSurface = TTF_RenderText_Solid(font, healthText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* lifeTXT = SDL_CreateTextureFromSurface(app.renderer, lifeSurface);
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* scoreTXT = SDL_CreateTextureFromSurface(app.renderer, scoreSurface);
	SDL_Surface* hsSurface = TTF_RenderText_Solid(font, hiScoreText.str().c_str(), { 255, 255, 255, 0 });
	SDL_Texture* hsTXT = SDL_CreateTextureFromSurface(app.renderer, hsSurface);
	draw(lifeTXT, 0, 0);
	draw(scoreTXT, 0, 20);
	draw(hsTXT, 0, 40);
}

void Game::prepareScene() {
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderClear(app.renderer);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void Game::updateScene() {
	if (app.running) {
		if (enemySpawnTimer > 0) {
			enemySpawnTimer--;
		}
		enemyFire++;
		if (player.getReload() > 0) {
			player.setReload(player.getReload() - 1);
		}
		gameTicks++;
		healthText.str(std::string());
		scoreText.str(std::string());
		hiScoreText.str(std::string());
	}
	if (player.getHP() <= 0 && Entities.effects.empty() && app.running) {
		Entities.bullets.clear();
		Entities.debrises.clear();
		Entities.fighters.clear();
		Entities.powerUp.clear();
		app.running = false;
		if (score > highScore) {
			highScore = score;
			file.close();
			file.open("resources/docs/scores.txt", ios::out);
			file << highScore;
		}
		endScreen();
		score = 0;
	}
	SDL_RenderPresent(app.renderer);
	SDL_Delay(40);
}
*/

//////////////////////////////////////////////////Refactorizado/////////////////////////////////////////////////////////////////////////////////
void Game::updateScene() {
    if (app.running) {
        updateGameTimers();
        updateGameTexts();
    }

    if (shouldEndGame()) {
        endGame();
    }

    SDL_RenderPresent(app.renderer);
    SDL_Delay(40);
}

void Game::updateGameTimers() {
    if (enemySpawnTimer > 0) {
        enemySpawnTimer--;
    }
    enemyFire++;
    if (player.getReload() > 0) {
        player.setReload(player.getReload() - 1);
    }
    gameTicks++;
}

void Game::updateGameTexts() {
    healthText.str(std::string());
    scoreText.str(std::string()); 
    hiScoreText.str(std::string()); 
}

bool Game::shouldEndGame() const {
    return player.getHP() <= 0 && Entities.effects.empty() && app.running;
}

void Game::endGame() {
    clearEntities();
    app.running = false;

    if (score > highScore) {
        updateHighScore();
    }

    endScreen();
    resetGameScore();
}

void Game::clearEntities() {
    Entities.bullets.clear();
    Entities.debrises.clear();
    Entities.fighters.clear();
    Entities.powerUp.clear();
}

void Game::updateHighScore() {
    highScore = score;
    file.close();
    file.open("resources/docs/scores.txt", ios::out);
    file << highScore;
}

void Game::resetGameScore() {
    score = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture* Game::loadTexture(std::string path) {
	SDL_Texture* texture = IMG_LoadTexture(app.renderer, path.c_str());
	if (texture == NULL) {
		cout << "Error loading image : " << IMG_GetError() << endl;
		exit(-1);
	}
	return texture;
}

void Game::draw(SDL_Texture* texture, int x, int y) {
	SDL_Rect target;
	target.x = x;
	target.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &target.w, &target.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &target);
}

bool Game::detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}