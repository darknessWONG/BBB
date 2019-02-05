#ifndef SPRITE_H_
#define SPRITE_H_

#include "stdafx.h"

// dx �Ƃ͕\���̍L��
// dy �Ƃ͕\���̍���
// tx �Ƃ͐؂����e�N�X�`���̎n�܂�ꏊ�̍L��
// ty �Ƃ͐؂����e�N�X�`���̎n�܂�ꏊ�̍���
// tw �Ƃ͐؂����e�N�X�`���̍L��
// th �Ƃ͐؂����e�N�X�`���̍���
// radian �Ƃ͉�]�̊p�x
// color �Ƃ�Diffuse�̐F

// ���ʂ̃X�v���C�g�@- �T�C�Y���X�v���C�g�t�@�C���Ɠ����ɂȂ�
void Sprite_Draw(int texture_index, float dx, float dy);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th);
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th,float cx, float cy, float sx, float sy, int radian);

// �w�i�Ƃ��ẴX�v���C�g
void Sprite_Draw_Background(int texture_index);
void Sprite_Draw_Background(int texture_index, float moveX, float moveY);			// moveX moveY�Ƃ�UV�̓����l
void Sprite_Draw_Background(int texture_index, int tx, int ty, int tw, int th);

// �T�C�Y���ݒ�ł���X�v���C�g
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, D3DXCOLOR color);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th);
void Sprite_Draw_Size(int texture_index, float dx, float dy, int sx, int sy, int tx, int ty, int tw, int th, D3DXCOLOR color);

// ��{��Diffuse�F��ݒ肷��
void Sprite_SetColor(D3DCOLOR color);

#endif  // SPRITE_H_