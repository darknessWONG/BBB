#ifndef SPRITE_H_
#define SPRITE_H_

#include "stdafx.h"

void Sprite_Draw(int texture_index, float dx, float dy);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th,float cx, float cy, float sx, float sy, int radian);

void Sprite_Draw_Background(int texture_index);
void Sprite_Draw_Background(int texture_index, float moveX, float moveY);

void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, D3DXCOLOR color);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th, D3DXCOLOR color);

void Sprite_SetColor(D3DCOLOR color);

#endif  // SPRITE_H_