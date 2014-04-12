/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2007      Scott Lembcke
Copyright (c) 2010      Lam Pham

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "custom_CCPointExtension.h"
#include <stdio.h>
#include <algorithm>
#include <cfloat>

namespace   qb {

#define kPointEpsilon FLT_EPSILON

CGFloat
qbpLength(const Point& v)
{
	return sqrtf(qbpLengthSQ(v));
}

CGFloat
qbpDistance(const Point& v1, const Point& v2)
{
	return qbpLength(qbpSub(v1, v2));
}

Point
qbpNormalize(const Point& v)
{
	return qbpMult(v, 1.0f/qbpLength(v));
}

Point
qbpForAngle(const CGFloat a)
{
	return qbp(cosf(a), sinf(a));
}

CGFloat
qbpToAngle(const Point& v)
{
	return atan2f(v.y, v.x);
}

Point qbpLerp(const Point& a, const Point& b, float alpha)
{
	return qbpAdd(qbpMult(a, 1.f - alpha), qbpMult(b, alpha));
}

float clampf(float value, float min_inclusive, float max_inclusive)
{
	if (min_inclusive > max_inclusive) {
		std::swap(min_inclusive, max_inclusive);
	}
	return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
}

Point qbpClamp(const Point& p, const Point& min_inclusive, const Point& max_inclusive)
{
	return qbp(clampf(p.x,min_inclusive.x,max_inclusive.x), clampf(p.y, min_inclusive.y, max_inclusive.y));
}

Point qbpCompOp(const Point& p, float (*opFunc)(float))
{
	return qbp(opFunc(p.x), opFunc(p.y));
}

bool qbpFuzzyEqual(const Point& a, const Point& b, float var)
{
	if(a.x - var <= b.x && b.x <= a.x + var)
		if(a.y - var <= b.y && b.y <= a.y + var)
			return true;
	return false;
}

Point qbpCompMult(const Point& a, const Point& b)
{
	return qbp(a.x * b.x, a.y * b.y);
}

float qbpAngleSigned(const Point& a, const Point& b)
{
	Point a2 = qbpNormalize(a);
    Point b2 = qbpNormalize(b);
	float angle = atan2f(a2.x * b2.y - a2.y * b2.x, qbpDot(a2, b2));
	if( fabs(angle) < kPointEpsilon ) return 0.f;
	return angle;
}

Point qbpRotateByAngle(const Point& v, const Point& pivot, float angle)
{
	Point r = qbpSub(v, pivot);
    float cosa = cosf(angle), sina = sinf(angle);
	float t = r.x;
    r.x = t*cosa - r.y*sina + pivot.x;
    r.y = t*sina + r.y*cosa + pivot.y;
	return r;
}


bool qbpSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D)
{
    float S, T;

    if( qbpLineIntersect(A, B, C, D, &S, &T )
        && (S >= 0.0f && S <= 1.0f && T >= 0.0f && T <= 1.0f) )
        return true;

    return false;
}

Point qbpIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D)
{
    float S, T;

    if( qbpLineIntersect(A, B, C, D, &S, &T) )
    {
        // Point of intersection
        Point P;
        P.x = A.x + S * (B.x - A.x);
        P.y = A.y + S * (B.y - A.y);
        return P;
    }

    return qbp(0, 0);
}

bool qbpLineIntersect(const Point& A, const Point& B, 
					  const Point& C, const Point& D,
					  float *S, float *T)
{
    // FAIL: Line undefined
    if ( (A.x==B.x && A.y==B.y) || (C.x==D.x && C.y==D.y) )
    {
        return false;
    }
    const float BAx = B.x - A.x;
    const float BAy = B.y - A.y;
    const float DCx = D.x - C.x;
    const float DCy = D.y - C.y;
    const float ACx = A.x - C.x;
    const float ACy = A.y - C.y;

    const float denom = DCy*BAx - DCx*BAy;

    *S = DCx*ACy - DCy*ACx;
    *T = BAx*ACy - BAy*ACx;

    if (denom == 0)
    {
        if (*S == 0 || *T == 0)
        { 
            // Lines incident
            return true;   
        }
        // Lines parallel and not incident
        return false;
    }

    *S = *S / denom;
    *T = *T / denom;

    // Point of intersection
    // CGPoint P;
    // P.x = A.x + *S * (B.x - A.x);
    // P.y = A.y + *S * (B.y - A.y);

    return true;
}

float qbpAngle(const Point& a, const Point& b)
{
	float angle = acosf(qbpDot(qbpNormalize(a), qbpNormalize(b)));
	if( fabs(angle) < kPointEpsilon ) return 0.f;
	return angle;
}
}//namespace   cocos2d 
