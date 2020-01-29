#pragma once
class UIControlVal
{
private:
	BOOL isCheckInfiniteBullet;
	BOOL isCheckInfiniteLife;
	BOOL isCheckAcce;
	BOOL isCheckInfiniteGrenade;
public:
	UIControlVal();
	~UIControlVal();
	void setIsCheckInfiniteBullet(BOOL isCheckInfiniteBullet);
	void setIsCheckInfiniteLife(BOOL isCheckInfiniteLife);
	void setIsCheckAcce(BOOL isCheckAcce);
	void setIsCheckInfiniteGrenade(BOOL isCheckInfiniteGrenade);
	BOOL getIsCheckInfiniteBullet();
	BOOL getIsCheckInfiniteLife();
	BOOL getIsCheckAcce();
	BOOL getIsCheckInfiniteGrenade();
};

