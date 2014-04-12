// Ŭnicode please
#include <gtest/gtest.h>
#include "vector.h"

using namespace qb;

TEST(Vector, Length)
{
	Vector2<float> v1(0, 0);
	Vector2<float> v2(3, 4);
	float length_square = VectorLengthSquare(v1 - v2);
	EXPECT_EQ(25, length_square);
	float length = VectorLength(v1 - v2);
	EXPECT_EQ(5.0, length);
}

TEST(Vector, Dot)
{
	Vector2<float> v1(1, 2);
	Vector2<float> v2(3, 4);
	float dot = VectorDot(v1, v2);
	EXPECT_EQ(1*3+2*4, dot);
}

TEST(Vector, EQ_NEQ)
{
	Vector2<float> v1(1, 2);
	Vector2<float> v2(3, 4);
	Vector2<float> v3 = v1;

	EXPECT_EQ(true, v1 == v3);
	EXPECT_EQ(true, v1 != v2);
}

TEST(Vector, BasicOper)
{
	Vector2<float> v1(1, 2);
	Vector2<float> v2(3, 4);

	Vector2<float> tmp;

	//plus
	tmp = v1;
	tmp += v2;
	EXPECT_EQ(4, tmp.x);
	EXPECT_EQ(6, tmp.y);

	tmp = v1 + v2;	//error?

	//minus

	//multi
	tmp = v1 * 2;
	EXPECT_EQ(true, Vector2<float>(2, 4) == tmp);
	
	//div
	tmp = v1 / 0.5;
	EXPECT_EQ(true, Vector2<float>(2, 4) == tmp);
}

TEST(Vector, SetZero)
{
	Vector2<float> v1(1, 2);
	v1.SetZero();
	EXPECT_EQ(true, v1.IsZero());
}

TEST(Vector, Normalize_Normalized)
{
	Vector2<float> v1(2, 0);
	VectorNormalized(v1);
	EXPECT_EQ(1, v1.x);
	EXPECT_EQ(0, v1.y);

	Vector2<float> v2(2, 0);
	Vector2<float> v3 = VectorNormalize(v2);
	EXPECT_EQ(1, v3.x);
	EXPECT_EQ(0, v3.y);
}