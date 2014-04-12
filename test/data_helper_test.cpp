// Ŭnicode please
#include <gtest/gtest.h>
#include <tinyxml.h>
#include "data_helper.h"
#include "class_attribute.h"
#include "class_dict.h"

#include "data_define.h"
#include "data_init.h"
#include "xml_util.h"
#include "stage_header.h"

using namespace std;
using namespace qb;

TEST(DataHelper, test1)
{
	init_generated_data();
	
	DemoStruct_v1 data;
	data.a = 1;
	data.b = 2.0f;
	data.c = true;
	data.d = "asdf";
	data.e = vec2(1, 4);
	data.f.push_back("a");
	data.f.push_back("b");
	data.g.push_back(vec2(2,1));
	data.g.push_back(vec2(4,3));

	TiXmlElement *element = new TiXmlElement("empty");
	DataHelper::DataToXmlNode(&data, element);

	//write as string
	dump_to_stdout(element);

	BaseDataPtr result = DataHelper::XmlNodeToData(element);
	EXPECT_EQ(data.class_hash, result->class_hash);
	EXPECT_EQ(true, DataHelper::Equal(&data, result.get()));
	
}

TEST(DataHelper, Equal)
{
	init_generated_data();

	DemoStruct_v1 data_a;
	data_a.a = 1;
	data_a.b = 2.0f;
	data_a.c = true;
	data_a.d = "asdf";
	data_a.e = vec2(1, 4);
	data_a.f.push_back("a");
	data_a.f.push_back("b");
	data_a.g.push_back(vec2(2,1));
	data_a.g.push_back(vec2(4,3));

	DemoStruct_v2 data_b;
	data_b.c = "asdf";

	DemoStruct_v1 data_c;
	data_c.a = 4;
	data_c.b = 243.0f;
	data_c.c = true;
	data_c.d = "asdf";
	data_c.e = vec2(1, 4);
	data_c.f.push_back("a");
	data_c.g.push_back(vec2(2,1));

	DemoStruct_v1 data_d;
	data_d.a = 1;
	data_d.b = 2.0f;
	data_d.c = true;
	data_d.d = "asdf";
	data_d.e = vec2(1, 4);
	data_d.f.push_back("a");
	data_d.f.push_back("b");
	data_d.g.push_back(vec2(2,1));
	data_d.g.push_back(vec2(4,3));

	EXPECT_EQ(true, DataHelper::Equal(&data_a, &data_a));	//자체 비교
	EXPECT_EQ(false, DataHelper::Equal(&data_a, &data_b));	//다른 타입
	EXPECT_EQ(false, DataHelper::Equal(&data_a, &data_c));	//내용 다름
	EXPECT_EQ(true, DataHelper::Equal(&data_a, &data_d));
}

TEST(DataHelper, Reset)
{
	DemoStruct_v1 data;
	DataHelper::Reset(&data);

	EXPECT_EQ(0, data.a);
	EXPECT_EQ(0, data.b);
	EXPECT_EQ(false, data.c);
	EXPECT_EQ(0, data.d.length());
	EXPECT_EQ(true, vec2(0, 0) == data.e);
	EXPECT_EQ(0, data.f.size());
	EXPECT_EQ(0, data.g.size());
}

TEST(DataHelper, RestGameHeader)
{
	PolyBlockHeader header;
	DataHelper::ResetGameHeader(&header);
	EXPECT_EQ(GetStructType<PolyBlockHeader>(), header.type);

	CoinHeader coin;
	DataHelper::ResetGameHeader(&coin);
	EXPECT_EQ(GetStructType<CoinHeader>(), coin.type);

	BalloonHeader *balloon = new BalloonHeader();
	DataHelper::ResetGameHeader(balloon);
}

TEST(DataHelper, XmlNodeToData)
{
	string xml = "	\
	<PolyBlockHeader_v1 base='PolyBlockHeader' version='1'>	\
      <name>block18</name>	\
	  <polygon>139.523,198.772,146.707,181.387,161.568,181.387,168.571,198.772</polygon>	\
	</PolyBlockHeader_v1>";

	TiXmlDocument doc;
	doc.Parse(xml.c_str());

	BaseDataPtr data = DataHelper::XmlNodeToData(doc.FirstChildElement());
	int type_code = DataHelper::GetStructTypeCode(data.get());
	EXPECT_EQ(PolyBlockHeader_v1::ClassHash(), data->class_hash);
	EXPECT_EQ(PolyBlockHeader_v1::BaseHash(), data->base_hash);
	
	PolyBlockHeader *header = DataHelper::ClassCast<PolyBlockHeader>(data.get());
	ASSERT_EQ(NULL, DataHelper::ClassCast<CoinHeader>(data.get()));	//올바르지 않은거로 캐스팅
	ASSERT_EQ(true, header != NULL);
	EXPECT_STREQ("block18", header->name.c_str());

	EXPECT_EQ(4, header->polygon.size());
	EXPECT_EQ(true, vec2(139.523f, 198.772f) == header->polygon[0]);
	EXPECT_EQ(true, vec2(146.707f, 181.387f) == header->polygon[1]);
	EXPECT_EQ(true, vec2(161.568f, 181.387f) == header->polygon[2]);
	EXPECT_EQ(true, vec2(168.571f, 198.772f) == header->polygon[3]);
}