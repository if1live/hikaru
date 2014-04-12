// Ŭnicode please
#include <gtest/gtest.h>
#include "typelist.h"

#include "data_define.h"
#include "stage_header.h"
#include "data_helper.h"

#include <typeinfo>

using namespace qb;

typedef TYPELIST_3(
	TerrainHeader,
	CheeseHeader,
	PolyBlockHeader
) SampleTypeList;

TEST(TypeList, test)
{
	//typedef TYPELIST_1(int) type1;
	typedef TYPELIST_1(CheeseHeader) type1;
	typedef TYPELIST_2(int, char) type2;
	type1 a;
	type2 b;
}

TEST(TypeList, TypeListLength)
{
	EXPECT_EQ(1, TypeListLength<TYPELIST_1(CheeseHeader)>::value);
	EXPECT_EQ(3, TypeListLength<SampleTypeList>::value);
}

TEST(TypeList, TypeListTypeAt)
{
	typedef TYPELIST_3(int, char, float) type3;
	EXPECT_EQ(typeid(int), typeid(TypeListTypeAt<type3, 0>::Result));
	EXPECT_EQ(typeid(char), typeid(TypeListTypeAt<type3, 1>::Result));
	EXPECT_EQ(typeid(float), typeid(TypeListTypeAt<type3, 2>::Result));
}
/*
template<typename TList>
class EntityTypeGetter;

template<typename T1, typename T2>
struct EntityTypeGetter< TypeList<T1, T2> > {
	typedef T1 LeftNode;
	typedef T2 RightNode;

};

template<class T1>
struct EntityTypeGetter< TypeList<T1, NullType> > {
	typedef T1 LeftNode;
};

TEST(TypeList, a)
{
	

	int a = EntityTypeGetter<SampleTypeList>::LeftNode::ClassHash();
	printf("%d\n", a);
}
*/