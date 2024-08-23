#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>

HRESULT Init();
void Uninit();
void Update(float tick);
void Draw();

float GetTick();

#endif // __MAIN_H__