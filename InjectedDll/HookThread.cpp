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
				UINT bulletAddress = bulletOffsetTwo + BULLET_OFFSET_THREE; // 子弹地址
				std::map<UINT, UINT>::iterator iter = addressNumberMap.find(bulletAddress);
				if (iter == addressNumberMap.end()) {
					//不存在该地址
					addressNumberMap.insert(std::pair<UINT, UINT>(bulletAddress, 1));
				} else {
				    //存在该地址
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
				UINT lifeAddress = lifeOffsetTwo + LIFE_OFFSET_THREE;//生命值地址
				std::map<UINT, UINT>::iterator iter = addressNumberMap.find(lifeAddress);
				if (iter == addressNumberMap.end()) {
					//不存在该地址
					addressNumberMap.insert(std::pair<UINT, UINT>(lifeAddress, 1));
				}
				else {
					//存在该地址
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
	INT n = 1;//加速倍数

	while (isRunHookThread) {
		BOOL isCheckInfiniteBullet = controlVal.getIsCheckInfiniteBullet();
		BOOL isCheckInfiniteLife = controlVal.getIsCheckInfiniteLife();
		BOOL isCheckAcce = controlVal.getIsCheckAcce();
		BOOL isCheckInfiniteGrenade = controlVal.getIsCheckInfiniteGrenade();
		UINT spiritBaseAddrValue = *((UINT *)SPIRIT_BASE_ADDRESS);
		if (spiritBaseAddrValue != 0) {
			if (isCheckInfiniteBullet) { //开启无限子弹
				UINT bulletAddress;
				bulletAddress = getBulletAddress();// 获取子弹数量地址
				if (bulletAddress != 0) {
					UINT bulletNumber = *((UINT *)(bulletAddress)); // 子弹数量
					if (bulletNumber < 90) {
						*((UINT *)(bulletAddress)) = 100;
						//char szBuf[1024] = { 0 };
						//sprintf(szBuf, "子弹数量小于90");
						//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
					}
				}
			}

			if (isCheckInfiniteLife) { //开启无限生命
				UINT lifeAddress;
				lifeAddress = getLifeAddress();
				FLOAT lifeValue = *((FLOAT *)(lifeAddress));//生命值
				if (lifeValue < 100) {
					*((FLOAT *)(lifeAddress)) = 100.0;
					//char szBuf[1024] = { 0 };
					//sprintf(szBuf, "生命值等于%f", lifeValue);
					//MessageBox(NULL, szBuf, "DLL Inject", MB_OK);
				}
			}

			if (isCheckAcce) { //开启移动加速
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