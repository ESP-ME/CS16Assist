#include "stdafx.h"
#include "UIControlVal.h"


UIControlVal::UIControlVal()
{
}


UIControlVal::~UIControlVal()
{
}

void UIControlVal::setIsCheckInfiniteBullet(BOOL isCheckInfiniteBullet) {
	this->isCheckInfiniteBullet = isCheckInfiniteBullet;
}

void UIControlVal::setIsCheckInfiniteLife(BOOL isCheckInfiniteLife) {
	this->isCheckInfiniteLife = isCheckInfiniteLife;
}
void UIControlVal::setIsCheckInfiniteMoney(BOOL isCheckInfiniteMoney) {
	this->isCheckInfiniteMoney = isCheckInfiniteMoney;
}
void UIControlVal::setIsCheckAcce(BOOL isCheckAcce) {
	this->isCheckAcce = isCheckAcce;
}

void UIControlVal::setIsCheckInfiniteGrenade(BOOL isCheckInfiniteGrenade) {
	this->isCheckInfiniteGrenade = isCheckInfiniteGrenade;
}

BOOL UIControlVal::getIsCheckInfiniteBullet() {
	return this->isCheckInfiniteBullet;
}

BOOL UIControlVal::getIsCheckInfiniteLife() {
	return this->isCheckInfiniteLife;
}
BOOL UIControlVal::getIsCheckInfiniteMoney() {
	return this->isCheckInfiniteMoney;
}
BOOL UIControlVal::getIsCheckAcce() {
	return this->isCheckAcce;
}

BOOL UIControlVal::getIsCheckInfiniteGrenade() {
	return this->isCheckInfiniteGrenade;
}