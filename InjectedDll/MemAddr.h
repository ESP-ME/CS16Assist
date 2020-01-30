#pragma once

//所有人物基础地址(人物包括英雄，朋友和敌人)
#define BASE_ADDRESS 0x02517C64

//英雄基础地址
//#define SPIRIT_BASE_ADDRESS 0x025069BC
#define SPIRIT_BASE_ADDRESS (*((UINT *)BASE_ADDRESS) + 0x00004B9C)

//控制英雄子弹数量地址的偏移
#define BULLET_OFFSET_ONE 0x7C
#define BULLET_OFFSET_TWO 0x5EC
#define BULLET_OFFSET_THREE 0xCC

//控制英雄生命值的地址的偏移量
#define LIFE_OFFSET_ONE 0x7C
#define LIFE_OFFSET_TWO 0x04
#define LIFE_OFFSET_THREE 0x160

//控制英雄X坐标的地址的偏移量
#define X_OFFSET 0x88

//控制英雄Y坐标的地址的偏移量
#define Y_OFFSET 0x8C

//控制英雄Z坐标的地址的偏移量
#define Z_OFFSET 0x90

//控制英雄金币的地址的偏移量
#define MONEY_OFFSET_ONE 0x7C
#define MONEY_OFFSET_TWO 0x1CC
#define MONEY_ADDRESS_ADDITIONAL 0x01A1B9FC



