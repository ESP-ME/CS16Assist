#pragma once

#include "stdafx.h"
#include "HookThread.h"
//#include <windows.h>
//#include<stdio.h>
#include <map>

BOOL isRunHookThread = true;

UINT findMaxValueRetKey(std::map<UINT, UINT> addressNumberMap) {
	UINT findAddress = 0;
	UINT maxValue = 0;

	std::map<UINT, UINT>::iterator iter2 = addressNumberMap.begin();
	for (; iter2 != addressNumberMap.end(); iter2++) {
		UINT key = iter2->first;
		UINT value = iter2->second;
		if (value > maxValue) {
			maxValue = key;
			findAddress = key;
		}
	}

	return findAddress;
}

UINT getBulletAddress() {
	UINT tryNumber = 0;
	std::map<UINT, UINT> addressNumberMap;

	while (tryNumber < 50) {
		tryNumber ++;
		UINT spiritBaseAddrValue = *((UINT *)SPIRIT_BASE_ADDRESS);
		UINT bulletOffsetOne = *((UINT *)(spiritBaseAddrValue + BULLET_OFFSET_ONE));
		if (bulletOffsetOne != 0) {
			UINT bulletOffsetTwo = *((UINT *)(bulletOffsetOne + BULLET_OFFSET_TWO));
			if (bulletOffsetTwo != 0) {
				UINT bulletAddress = bulletOffsetTwo + BULLET_OFFSET_THREE; // �ӵ���ַ
				std::map<UINT, UINT>::iterator iter = addressNumberMap.find(bulletAddress);
				if (iter == addressNumberMap.end()) {
					//�����ڸõ�ַ
					addressNumberMap.insert(std::pair<UINT, UINT>(bulletAddress, 1));
				} else {
				    //���ڸõ�ַ
					UINT oldNumber = addressNumberMap[bulletAddress];
					UINT newNumber = oldNumber;
					iter->second = newNumber;
				}
			}
		}
	}

	return findMaxValueRetKey(addressNumberMap);
}

UINT getLifeAddress() {
	UINT tryNumber = 0;
	std::map<UINT, UINT> addressNumberMap;

	while (tryNumber < 50) {
		tryNumber++;
		UINT spiritBaseAddrValue = *((UINT *)SPIRIT_BASE_ADDRESS);
		UINT lifeOffsetOne = *((UINT *)(spiritBaseAddrValue + LIFE_OFFSET_ONE));
		if (lifeOffsetOne != 0) {
			UINT lifeOffsetTwo = *((UINT *)(lifeOffsetOne + LIFE_OFFSET_TWO));
			if (lifeOffsetTwo != 0) {
				UINT lifeAddress = lifeOffsetTwo + LIFE_OFFSET_THREE;//����ֵ��ַ
				std::map<UINT, UINT>::iterator iter = addressNumberMap.find(lifeAddress);
				if (iter == addressNumberMap.end()) {
					//�����ڸõ�ַ
					addressNumberMap.insert(std::pair<UINT, UINT>(lifeAddress, 1));
				}
				else {
					//���ڸõ�ַ
					UINT oldNumber = addressNumberMap[lifeAddress];
					UINT newNumber = oldNumber;
					iter->second = newNumber;
				}
			}
		}
	}

	return findMaxValueRetKey(addressNumberMap);
}

DWORD WINAPI HookThreadFunc(LPVOID lpPatameter) {
	//UINT spiritBulletAddress = 0;
	//UINT spiritLifeAddress = 0;
	//UINT spiritXAddress = 0;
	//UINT spiritYAddress = 0;
	//UINT spiritZAddress = 0;
	FLOAT lastSpiritX = 0;
	FLOAT lastSpiritY = 0;
	FLOAT lastSpiritZ = 0;
	INT n = 1;//���ٱ���

	while (isRunHookThread) {
		BOOL isCheckInfiniteBullet = controlVal.getIsCheckInfiniteBullet();
		BOOL isCheckInfiniteLife = controlVal.getIsCheckInfiniteLife();
		BOOL isCheckAcce = controlVal.getIsCheckAcce();
		BOOL isCheckInfiniteGrenade = controlVal.getIsCheckInfiniteGrenade();
		UINT spiritBaseAddrValue = *((UINT *)SPIRIT_BASE_ADDRESS);
		if (spiritBaseAddrValue != 0) {
			if (isCheckInfiniteBullet) { //���������ӵ�
				UINT bulletAddress;
				bulletAddress = getBulletAddress();// ��ȡ�ӵ�������ַ
				if (bulletAddress != 0) {
					UINT bulletNumber = *((UINT *)(bulletAddress)); // �ӵ�����
					if (bulletNumber < 90) {
						*((UINT *)(bulletAddress)) = 100;
						//char szBuf[1024] = { 0 };
						//sprintf(szBuf, "�ӵ�����С��90");
						//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
					}
				}
			}

			if (isCheckInfiniteLife) { //������������
				UINT lifeAddress;
				lifeAddress = getLifeAddress();
				FLOAT lifeValue = *((FLOAT *)(lifeAddress));//����ֵ
				if (lifeValue < 100) {
					*((FLOAT *)(lifeAddress)) = 100.0;
					//char szBuf[1024] = { 0 };
					//sprintf(szBuf, "����ֵ����%f", lifeValue);
					//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				}
			}

			if (isCheckAcce) { //�����ƶ�����
				UINT spiritXAddr;
				spiritXAddr = spiritBaseAddrValue + X_OFFSET;
				if (spiritXAddr != 0) {
					FLOAT newSpiritX = *((FLOAT *)(spiritXAddr));
					if (lastSpiritX != 0) {
						if (newSpiritX >= lastSpiritX) {
							if (newSpiritX - lastSpiritX >= 500) {
								continue;
							}
							*((FLOAT *)(spiritXAddr)) = newSpiritX + (newSpiritX - lastSpiritX) * n;
							lastSpiritX = newSpiritX + (newSpiritX - lastSpiritX) * n;
						} else {
							if (lastSpiritX - newSpiritX >= 500) {
								continue;
							}
							*((FLOAT *)(spiritXAddr)) = newSpiritX - (lastSpiritX - newSpiritX) * n;
							lastSpiritX = newSpiritX + (newSpiritX - lastSpiritX) * n;
						}
					} else {
						lastSpiritX = newSpiritX;
					}
				}
				UINT spiritYAddr;
				spiritYAddr = spiritBaseAddrValue + Y_OFFSET;
				if (spiritYAddr != 0) {
					FLOAT newSpiritY = *((FLOAT *)(spiritYAddr));
					if (lastSpiritY != 0) {
						if (newSpiritY >= lastSpiritY) {
							if (newSpiritY - lastSpiritY >= 500) {
								continue;
							}
							*((FLOAT *)(spiritYAddr)) = newSpiritY + (newSpiritY - lastSpiritY) * n;
							lastSpiritY = newSpiritY + (newSpiritY - lastSpiritY) * n;
						}
						else {
							if (lastSpiritY - newSpiritY >= 500) {
								continue;
							}
							*((FLOAT *)(spiritYAddr)) = newSpiritY - (lastSpiritY - newSpiritY) * n;
							lastSpiritY = newSpiritY + (newSpiritY - lastSpiritY) * n;
						}
					} else {
						lastSpiritY = newSpiritY;
					}
				}
				UINT spiritZAddr;
				spiritZAddr = spiritBaseAddrValue + Z_OFFSET;
				if (spiritZAddr != 0) {
					FLOAT newSpiritZ = *((FLOAT *)(spiritZAddr));
				}
			}
		} else {
			lastSpiritX = 0;
			lastSpiritY = 0;
			lastSpiritZ = 0;
		}

		Sleep(10);
	}
	return 0;
}