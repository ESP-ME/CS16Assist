#include "stdafx.h"
#include "Spirit.h"


Spirit::Spirit()
{
}


Spirit::~Spirit()
{
}

void Spirit::setBullet(UINT32 bullet) {
	this->bullet = bullet;
}

void Spirit::setX(FLOAT x) {
	this->x = x;
}

void Spirit::setY(FLOAT y) {
	this->y = y;
}

void Spirit::setZ(FLOAT z) {
	this->z = z;
}

void Spirit::setLifess(FLOAT life) {
	this->life = life;
}

UINT32 Spirit::getBullet() {
	return this->bullet;
}

FLOAT Spirit::getX() {
	return this->x;
}

FLOAT Spirit::getY() {
	return this->y;
}

FLOAT Spirit::getZ() {
	return this->z;
}

FLOAT Spirit::getLife() {
	return this->life;
}
