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
		if (point.y < rectPoints[0].y && point.y > rectPoints[3].y)
		{
			return true;
		}
	}
	return false;
}

bool Physics::pointInRect(D3DXVECTOR2 point, RECTF rect)
{
	D3DXVECTOR2* points = createRectPointsFromRECTF(&rect);
	bool result = pointInRect(point, points);
	delete points;
	return result;
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

//bool Physics::rectInRect(D3DXVECTOR2 * rectPoints1, D3DXVECTOR2 * rectPoints2)
//{
//
//	return false;
//}

TouchType Physics::rectTouchRect(D3DXVECTOR2 * rect1, D3DXVECTOR2 * rect2)
{
	D3DXVECTOR2 rectPoints1[4];
	D3DXVECTOR2 rectPoints2[4];
	for (int i = 0; i < 4; i++)
	{
		rectPoints1[i].x = round(rect1[i].x, FLOAT_BITS);
		rectPoints1[i].y = round(rect1[i].y, FLOAT_BITS);
		rectPoints2[i].x = round(rect2[i].x, FLOAT_BITS);
		rectPoints2[i].y = round(rect2[i].y, FLOAT_BITS);

		//rectPoints1[i].x = rect1[i].x;
		//rectPoints1[i].y = rect1[i].y;
		//rectPoints2[i].x = rect2[i].x;
		//rectPoints2[i].y = rect2[i].y;
	}
	float lengthx = fabs((rectPoints1[1].x - rectPoints1[0].x) + (rectPoints2[1].x - rectPoints2[0].x));
	float lengthy = fabs((rectPoints1[2].y - rectPoints1[0].y) + (rectPoints2[2].y - rectPoints2[0].y));
	float lx = fabs((rectPoints1[0].x + rectPoints1[1].x) - (rectPoints2[0].x + rectPoints2[1].x));
	float ly = fabs((rectPoints1[0].y + rectPoints1[2].y) - (rectPoints2[0].y + rectPoints2[2].y));

	lx = round(lx, FLOAT_BITS);
	ly = round(ly, FLOAT_BITS);
	lengthx = round(lengthx, FLOAT_BITS);
	lengthy = round(lengthy, FLOAT_BITS);
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

bool Physics::pointInCycle(Cycle * cycle, D3DXVECTOR2 * point)
{
	//float dis = (point->x - cycle->center_x) * (point->x - cycle->center_x) + (point->y - cycle->center_y) * (point->y - cycle->center_y);
	D3DXVECTOR2 vecDis = D3DXVECTOR2(cycle->center_x, cycle->center_y) - *point;
	float dis = D3DXVec2LengthSq(&vecDis);
	float ra2 = cycle->r * cycle->r;

	if (round(dis, FLOAT_BITS) <= round(ra2, FLOAT_BITS))
	{
		return true;
	}
	return false;
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

	intersectPoint.x = (line2.b - line1.b) / (line1.a - line2.a);
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

line Physics::createLine(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	line li;
	li.a = (point1.y - point2.y) / (point1.x - point2.x);
	li.b = point1.y - li.a * point1.x;
	return li;
}

line_segment Physics::createLinesegment(D3DXVECTOR2 point1, D3DXVECTOR2 point2)
{
	line li = createLine(point1, point2);
	line_segment lis = { li.a, li.b, point1.x, point2.x };

	return lis;
}

float Physics::round(float src, int bits)
{
	stringstream ss;
	ss << fixed << setprecision(bits) << src;
	ss >> src;

	ss.clear();

	return src;
}

D3DXVECTOR2 * Physics::createRectPointsFromRECTF(RECTF const * rect)
{
	D3DXVECTOR2 *points = new D3DXVECTOR2[4]{
		{ rect->left, rect->top },
		{ rect->right, rect->top },
		{ rect->left, rect->bottom },
		{ rect->right, rect->bottom }
	};
	return points;
}

D3DXVECTOR3 Physics::takeSmallerVaule(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	float x = a.x < b.x ? a.x : b.x;
	float y = a.y < b.y ? a.y : b.y;
	float z = a.z < b.z ? a.z : b.z;
	return D3DXVECTOR3(x, y, z);
}

D3DXVECTOR3 Physics::takebiggerVaule(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	float x = a.x > b.x ? a.x : b.x;
	float y = a.y > b.y ? a.y : b.y;
	float z = a.z > b.z ? a.z : b.z;
	return D3DXVECTOR3(x, y, z);
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