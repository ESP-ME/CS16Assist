#pragma once
class UIControlVal
{
private:
	BOOL isCheckInfiniteBullet;
	BOOL isCheckInfiniteLife;
	BOOL isCheckInfiniteMoney;
	BOOL isCheckAcce;
	BOOL isCheckInfiniteGrenade;
public:
	UIControlVal();
	~UIControlVal();
	void setIsCheckInfiniteBullet(BOOL isCheckInfiniteBullet);
	void setIsCheckInfiniteLife(BOOL isCheckInfiniteLife);
	void setIsCheckInfiniteMoney(BOOL isCheckInfiniteMoney);
	void setIsCheckAcce(BOOL isCheckAcce);
	void setIsCheckInfiniteGrenade(BOOL isCheckInfiniteGrenade);
	BOOL getIsCheckInfiniteBullet();
	BOOL getIsCheckInfiniteLife();
	BOOL getIsCheckInfiniteMoney();
	BOOL getIsCheckAcce();
	BOOL getIsCheckInfiniteGrenade();
};

