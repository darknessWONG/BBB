#ifndef FONT_T_
#define FONT_T_

#include "stdafx.h"

void Font_Initialize(void);
void Font_Finalize(void);
void Font_SetSize(int size);
void Font_SetColor(int r, int g, int b, int a);
void Font_Draw(float x, float y, char * text);
void Font_Draw(float x, float y, float width, float height, char * text);

#endif // !FONT_T_
