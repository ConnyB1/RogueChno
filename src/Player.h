#pragma once
#include <SDL.h>
#include "Entity.h"

class Player :public Entity {
private:
	int speed, reload;
	bool up, down, left, right, fire;
	bool bulletType;
	bool enterGame;
	bool die;
	int ammo;
	bool isBoosting;
	int boostSpeed;
	int speedBoostDuration;
public:
	Player();
	void move();
	void keyDown(SDL_KeyboardEvent*);
	void keyUp(SDL_KeyboardEvent*);
	void updateAmmo(int);
	void setReload(int);
	void setBulletType(int);
	void setEnterStatus(bool);
	void setDieStatus(bool);
	int getAmmo();
	int getReload();
	int getBulletType();
	bool fireStatus();
	bool enterStatus();
	bool died();
	void resetInput();
	void speedBoost(int duration);
	void setBoosting(bool boosting);
	bool getBoosting();
};