#pragma once
class Spirit
{
private:
	//人物的子弹
	UINT32 bullet;
	//人物X坐标
	FLOAT x;
	//人物Y坐标
	FLOAT y;
	//人物Z坐标
	FLOAT z;
	//人物的生命值
	FLOAT life;
public:
	Spirit();
	~Spirit();
	void setBullet(UINT32 bullet);
	void setX(FLOAT x);
	void setY(FLOAT y);
	void setZ(FLOAT z);
	void setLifess(FLOAT life);
	UINT32 getBullet();
	FLOAT getX();
	FLOAT getY();
	FLOAT getZ();
	FLOAT getLife();
};

