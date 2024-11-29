#pragma once
#include "Entity.h"

class Enemy :public Entity {
private:
	int reload;
	int ticks;
	bool changeMovement;
public:
	Enemy();
	void setReload(int);
	void setChangeMovement(bool);
	void updateTicks();
	int getReload();
	bool getChangeMovement();
	int getTIcks();
};