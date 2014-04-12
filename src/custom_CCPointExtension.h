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

#pragma once
/**
 @file
 Point extensions based on Chipmunk's cpVect file.
 These extensions work both with Point and cpVect.
 
 The "qbp" prefix means: "CoCos2d Point"
 
 Examples:
  - qbpAdd( qbp(1,1), qbp(2,2) ); // preferred cocos2d way
  - qbpAdd( PointMake(1,1), PointMake(2,2) ); // also ok but more verbose
  
  - cpvadd( cpv(1,1), cpv(2,2) ); // way of the chipmunk
  - qbpAdd( cpv(1,1), cpv(2,2) ); // mixing chipmunk and cocos2d (avoid)
  - cpvadd( PointMake(1,1), PointMake(2,2) ); // mixing chipmunk and CG (avoid)
 */

#include "custom_CCGeometry.h"

#include <math.h>
namespace   qb {

/** Helper macro that creates a Point
 @return Point
 @since v0.7.2
 */
#define qbp(__X__,__Y__) qb::PointMake((float)(__X__), (float)(__Y__))

/** Returns opposite of point.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpNeg(const Point& v)
{
	return qbp(-v.x, -v.y);
}

/** Calculates sum of two points.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpAdd(const Point& v1, const Point& v2)
{
	return qbp(v1.x + v2.x, v1.y + v2.y);
}

/** Calculates difference of two points.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpSub(const Point& v1, const Point& v2)
{
	return qbp(v1.x - v2.x, v1.y - v2.y);
}

/** Returns point multiplied by given factor.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpMult(const Point& v, const CGFloat s)
{
	return qbp(v.x*s, v.y*s);
}

/** Calculates midpoint between two points.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpMidpoint(const Point& v1, const Point& v2)
{
	return qbpMult(qbpAdd(v1, v2), 0.5f);
}

/** Calculates dot product of two points.
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
qbpDot(const Point& v1, const Point& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

/** Calculates cross product of two points.
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
qbpCross(const Point& v1, const Point& v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
 @return Point
 @since v0.7.2
 */
static inline Point
qbpPerp(const Point& v)
{
	return qbp(-v.y, v.x);
}

/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
 @return Point
 @since v0.7.2
 */
static inline Point
qbpRPerp(const Point& v)
{
	return qbp(v.y, -v.x);
}

/** Calculates the projection of v1 over v2.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpProject(const Point& v1, const Point& v2)
{
	return qbpMult(v2, qbpDot(v1, v2)/qbpDot(v2, v2));
}

/** Rotates two points.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpRotate(const Point& v1, const Point& v2)
{
	return qbp(v1.x*v2.x - v1.y*v2.y, v1.x*v2.y + v1.y*v2.x);
}

/** Unrotates two points.
 @return Point
 @since v0.7.2
 */
static inline Point
qbpUnrotate(const Point& v1, const Point& v2)
{
	return qbp(v1.x*v2.x + v1.y*v2.y, v1.y*v2.x - v1.x*v2.y);
}

/** Calculates the square length of a Point (not calling sqrt() )
 @return CGFloat
 @since v0.7.2
 */
static inline CGFloat
qbpLengthSQ(const Point& v)
{
	return qbpDot(v, v);
}

/** Calculates distance between point an origin
 @return CGFloat
 @since v0.7.2
 */
CGFloat qbpLength(const Point& v);

/** Calculates the distance between two points
 @return CGFloat
 @since v0.7.2
 */
CGFloat qbpDistance(const Point& v1, const Point& v2);

/** Returns point multiplied to a length of 1.
 @return Point
 @since v0.7.2
 */
Point qbpNormalize(const Point& v);

/** Converts radians to a normalized vector.
 @return Point
 @since v0.7.2
 */
Point qbpForAngle(const CGFloat a);

/** Converts a vector to radians.
 @return CGFloat
 @since v0.7.2
 */
CGFloat qbpToAngle(const Point& v);


/** Clamp a value between from and to.
 @since v0.99.1
 */
float clampf(float value, float min_inclusive, float max_inclusive);

/** Clamp a point between from and to.
 @since v0.99.1
 */
Point qbpClamp(const Point& p, const Point& from, const Point& to);


/** Run a math operation function on each point component
 * absf, fllorf, ceilf, roundf
 * any function that has the signature: float func(float);
 * For example: let's try to take the floor of x,y
 * qbpCompOp(p,floorf);
 @since v0.99.1
 */
Point qbpCompOp(const Point& p, float (*opFunc)(float));

/** Linear Interpolation between two points a and b
 @returns
	alpha == 0 ? a
	alpha == 1 ? b
	otherwise a value between a..b
 @since v0.99.1
 */
Point qbpLerp(const Point& a, const Point& b, float alpha);


/** @returns if points have fuzzy equality which means equal with some degree of variance.
 @since v0.99.1
 */
bool qbpFuzzyEqual(const Point& a, const Point& b, float variance);


/** Multiplies a nd b components, a.x*b.x, a.y*b.y
 @returns a component-wise multiplication
 @since v0.99.1
 */
Point qbpCompMult(const Point& a, const Point& b);

/** @returns the signed angle in radians between two vector directions
 @since v0.99.1
 */
float qbpAngleSigned(const Point& a, const Point& b);

/** @returns the angle in radians between two vector directions
 @since v0.99.1
*/
float qbpAngle(const Point& a, const Point& b);

/** Rotates a point counter clockwise by the angle around a pivot
 @param v is the point to rotate
 @param pivot is the pivot, naturally
 @param angle is the angle of rotation cw in radians
 @returns the rotated point
 @since v0.99.1
 */
Point qbpRotateByAngle(const Point& v, const Point& pivot, float angle);

/** A general line-line intersection test
 @param p1 
	is the startpoint for the first line P1 = (p1 - p2)
 @param p2 
	is the endpoint for the first line P1 = (p1 - p2)
 @param p3 
	is the startpoint for the second line P2 = (p3 - p4)
 @param p4 
	is the endpoint for the second line P2 = (p3 - p4)
 @param s 
	is the range for a hitpoint in P1 (pa = p1 + s*(p2 - p1))
 @param t
	is the range for a hitpoint in P3 (pa = p2 + t*(p4 - p3))
 @return bool 
	indicating successful intersection of a line
	note that to truly test intersection for segments we have to make 
	sure that s & t lie within [0..1] and for rays, make sure s & t > 0
	the hit point is		p3 + t * (p4 - p3);
	the hit point also is	p1 + s * (p2 - p1);
 @since v0.99.1
 */
bool qbpLineIntersect(const Point& p1, const Point& p2, 
					  const Point& p3, const Point& p4,
					  float *s, float *t);

/*
qbpSegmentIntersect returns YES if Segment A-B intersects with segment C-D
@since v1.0.0
*/
bool qbpSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D);

/*
qbpIntersectPoint returns the intersection point of line A-B, C-D
@since v1.0.0
*/
Point qbpIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D);

}//namespace   cocos2d 
