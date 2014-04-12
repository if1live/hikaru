// 클nicode please
#include <gtest/gtest.h>
#include <map>
#include <list>
#include <string>
#include "template_lib.h"

using namespace std;
using namespace qb;

class DummyClass {
};

TEST(KKGetDictKeyList, test)
{
	map<string, int> dict;
	dict["a"] = 1;
	dict["fdsfd"] = 2;
	dict["432"] = 2;
	vector<string> keySet;
	GetDictKeyList(dict, keySet);
	EXPECT_EQ(3, (int)keySet.size());
	vector<string>::iterator it = find(keySet.begin(), keySet.end(), string("a"));
	EXPECT_TRUE(it != keySet.end());
	it = find(keySet.begin(), keySet.end(), string("fdsfd"));
	EXPECT_TRUE(it != keySet.end());
	it = find(keySet.begin(), keySet.end(), string("432"));
	EXPECT_TRUE(it != keySet.end());
}

TEST(KKEraseKeyFromAssocContainer, test)
{
	map<int, DummyClass*> dict;
	DummyClass *p1 = new DummyClass();
	DummyClass *p2 = new DummyClass();
	DummyClass *p3 = new DummyClass();
	DummyClass *p4 = new DummyClass();
	DummyClass *p5 = new DummyClass();
	dict[0] = p1;
	dict[1] = p2;
	dict[2] = p3;
	dict[3] = p4;
	dict[4] = p5;
	EXPECT_EQ(5, (int)dict.size());
	
	vector<int> keylist;
	keylist.push_back(1);
	keylist.push_back(3);
	EraseKeyFromAssocContainer(keylist, dict);
	EXPECT_EQ(3, (int)dict.size());
	EXPECT_TRUE(dict.end() == dict.find(1));
	EXPECT_TRUE(dict.end() == dict.find(3));
	
	keylist.push_back(0);
	keylist.push_back(1);
	keylist.push_back(2);
	keylist.push_back(4);
	EraseKeyFromAssocContainer(keylist, dict);
	EXPECT_EQ(0, (int)dict.size());
}
TEST(KKEraseSecondPtrFromAssocContainer, test)
{
	map<int, DummyClass*> dict;
	DummyClass *p1 = new DummyClass();
	DummyClass *p2 = new DummyClass();
	DummyClass *p3 = new DummyClass();
	DummyClass *p4 = new DummyClass();
	DummyClass *p5 = new DummyClass();
	dict[0] = p1;
	dict[1] = p2;
	dict[2] = p3;
	dict[3] = p4;
	dict[4] = p5;
	
	EXPECT_EQ(5, (int)dict.size());
	
	//2,4
	vector<DummyClass*> target;
	target.push_back(p2);
	target.push_back(p4);
	EraseSecondPtrFromAssocContainer(target, dict);
	EXPECT_EQ(3, (int)dict.size());
	EXPECT_TRUE(dict.end() == dict.find(1));
	EXPECT_TRUE(dict.end() == dict.find(3));
	EXPECT_EQ(0, (int)target.size());
	
	//1,3,5
	target.push_back(p1);
	target.push_back(p3);
	target.push_back(p5);
	EraseSecondPtrFromAssocContainer(target, dict);
	EXPECT_EQ(0, (int)dict.size());
}

TEST(IUErasePtrFromSeqContainer, test)
{
	list<DummyClass*> dict;
	DummyClass *p1 = new DummyClass();
	DummyClass *p2 = new DummyClass();
	DummyClass *p3 = new DummyClass();
	DummyClass *p4 = new DummyClass();
	DummyClass *p5 = new DummyClass();
	dict.push_back(p1);
	dict.push_back(p2);
	dict.push_back(p3);
	dict.push_back(p4);
	dict.push_back(p5);
	
	EXPECT_EQ(5, (int)dict.size());
	
	//2,4??젣
	vector<DummyClass*> target;
	target.push_back(p2);
	target.push_back(p4);
	ErasePtrFromSeqContainer(target, dict);
	EXPECT_EQ(3, (int)dict.size());
	EXPECT_TRUE(dict.end() == find(dict.begin(), dict.end(), p2));
	EXPECT_TRUE(dict.end() == find(dict.begin(), dict.end(), p4));
	EXPECT_EQ(0, (int)target.size());
	
	//1,3,5??젣
	target.push_back(p1);
	target.push_back(p3);
	target.push_back(p5);
	ErasePtrFromSeqContainer(target, dict);
	EXPECT_EQ(0, (int)dict.size());
}

TEST(KKSafeDelete, test)
{
	int *a = new int(1);
	SafeDelete(a);
	EXPECT_EQ(true, NULL == a);

	int *b = new int[10];
	SafeDeleteArray(b);
	EXPECT_EQ(true, NULL == b);
}
