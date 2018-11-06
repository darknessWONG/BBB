#include "stdafx.h"
#include "Physics.h"
#include <math.h>


Physics::Physics()
{
}


Physics::~Physics()
{
}

bool Physics::pointOnRect(D3DXVECTOR2 point, D3DXVECTOR2 * rectPoints)
{
	if (pointInRect(point, rectPoints) || pointTouchRect(point, rectPoints))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Physics::pointInRect(D3DXVECTOR2 point, D3DXVECTOR2 * rectPoints)
{
	if (point.x > rectPoints[0].x && point.x < rectPoints[1].x)
	{
		if (point.y > rectPoints[0].y && point.y < rectPoints[3].y)
		{
			return true;
		}
	}
	return false;
}

bool Physics::pointTouchRect(D3DXVECTOR2 point, D3DXVECTOR2 * rectPoints)
{
	if (point.x >= rectPoints[0].x && point.x <= rectPoints[1].x)
	{
		if (point.y == rectPoints[0].y || point.y == rectPoints[3].y)
		{
			return true;
		}
	}
	if (point.x == rectPoints[0].x || point.x == rectPoints[1].x)
	{
		if (point.y >= rectPoints[0].y && point.y <= rectPoints[3].y)
		{
			return true;
		}
	}
	return false;
}

bool Physics::rectInRect(D3DXVECTOR2 * rectPoints1, D3DXVECTOR2 * rectPoints2)
{

	return false;
}

TouchType Physics::rectTouchRect(D3DXVECTOR2 * rectPoints1, D3DXVECTOR2 * rectPoints2)
{
	float lengthx = fabs((rectPoints1[1].x - rectPoints1[0].x) + (rectPoints2[1].x - rectPoints2[0].x));
	float lengthy = fabs((rectPoints1[2].y - rectPoints1[0].y) + (rectPoints2[2].y - rectPoints2[0].y));
	float lx = fabs((rectPoints1[0].x + rectPoints1[1].x) - (rectPoints2[0].x + rectPoints2[1].x));
	float ly = fabs((rectPoints1[0].y + rectPoints1[2].y) - (rectPoints2[0].y + rectPoints2[2].y));

	if (lx < lengthx && ly < lengthy)
	{
		return TouchType::cover;
	}
	else if (lx < lengthx && ly == lengthy)
	{
		return TouchType::yTouch;
	}
	else if (lx == lengthx && ly < lengthy)
	{
		return TouchType::xTouch;
	}
	else if (lx == lengthx && ly == lengthy)
	{
		return TouchType::pointTouch;
	}
	return TouchType::noTouch;
}

BOOL Physics::lineTouchLine(line line1, line line2, D3DXVECTOR2& intersectPoint)
{
	if (line1.a == line2.a)
	{
		if (line1.b == line2.b)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}

	intersectPoint.x = (line2.b - line1.b) / (line1.a - line1.b);
	intersectPoint.y = line1.a * intersectPoint.x + line1.b;

	return TRUE;
}

BOOL Physics::linesegmentTouchLinesegment(line_segment line1, line_segment line2)
{
	D3DXVECTOR2 intersect_point;
	BOOL is_intersect = lineTouchLine(line{ line1.a, line1.b }, line{ line2.a, line2.b }, intersect_point);
	if (is_intersect == 0)
	{
		return FALSE;
	}
	else if (is_intersect == 2)
	{
		return 2;
	}
	else
	{
		sortLinesegmentPoint(line1);
		sortLinesegmentPoint(line2);
		if (intersect_point.x >= line1.pointAX && intersect_point.x <= line1.pointBX
			&& intersect_point.x >= line2.pointAX && intersect_point.x <= line2.pointBX)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

void Physics::sortLinesegmentPoint(line_segment & line)
{
	if (line.pointAX > line.pointBX)
	{
		float tmp = line.pointAX;
		line.pointAX = line.pointBX;
		line.pointBX = tmp;
	}
}
