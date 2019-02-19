#pragma once
#include "stdafx.h"

typedef struct
{
	float a;
	float b;
}line;

typedef struct
{
	float a;
	float b;
	float pointAX;
	float pointBX;
}line_segment;

typedef struct
{
	float left;
	float right;
	float top;
	float bottom;
}RECTF;

typedef struct
{
	float r;
	float center_x;
	float center_y;
}Cycle;

typedef struct
{
	float left;
	float right;
	float bottom;
	float top;
	float front;
	float back;
}BOXF;

enum TouchType
{
	noTouch,
	xTouch,
	yTouch,
	pointTouch,
	cover
};

class Physics
{
public:
	Physics();
	~Physics();

	//Is point in the rect or on the rect's edege 
	static bool pointOnRect(D3DXVECTOR2 point, D3DXVECTOR2* rectPoints);
	//Is point in the rect
	static bool pointInRect(D3DXVECTOR2 point, D3DXVECTOR2* rectPoints);
	//Is point on the rect's edege 
	static bool pointTouchRect(D3DXVECTOR2 point, D3DXVECTOR2* rectPoints);
	//static bool rectInRect(D3DXVECTOR2* rectPoints1, D3DXVECTOR2* rectPoints2);
	static TouchType rectTouchRect(D3DXVECTOR2* rectPoints1, D3DXVECTOR2* rectPoints2);
	static bool pointInCycle(Cycle* cycle, D3DXVECTOR2* point);
	//Is two line intersect
	//if yes, the point of intersection will be save in intersect_point
	//it will return 2 if this two lines are overlap
	static BOOL lineTouchLine(line line1, line line2, D3DXVECTOR2& intersectPoint);
	static BOOL linesegmentTouchLinesegment(line_segment line1, line_segment line2);
	static line createLine(D3DXVECTOR2 point1, D3DXVECTOR2 point2);
	static line_segment createLinesegment(D3DXVECTOR2 point1, D3DXVECTOR2 point2);
	static float round(float src, int bits);

	//it will return a vector which element are the smaller one between a and b
	static D3DXVECTOR3 takeSmallerVaule(D3DXVECTOR3 a, D3DXVECTOR3 b);
	//it will return a vector which element are the bigger one between a and b
	static D3DXVECTOR3 takebiggerVaule(D3DXVECTOR3 a, D3DXVECTOR3 b);
private:
	static void sortLinesegmentPoint(line_segment& line);
};