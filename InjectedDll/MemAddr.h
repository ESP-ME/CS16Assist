#pragma once

//�������������ַ(�������Ӣ�ۣ����Ѻ͵���)
#define BASE_ADDRESS 0x02517C64

//Ӣ�ۻ�����ַ
//#define SPIRIT_BASE_ADDRESS 0x025069BC
#define SPIRIT_BASE_ADDRESS (*((UINT *)BASE_ADDRESS) + 0x00004B9C)

//����Ӣ���ӵ�������ַ��ƫ��
#define BULLET_OFFSET_ONE 0x7C
#define BULLET_OFFSET_TWO 0x5EC
#define BULLET_OFFSET_THREE 0xCC

//����Ӣ������ֵ�ĵ�ַ��ƫ����
#define LIFE_OFFSET_ONE 0x7C
#define LIFE_OFFSET_TWO 0x04
#define LIFE_OFFSET_THREE 0x160

//����Ӣ��X����ĵ�ַ��ƫ����
#define X_OFFSET 0x88

//����Ӣ��Y����ĵ�ַ��ƫ����
#define Y_OFFSET 0x8C

//����Ӣ��Z����ĵ�ַ��ƫ����
#define Z_OFFSET 0x90

//����Ӣ�۽�ҵĵ�ַ��ƫ����
#define MONEY_OFFSET_ONE 0x7C
#define MONEY_OFFSET_TWO 0x1CC
#define MONEY_ADDRESS_ADDITIONAL 0x01A1B9FC



