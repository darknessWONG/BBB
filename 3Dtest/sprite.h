#ifndef SPRITE_H_
#define SPRITE_H_

#include "stdafx.h"

// dx とは表示の広さ
// dy とは表示の高さ
// tx とは切ったテクスチャの始まる場所の広さ
// ty とは切ったテクスチャの始まる場所の高さ
// tw とは切ったテクスチャの広さ
// th とは切ったテクスチャの高さ
// radian とは回転の角度
// color とはDiffuseの色

// 普通のスプライト　- サイズがスプライトファイルと同じになる
void Sprite_Draw(int texture_index, float dx, float dy);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th,float cx, float cy, float sx, float sy, int radian);

// 背景としてのスプライト
void Sprite_Draw_Background(int texture_index);
void Sprite_Draw_Background(int texture_index, float moveX, float moveY);			// moveX moveYとはUVの動く値
void Sprite_Draw_Background(int texture_index, int tx, int ty, int tw, int th);

// サイズが設定できるスプライト
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, D3DXCOLOR color);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th, D3DXCOLOR color);

// 基本のDiffuse色を設定する
void Sprite_SetColor(D3DCOLOR color);

#endif  // SPRITE_H_