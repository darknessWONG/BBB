#pragma once
#include <d3dx9.h>

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
	static bool rectInRect(D3DXVECTOR2* rectPoints1, D3DXVECTOR2* rectPoints2);
	static TouchType rectTouchRect(D3DXVECTOR2* rectPoints1, D3DXVECTOR2* rectPoints2);
	//Is two line intersect
	//if yes, the point of intersection will be save in intersect_point
	//it will return 2 if this two lines are overlap
	static BOOL lineTouchLine(line line1, line line2, D3DXVECTOR2& intersectPoint);
	static BOOL linesegmentTouchLinesegment(line_segment line1, line_segment line2);

private:
	static void sortLinesegmentPoint(line_segment& line);
};