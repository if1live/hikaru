// Ŭnicode please
#include <gtest/gtest.h>
#include <tinyxml.h>
#include "stage_header.h"
#include "stage_helper.h"
#include "xml_util.h"
#include "data_helper.h"

using namespace std;
using namespace qb;

TEST(StageHelper, read_write)
{
	const char *file = "first.xml";
	FILE *fp = fopen(file, "r");
	if(fp != NULL) {
		ASSERT_EQ(true, fp != NULL);
	
		fseek(fp, 0, SEEK_END);
		int filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *content = (char*)malloc(sizeof(char) * (filesize + 1));
		memset(content, 0, sizeof(char) * (filesize + 1));
		fread(content, sizeof(char), filesize, fp);

		//how to read
		StageHeader stage_header;
		StageHelper helper;
		EXPECT_EQ(true, helper.ReadStage(content, stage_header));

		//how to write
		TiXmlDocument doc = helper.WriteStage(stage_header);
		dump_to_stdout(doc.FirstChildElement());
		doc.Value();
		doc.SaveFile("first_result.xml");

		free(content);
		fclose(fp);
	}
}
/*
TEST(StageHelper, convert_legacy_format)
{
	const char *map_file_list[] = {
		"0316/first.xml",
		"0316/statue2.xml",
		"0316/side_caution3.xml",
		"0316/belowfirst2.xml",
		"0316/white_tuto.xml",
		"0316/white_belowfirst.xml",
		"0316/rope_tuto.xml",
		"0316/rope_white.xml",
		"0316/spike_tuto.xml",
		"0316/rope_spike.xml",
		"0316/asap.xml",
		"0316/balloon_tuto.xml",
		"0316/balloon_easy.xml",
		"0316/switch_tuto_moon.xml",
		"0330/belt0.xml",
		"0330/belt3.xml",
		"0330/belt4.xml",
		"0330/belt2.xml",
		"0330/make_road.xml",
		"0330/balloon_road.xml",
		"0330/split.xml",
		"0330/switch_1.xml",
		"0330/switch_procedure3.xml",
		"0330/switch_procedure.xml",
		"0330/switch_procedure2.xml",
		"0330/switch_floor.xml",
		"0330/belt5.xml",
		"0330/belt1.xml",		
		"0330/bad_tuto.xml",
		"0330/bad0.xml",
		"0330/bad1.xml",
	};

	StageHelper helper;

	size_t map_count = sizeof(map_file_list) / sizeof(map_file_list[0]);
	for(size_t i = 0 ; i < map_count ; i++) {
		string src = "conv/";
		string dst = "conv_result/";
		const char *filename = map_file_list[i];
		src += filename;
		dst += filename;

		FILE *fp = fopen(src.c_str(), "r");
		ASSERT_EQ(true, fp != NULL);
	
		fseek(fp, 0, SEEK_END);
		int filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *content = (char*)malloc(sizeof(char) * (filesize + 1));
		memset(content, 0, sizeof(char) * (filesize + 1));
		fread(content, sizeof(char), filesize, fp);

		//how to read
		StageHeader stage_header;
	
		EXPECT_EQ(true, helper.ReadStage(content, stage_header));

		//how to write
		TiXmlDocument doc = helper.WriteStage(stage_header);
		//dump_to_stdout(doc.FirstChildElement());

		//다시 읽어지나 확인
		StageHeader read_check;
		//helper.ReadStage(doc.FirstChildElement(), read_check);


		doc.SaveFile(dst.c_str());
		free(content);
		fclose(fp);
	}
}*/