#pragma once
class Spirit
{
private:
	//������ӵ�
	UINT32 bullet;
	//����X����
	FLOAT x;
	//����Y����
	FLOAT y;
	//����Z����
	FLOAT z;
	//���������ֵ
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

