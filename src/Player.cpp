#include "Player.h"
#include <iostream>

Player::Player() {
	up = left = down = right = fire = die = false;
	reload = 0;
	speed = 10;
	bulletType = ammo = enterGame = 0;
	isBoosting = false;
	boostSpeed = speed * 1.5;
}
/*
void Player::move() {
	int currentSpeed = speed;

	if (isBoosting) {
		currentSpeed = boostSpeed;
	}


	if (up && left) {
		dx = dy = -currentSpeed;
	}
	else if (up && right) {
		dx = currentSpeed;
		dy = -currentSpeed;
	}
	else if (down && left) {
		dx = -currentSpeed;
		dy = currentSpeed;
	}
	else if (down && right) {
		dx = dy = currentSpeed;
	}
	else if (up) {
		dy = -currentSpeed;
	}
	else if (down) {
		dy = currentSpeed;
	}
	else if (left) {
		dx = -currentSpeed;
	}
	else if (right) {
		dx = currentSpeed;
	}
	x = (x + dx < 0 ? 0 : (x + dx > 950 ? 950 : x + dx));
	y = (y + dy < 0 ? 0 : (y + dy > 396 ? 396 : y + dy));
	dx = dy = 0;

}
*/


template <typename T>
T clamp(const T& value, const T& min, const T& max) {
	return (value < min) ? min : (value > max) ? max : value;
}

void Player::move() {
	int currentSpeed = isBoosting ? boostSpeed : speed;

	dx = 0;
	dy = 0;

	if (up) dy = -currentSpeed;
	if (down) dy = currentSpeed;
	if (left) dx = -currentSpeed;
	if (right) dx = currentSpeed;

	if ((up || down) && (left || right)) {
		dx = (dx > 0) ? currentSpeed : (dx < 0 ? -currentSpeed : dx);
		dy = (dy > 0) ? currentSpeed : -currentSpeed;
	}

	x = clamp(x + dx, 0, 950);
	y = clamp(y + dy, 0, 396);

	dx = dy = 0;
}

void Player::keyDown(SDL_KeyboardEvent* event) {
	if (!(event->repeat)) {
		switch (event->keysym.scancode) {
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			up = true;
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			down = true;
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			left = true;
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			right = true;
			break;
		case SDL_SCANCODE_SPACE:
			fire = true;
			break;
		case SDL_SCANCODE_LSHIFT:
			isBoosting = true;
			break;
		}
	}
}

void Player::keyUp(SDL_KeyboardEvent* event) {
	if (!(event->repeat)) {
		switch (event->keysym.scancode) {
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			up = false;
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			down = false;
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			left = false;
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			right = false;
			break;
		case SDL_SCANCODE_SPACE:
			fire = false;
			break;
		case SDL_SCANCODE_LSHIFT:
			isBoosting = false;
			break;
		}
	}
}

void Player::updateAmmo(int ammo) {
	this->ammo += ammo;
}

void Player::setReload(int reload) {
	this->reload = reload;
}

void Player::setBulletType(int type) {
	this->bulletType = type;
}

void Player::setEnterStatus(bool status) {
	this->enterGame = status;
}

void Player::setDieStatus(bool status) {
	this->die = status;
}

int Player::getAmmo() {
	return ammo;
}

int Player::getReload() {
	return reload;
}

int Player::getBulletType() {
	return bulletType;
}

bool Player::fireStatus() {
	return fire;
}

bool Player::enterStatus() {
	return enterGame;
}

bool Player::died() {
	return die;
}

void Player::resetInput() {
	left = up = right = down = fire = false;
}

void Player::setBoosting(bool boosting) {
	isBoosting = boosting;
}

bool Player::getBoosting() {
	return isBoosting;
}

void Player::speedBoost(int duration) {
	speedBoostDuration = duration * 60;
	speed *= 2;
}