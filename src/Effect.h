#pragma once
#include "Entity.h"

class Effect :public Entity {
private:
	int r, g, b, a;
public:
	void setRGBA(int, int, int, int);
	int getR();
	int getG();
	int getB();
	int getA();
	void updateA(int);
};