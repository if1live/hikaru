#if 0
// Ŭnicode please
#include "stage_read_policy_v02.h"
#include <vector>
#include <string>
#include "qbunit.h"
#include "Box2D.h"
#include "tinyxml.h"
#include "stage_header.h"
#include "vector.h"
#include "data_helper.h"

using namespace std;
using namespace qb;

enum {
	kNoneScoreBlock,
	kScoreBlock,
	kBadBlock,
};

//컴포넌트 적용 전의 맵포맷을 읽기위한 용도
//이전에 짜여진 코드를 재탕하기 위해서 스크립트 대신 c를 썼다.
//테스트케이스같은데 끼워넣고 돌려서 변환해서 뽑으면 될듯

void StageReadPolicy_v02::Read(TiXmlElement *root, StageHeader &stage)
{
	if(StageHelper::GetValue(root)=="stage") {
		string versionStr = StageHelper::GetAttribute(root,"version");
		if(versionStr != "0.2")
		{
			assert(false);//version 오류
		}
		TiXmlElement *stage_elem = root->FirstChildElement();
		while(stage_elem) {
			//stage Properties
			string elem_value = StageHelper::GetValue(stage_elem);
			if(elem_value=="properties") {
				ReadStageProperties(stage_elem,&stage);
			}
			else if(elem_value=="layers") {
				ReadLayers(stage_elem,&stage);
			}
			else {				
			}
			stage_elem = stage_elem->NextSiblingElement();
		}
	}
}
	
void StageReadPolicy_v02::ReadStageProperties(TiXmlElement *elem,StageHeader *stage)
{
	assert(StageHelper::GetValue(elem)=="properties");
	float height = 480;
	float width = 320;
	float start_x = 0;
	float start_y = 0;
	std::string background("back01.png");
	TiXmlElement *property_elem = elem->FirstChildElement();
	while(property_elem) {
		assert(StageHelper::GetValue(property_elem)=="property");
		string name = StageHelper::GetAttribute(property_elem,"name");
		if(name == "height") {
			const char *value = property_elem->Attribute("value");
			height = (float)atof(value);
		} else if(name == "width") {
			const char *value = property_elem->Attribute("value");
			width = (float)atof(value);
		} else if(name == "start_x") {
			const char *value = property_elem->Attribute("value");
			start_x = (float)atof(value);
		} else if(name == "start_y") {
			const char *value = property_elem->Attribute("value");
			start_y = (float)atof(value);
		} else if(name == "background") {
			const char *value = property_elem->Attribute("value");
			background = string(value);
		} else {
		}
		property_elem = property_elem->NextSiblingElement();
	}
	stage->height = height;
	stage->width = width;
	stage->qbu_initial_pos_x = start_x;
	stage->qbu_initial_pos_y = start_y;
	stage->background = background;
}


void StageReadPolicy_v02::ReadLayers(TiXmlElement *elem,StageHeader *stage)
{
	TiXmlElement *layer_elem = elem->FirstChildElement();
	while(layer_elem) {
		if(StageHelper::GetValue(layer_elem)=="layer") {
			if(StageHelper::GetAttribute(layer_elem,"type")=="block_layer") {
				TiXmlElement *block_layer_elem = layer_elem->FirstChildElement();
				while(block_layer_elem)	{
					string value = StageHelper::GetValue(block_layer_elem);
					if(value=="block")	{
						stage->entities.push_back(ReadBlock(block_layer_elem));					
					} else if(value=="spike") {
						stage->entities.push_back(ReadSpike(block_layer_elem));
					} else if(value=="balloon") {
						stage->entities.push_back(ReadBalloon(block_layer_elem));
					} else if(value=="movable_block") {
						stage->entities.push_back(ReadMovableBlock(block_layer_elem));
					} else if(value=="candy") {
						stage->entities.push_back(ReadCandy(block_layer_elem));
					} else if(value=="dispenser") {
						stage->entities.push_back(ReadDispenser(block_layer_elem));
					} else if(value=="physical_object") {
						stage->entities.push_back(ReadPhysicalObject(block_layer_elem));
					} else if(value=="fixed_block") {
						stage->entities.push_back(ReadFixedBlock(block_layer_elem));
					} else if(value=="floor") {
						stage->entities.push_back(ReadFloor(block_layer_elem));	
					} else if(value=="belt") {
						stage->entities.push_back(ReadBelt(block_layer_elem));
					} else {
					}
					block_layer_elem = block_layer_elem->NextSiblingElement();
				}
			} else if(StageHelper::GetAttribute(layer_elem,"type")=="joint_layer") {
				TiXmlElement *joint_layer_elem = layer_elem->FirstChildElement();
				while(joint_layer_elem) {
					string value = StageHelper::GetValue(joint_layer_elem);
					if(value=="properties") {
					} else if(value=="joint") {
						stage->entities.push_back(ReadJoint(joint_layer_elem));
					} else 	{
					}
					joint_layer_elem = joint_layer_elem->NextSiblingElement();
				}

			} else if(StageHelper::GetAttribute(layer_elem,"type") == "comment_layer") {
				TiXmlElement *comment_layer_elem = layer_elem->FirstChildElement();
				while(comment_layer_elem) {
					string value = StageHelper::GetValue(comment_layer_elem);
					if(value=="comment") {
						stage->comments.push_back(ReadComment(comment_layer_elem));
					}
					comment_layer_elem = comment_layer_elem->NextSiblingElement();
				}			
			} else {
			}
		}
		layer_elem = layer_elem->NextSiblingElement();
	}

}

BaseDataPtr StageReadPolicy_v02::ReadBlock(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="block");
	TiXmlElement *block_elem = elem->FirstChildElement();
	
	bool is_dynamic = true;
	bool is_score = false;
	bool is_sliceable = true;
	int score_type = kNoneScoreBlock;
	//string texture_file;
	float pos_qbu_x = 0;
	float pos_qbu_y = 0;

	vector<qb::vec2> polygon;
	string block_name;
	while(block_elem) {
		if(StageHelper::GetValue(block_elem)=="properties") {
			TiXmlElement *property_elem = block_elem->FirstChildElement();
			
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "score_type") {
					string value = StageHelper::GetAttribute(property_elem,"value");
					if(value.at(0) == 'n' || value.at(0) == 'N') {
						score_type = kNoneScoreBlock;
					} else if(value.at(0) == 's' || value.at(0) == 'S') {
						score_type = kScoreBlock;
					} else if(value.at(0) == 'b' || value.at(0) == 'B') {
						score_type = kBadBlock;
					} else {
					}
				}
				else if(name == "is_score") {
					string att_value = StageHelper::GetAttribute(property_elem,"value");
					is_score = StageHelper::ReadBool(att_value,is_score);
					if(is_score) {
						score_type = kScoreBlock;
					}
				} else if(name == "is_bad") {
					string att_value = StageHelper::GetAttribute(property_elem,"value");
					bool is_bad = StageHelper::ReadBool(att_value, false);
					if(is_bad) {
						score_type = kBadBlock;
					}
				} else if(name == "is_sliceable") {
					string att_value = StageHelper::GetAttribute(property_elem,"value");
					is_sliceable = StageHelper::ReadBool(att_value,is_sliceable);
				} else if(name == "name") {
					block_name = StageHelper::GetAttribute(property_elem,"value");
				} else if(name == "is_dynamic") {
					string value = StageHelper::GetAttribute(property_elem,"value");
					is_dynamic = StageHelper::ReadBool(value,true);
				} else if(name == "texture_file") {
					/*string value = GetAttribute(property_elem, "value");
					texture_file = value;*/

				} else if(name == "pos_qbu_x") {
					string value = StageHelper::GetAttribute(property_elem, "value");
					pos_qbu_x = (float)atof(value.c_str());

				} else if(name == "pos_qbu_y") {
					string value = StageHelper::GetAttribute(property_elem, "value");
					pos_qbu_y = (float)atof(value.c_str());

				} else {
					//IUASSERT(!"maybe not valid");
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		else if(StageHelper::GetValue(block_elem)=="polygon") {
			TiXmlElement *point_elem = block_elem->FirstChildElement();
			while(point_elem) {
				assert(StageHelper::GetValue(point_elem)=="point");
				float x = atof(point_elem->Attribute("x"));
				float y = atof(point_elem->Attribute("y"));
				polygon.push_back(qb::vec2(x,y));

				point_elem = point_elem->NextSiblingElement();
			}
		}
		block_elem = block_elem->NextSiblingElement();
	}
	
	
	/*TerritoryHeader territory;
	territory.territory_type = kDrawingTerritory;
	territory.polygon_qbu = polygon;*/

	if(is_dynamic)//dynamic일경우 polyblock
	{
		PolyBlockHeader *block = new PolyBlockHeader();
		DataHelper::ResetGameHeader(block);

		//block->territory = territory;
		block->polygon = polygon;
		block->name = block_name;

		BaseDataPtr ptr(block);
		return ptr;
	} else {
		TerrainHeader *terrain = new TerrainHeader();
		DataHelper::ResetGameHeader(terrain);

		//bezier 로 폴리곤 표현하기위해 3번씩 집어넘
		/*for(auto it = polygon.begin();it!=polygon.end();it++)
		{
			terrain->bezier.push_back(*it);
			terrain->bezier.push_back(*it);
			terrain->bezier.push_back(*it);
		}*/
		terrain->points = polygon;
		
		terrain->name = block_name;
		//terrain->physics_body_name = "";
		terrain->texture_file = "pattern/rubber.png";

		BaseDataPtr ptr(terrain);
		return ptr;
	}
	//block->texture_file = texture_file;
}

BaseDataPtr StageReadPolicy_v02::ReadSpike(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="spike");
	qb::vec2 pos_a;
	qb::vec2 pos_b;

	const char *x_a_str = elem->Attribute("x_a");
	const char *y_a_str = elem->Attribute("y_a");
	const char *x_b_str = elem->Attribute("x_b");
	const char *y_b_str = elem->Attribute("y_b");
	pos_a.x = atof(x_a_str);
	pos_a.y = atof(y_a_str);
	pos_b.x = atof(x_b_str);
	pos_b.y = atof(y_b_str);
	string spike_name;

	TiXmlElement *spike_elem = elem->FirstChildElement();
	while(spike_elem) {
		if(StageHelper::GetValue(spike_elem)=="properties") {
			TiXmlElement *property_elem = spike_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "name") {
					spike_name = StageHelper::GetAttribute(property_elem,"value");
				} else {

				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		spike_elem = spike_elem->NextSiblingElement();
	}

	SpikeHeader *spike = new SpikeHeader();
	DataHelper::ResetGameHeader(spike);
	spike->pos_a_qbu = pos_a;
	spike->pos_b_qbu = pos_b;
	spike->name = spike_name;
	return BaseDataPtr(spike);
}

BaseDataPtr StageReadPolicy_v02::ReadBalloon(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="balloon");
	qb::vec2 pos;

	const char *x_str = elem->Attribute("x");
	const char *y_str = elem->Attribute("y");
	pos.x = atof(x_str);
	pos.y = atof(y_str);
	string object_name;
	
	TiXmlElement *balloon_elem = elem->FirstChildElement();
	while(balloon_elem) {
		if(StageHelper::GetValue(balloon_elem)=="properties") {
			TiXmlElement *property_elem = balloon_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else {

				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		balloon_elem = balloon_elem->NextSiblingElement();
	}


	BalloonHeader *balloon = new BalloonHeader();
	DataHelper::ResetGameHeader(balloon);
	balloon->pos_qbu = pos;
	balloon->name = object_name;
	return BaseDataPtr(balloon);
}
BaseDataPtr StageReadPolicy_v02::ReadBelt(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem) == "belt");
	qb::vec2 pos;
	float width = 128;
	float angle = 0;
	float initial_speed_qbups = 0;
	string object_name;

	const char *x_str = elem->Attribute("pos_x");
	const char *y_str = elem->Attribute("pos_y");
	pos.x = atof(x_str);
	pos.y = atof(y_str);

	TiXmlElement *belt_elem = elem->FirstChildElement();
	while(belt_elem) {
		if(StageHelper::GetValue(belt_elem)=="properties") {
			TiXmlElement *property_elem = belt_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else if(name == "width") {
					width = atof(property_elem->Attribute("value"));
				} else if(name == "angle") {
					angle = atof(property_elem->Attribute("value"));
				} else if(name == "initial_speed_qbups") {
					initial_speed_qbups = atof(property_elem->Attribute("value"));
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		belt_elem = belt_elem->NextSiblingElement();
	}
	BeltHeader *belt = new BeltHeader();
	DataHelper::ResetGameHeader(belt);
	belt->angle_deg = angle;
	belt->width_qbu = width;
	belt->name = object_name;
	belt->x_qbu = pos.x;
	belt->y_qbu = pos.y;
	belt->initial_speed_qbups = initial_speed_qbups;

	return BaseDataPtr(belt);

}
BaseDataPtr StageReadPolicy_v02::ReadFloor(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="floor");
	qb::vec2 pos;

	const char *x_str = elem->Attribute("pos_x");
	const char *y_str = elem->Attribute("pos_y");
	pos.x = atof(x_str);
	pos.y = atof(y_str);

	string object_name;
	float width = 32;
	float height = 32;
	float angle = 0;
	TiXmlElement *floor_elem = elem->FirstChildElement();
	while(floor_elem) {
		if(StageHelper::GetValue(floor_elem)=="properties") {
			TiXmlElement *property_elem = floor_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else if(name == "width") {
					width = atof(property_elem->Attribute("value"));
				} else if(name == "height") {
					height = atof(property_elem->Attribute("value"));
				} else if(name == "angle") {
					angle = atof(property_elem->Attribute("value"));
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		floor_elem = floor_elem->NextSiblingElement();
	}
	FloorHeader *floor = new FloorHeader();
	DataHelper::ResetGameHeader(floor);
	floor->angle_deg = angle;
	floor->height_qbu = height;
	floor->width_qbu = width;
	floor->name = object_name;
	floor->x_qbu = pos.x;
	floor->y_qbu = pos.y;

	return BaseDataPtr(floor);
}

BaseDataPtr StageReadPolicy_v02::ReadCandy(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem) == "candy");
	std::string body_name = elem->Attribute("body_name");
	float x = atof(elem->Attribute("x"));
	float y = atof(elem->Attribute("y"));

	TiXmlElement *candy_elem = elem->FirstChildElement();

	bool flip;
	float rotation;
	float scale;
	string object_name;
	while(candy_elem) {
		if(StageHelper::GetValue(candy_elem)=="properties") {
			TiXmlElement *property_elem = candy_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "flip") {
					const char *value = property_elem->Attribute("value");
					flip = (value[0]=='t' || value[0] == 'T'); 
				} else if(name == "rotation") {
					const char *value = property_elem->Attribute("value");
					rotation = atof(value);
				} else if(name == "scale") {
					const char *value = property_elem->Attribute("value");
					scale = atof(value);
				} else if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		candy_elem = candy_elem->NextSiblingElement();
	}

	//임시
	SpriteBlockHeader *block = new SpriteBlockHeader();
	DataHelper::ResetGameHeader(block);
	block->sprite_name = body_name;
	block->pos_qbu = qb::vec2(x,y);
	block->flip = flip;
	block->angle_deg = rotation;
	block->name = object_name;
	return BaseDataPtr(candy);
}

BaseDataPtr StageReadPolicy_v02::ReadDispenser(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="dispenser");
	qb::vec2 pos;

	const char *x_str = elem->Attribute("x");
	const char *y_str = elem->Attribute("y");
	pos.x = atof(x_str);
	pos.y = atof(y_str);

	TiXmlElement *dispenser_elem = elem->FirstChildElement();
	
	float dispense_delay = 0;
	int dispense_num = -1;
	std::string dispense_type = "candy";
	string object_name;

	while(dispenser_elem) {
		if(StageHelper::GetValue(dispenser_elem)=="properties") {
			TiXmlElement *property_elem = dispenser_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "dispense_delay") {
					const char *value = property_elem->Attribute("value");
					dispense_delay = atof(value);
				} else if(name == "dispense_type") {
					const char *value = property_elem->Attribute("value");
					dispense_type = std::string(value);
				} else if(name == "dispense_num") {
					const char *value = property_elem->Attribute("value");
					dispense_num = atoi(value);
				} else if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		dispenser_elem = dispenser_elem->NextSiblingElement();
	}



	DispenserHeader *dispenser = new DispenserHeader();
	DataHelper::ResetGameHeader(dispenser);
	dispenser->pos_qbu = pos;
	dispenser->dispense_delay = dispense_delay;
	dispenser->dispense_type = dispense_type;
	dispenser->dispense_num = dispense_num;
	dispenser->name = object_name;
	return BaseDataPtr(dispenser);
}
BaseDataPtr StageReadPolicy_v02::ReadFixedBlock(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem) == "fixed_block");
	std::string body_name = elem->Attribute("body_name");
	std::string texture_file = elem->Attribute("texture");


	float x = atof(elem->Attribute("x"));
	float y = atof(elem->Attribute("y"));

	TiXmlElement *block_elem = elem->FirstChildElement();

	bool flip = false;
	float rotation = 0;
	float scale = 1.0f;
	bool is_dynamic = true;
	bool is_score = true;
	int score_type = kNoneScoreBlock;
	bool is_sliceable = true;
	string block_name;
	while(block_elem) {
		if(StageHelper::GetValue(block_elem)=="properties") {
			TiXmlElement *property_elem = block_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "flip") {
					const char *value = property_elem->Attribute("value");
					flip = (value[0]=='t' || value[0] == 'T'); 
				} else if(name == "rotation") {
					const char *value = property_elem->Attribute("value");
					rotation = atof(value);
				} else if(name == "scale") {
					const char *value = property_elem->Attribute("value");
					scale = atof(value);
				} else if(name == "score_type") {
					string value = StageHelper::GetAttribute(property_elem,"value");
					if(value.at(0) == 'n' || value.at(0) == 'N') {
						score_type = kNoneScoreBlock;
					} else if(value.at(0) == 's' || value.at(0) == 'S') {
						score_type = kScoreBlock;
					} else if(value.at(0) == 'b' || value.at(0) == 'B') {
						score_type = kBadBlock;
					} else {
					}
				}
				else if(name == "is_score") {
					string att_value = StageHelper::GetAttribute(property_elem,"value");
					is_score = StageHelper::ReadBool(att_value,is_score);
					if(is_score) {
						score_type = kScoreBlock;
					} else {
						score_type = kNoneScoreBlock;
					}
				} else if(name == "is_sliceable") {
					string att_value = StageHelper::GetAttribute(property_elem,"value");
					is_sliceable = StageHelper::ReadBool(att_value,is_sliceable);
				} else if(name == "name") {
					block_name = StageHelper::GetAttribute(property_elem,"value");
				} else if(name == "is_dynamic") {
					string value = StageHelper::GetAttribute(property_elem,"value");
					is_dynamic = StageHelper::ReadBool(value,true);
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		block_elem = block_elem->NextSiblingElement();
	}


	//기존맵 Object화 Block은 전부 dynamic 이였으므로 그냥 넣자.
	if(is_dynamic) {
		SpriteBlockHeader *block = new SpriteBlockHeader();
		DataHelper::ResetGameHeader(block);
		block->flip = flip;
		block->sprite_name = body_name;
		block->name = block_name;
		block->pos_qbu.x = x;
		block->pos_qbu.y = y;
		block->angle_deg = rotation;
		return BaseDataPtr(block);
	} else {
		/*
		TerrainBlockHeader *terrain_block = new TerrainBlockHeader();
		DataHelper::ResetGameHeader(terrain_block);
		terrain_block->flip = flip;
		terrain_block->physics_body_name = body_name;
		terrain_block->name = block_name;
		terrain_block->pos_qbu.x = x;
		terrain_block->pos_qbu.y = y;
		terrain_block->rotation = rotation;
		terrain_block->scale = scale;
		terrain_block->sprite_file = texture_file;
		terrain_block->sprite_offset_qbu.x = 0;
		terrain_block->sprite_offset_qbu.y = 0;
		return BaseDataPtr(terrain_block);
		*/
	}
}
BaseDataPtr StageReadPolicy_v02::ReadPhysicalObject(TiXmlElement *elem)
{
	/*assert(StageHelper::GetValue(elem) == "physical_object");
	std::string body_name = elem->Attribute("body_name");
	float x = atof(elem->Attribute("x"));
	float y = atof(elem->Attribute("y"));

	TiXmlElement *physical_elem = elem->FirstChildElement();

	bool flip;
	float rotation;
	float scale;
	while(physical_elem) {
		if(StageHelper::GetValue(physical_elem)=="properties") {
			TiXmlElement *property_elem = physical_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "flip") {
					const char *value = property_elem->Attribute("value");
					flip = (value[0]=='t' || value[0] == 'T'); 
				} else if(name == "rotation") {
					const char *value = property_elem->Attribute("value");
					rotation = atof(value);
				} else if(name == "scale") {
					const char *value = property_elem->Attribute("value");
					scale = atof(value);
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		physical_elem = physical_elem->NextSiblingElement();
	}

	//임시
	CandyHeader *candy = new CandyHeader();
	DataHelper::ResetGameHeader(candy);
	candy->entity_name = body_name;
	candy->pos_qbu = qb::vec2(x,y);
	candy->flip = flip;
	candy->rotation = rotation;
	candy->scale = scale;
	return BaseDataPtr(candy);*/
	return BaseDataPtr(NULL);
}
BaseDataPtr StageReadPolicy_v02::ReadMovableBlock(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="movable_block");
	qb::vec2 pos;
	float width, height, angle, min, max;

	const char *x_str = elem->Attribute("x");
	const char *y_str = elem->Attribute("y");
	const char *width_str = elem->Attribute("width");
	const char *height_str = elem->Attribute("height");
	const char *angle_str = elem->Attribute("angle");
	const char *min_str = elem->Attribute("min");
	const char *max_str = elem->Attribute("max");

	pos.x = atof(x_str);
	pos.y = atof(y_str);
	width = atof(width_str);
	height = atof(height_str);
	angle = atof(angle_str);
	min = atof(min_str);
	max = atof(max_str);

	string object_name;
	TiXmlElement *movable_elem = elem->FirstChildElement();
	while(movable_elem) {
		if(StageHelper::GetValue(movable_elem)=="properties") {
			TiXmlElement *property_elem = movable_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "name") {
					object_name = StageHelper::GetAttribute(property_elem,"value");
				} else {

				}
				property_elem = property_elem->NextSiblingElement();
			}
		}
		movable_elem = movable_elem->NextSiblingElement();
	}


	MovableBlockHeader *movableBlock = new MovableBlockHeader();
	DataHelper::ResetGameHeader(movableBlock);
	movableBlock->initial_pos_qbu = pos;
	movableBlock->is_vertical = (angle==90);
	movableBlock->qbu_height = height;
	movableBlock->qbu_width = width;
	movableBlock->qbu_max_bound = max;
	movableBlock->qbu_min_bound = min;
	movableBlock->name = object_name;

	return BaseDataPtr(movableBlock);
}
CommentHeader StageReadPolicy_v02::ReadComment(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="comment");
	TiXmlElement *comment_elem = elem->FirstChildElement();

	int size = 10;	//기본 크기
	std::string text;
	float top = 0;
	float left = 0;

	while(comment_elem) {
		if(StageHelper::GetValue(comment_elem)=="properties") {
			TiXmlElement *property_elem = comment_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string name = StageHelper::GetAttribute(property_elem,"name");
				if(name == "size") {
					const char *value = property_elem->Attribute("value");
					size = atoi(value);
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		} else if(StageHelper::GetValue(comment_elem) == "text") {
			text = std::string(comment_elem->GetText());
		} else if(StageHelper::GetValue(comment_elem) == "rect") {
			top = atof(comment_elem->Attribute("top"));
			left = atof(comment_elem->Attribute("left"));
		}
		comment_elem = comment_elem->NextSiblingElement();
	}
	CommentHeader comment;
	comment.size = size;
	comment.text = text;
	comment.top_left_qbu.x = left;
	comment.top_left_qbu.y = top;
	return comment;
}

BaseDataPtr StageReadPolicy_v02::ReadJoint(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="joint");
	string type = StageHelper::GetAttribute(elem,"type");
	string body_a_name = StageHelper::GetAttribute(elem,"body_a");
	string body_b_name = StageHelper::GetAttribute(elem,"body_b");
	string body_name = StageHelper::GetAttribute(elem,"body");
	
	if(type == "linear_joint") {
		qb::vec2 anchor;
		float angle_rad = 0;
		float min_qbu = 100;
		float max_qbu = 100;
		bool is_enable = true;
		string joint_name;
		bool collide_connected = true;
		bool enable_motor = true;
		float motor_speed_qbu = 1.0f;
		bool repeat = true;

		TiXmlElement *joint_elem = elem->FirstChildElement();

		while(joint_elem) {
			string value = StageHelper::GetValue(joint_elem);
			if(value == "anchor") {
				anchor.x = atof(joint_elem->Attribute("x"));
				anchor.y = atof(joint_elem->Attribute("y"));
			} else if(value == "angle_rad") {
				angle_rad = atof(joint_elem->Attribute("value"));
			} else if(value == "min_qbu") {
				min_qbu = atof(joint_elem->Attribute("value"));
			} else if(value == "max_qbu") {
				max_qbu = atof(joint_elem->Attribute("value"));
			} else if(value == "properties") {
				TiXmlElement *property_elem = joint_elem->FirstChildElement();
				while(property_elem) {
					assert(StageHelper::GetValue(property_elem)=="property");
					string name = StageHelper::GetAttribute(property_elem,"name");
					if(name == "is_enable") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="false" || att_value=="FALSE" || att_value=="f" || att_value=="F" || att_value=="False") {
							is_enable = false;
						} else {
							is_enable = true;
						}
					} else if(name == "name") {
						joint_name = StageHelper::GetAttribute(property_elem,"value");
					} else if(name == "collide_connected") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value[0] == 'F' || att_value[0] == 'f') {
							collide_connected = false;
						} else {
							collide_connected = true;
						}
					} else if(name == "enable_motor") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value[0] == 'F' || att_value[0] == 'f') {
							enable_motor = false;
						} else {
							enable_motor = true;
						}
					} else if(name == "motor_speed_qbu") {
						motor_speed_qbu = atof(property_elem->Attribute("value"));
					} else if(name == "repeat") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value[0] == 'F' || att_value[0] == 'f') {
							repeat = false;
						} else {
							repeat = true;
						}
					} else {
					}
					property_elem = property_elem->NextSiblingElement();
				}

			}
			joint_elem = joint_elem->NextSiblingElement();
		}
		LinearJointHeader *linearJoint = new LinearJointHeader();
		linearJoint->anchor = anchor;
		linearJoint->angle_rad = angle_rad;
		linearJoint->body_name = body_name;
		linearJoint->enable_motor = enable_motor;
		linearJoint->max_qbu = max_qbu;
		linearJoint->min_qbu = min_qbu;
		linearJoint->motor_speed_qbu = motor_speed_qbu;
		linearJoint->pos_qbu = anchor;
		linearJoint->name = joint_name;
		linearJoint->repeat = repeat;
		return BaseDataPtr(linearJoint);

	}

	else if(type == "rope_joint") {
		//로프의 경우 직접 만든 Rope Class를 사용
		float length = 10.0f;

		qb::vec2 anchor_a;
		qb::vec2 anchor_b;
		bool is_enable = true;
		string joint_name;
		TiXmlElement *joint_elem = elem->FirstChildElement();

		while(joint_elem) {
			string value = StageHelper::GetValue(joint_elem);
			if(value=="anchor_a")	{
				anchor_a.x = atof(joint_elem->Attribute("x"));
				anchor_a.y = atof(joint_elem->Attribute("y"));
			} else if(value=="anchor_b") {
				anchor_b.x = atof(joint_elem->Attribute("x"));
				anchor_b.y = atof(joint_elem->Attribute("y"));
			} else if(value=="properties") {
				TiXmlElement *property_elem = joint_elem->FirstChildElement();
				while(property_elem) {
					assert(StageHelper::GetValue(property_elem)=="property");
					string name = StageHelper::GetAttribute(property_elem,"name");
					if(name == "length") {
						length = atof(property_elem->Attribute("value"));
					} else if(name == "is_enable") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="false" || att_value=="FALSE" || att_value=="f" || att_value=="F" || att_value=="False") {
							is_enable = false;
						} else {
							is_enable = true;
						}
					} else if(name == "name") {
						joint_name = StageHelper::GetAttribute(property_elem,"value");
					} else {
					}
					property_elem = property_elem->NextSiblingElement();
				}
			} else {

			}

			joint_elem = joint_elem->NextSiblingElement();
		}
		RopeJointHeader *ropeJoint = new RopeJointHeader();
		DataHelper::ResetGameHeader(ropeJoint);
		ropeJoint->anchor_a_qbu = anchor_a;
		ropeJoint->anchor_b_qbu = anchor_b;
		ropeJoint->body_a_name = body_a_name;
		ropeJoint->body_b_name = body_b_name;
		ropeJoint->type = kStructRope;
		ropeJoint->length = length;
		ropeJoint->name = joint_name;
		return BaseDataPtr(ropeJoint);
	} else if(type == "revolute_joint") {
		qb::vec2 anchor;

		bool collide_connected = true;
		bool enable_limit = false;
		bool enable_motor = false;
		float lower_angle = 0;
		float upper_angle = 0;
		float max_motor_torque = 0;
		float motor_speed = 0;
		float reference_angle = 0;
		bool is_enable = true;
		string joint_name;
		TiXmlElement *joint_elem = elem->FirstChildElement();

		while(joint_elem) {
			string value = StageHelper::GetValue(joint_elem);
			if(value=="anchor")	{
				anchor.x = atof(joint_elem->Attribute("x"));
				anchor.y = atof(joint_elem->Attribute("y"));
			} else if(value=="properties") {
				TiXmlElement *property_elem = joint_elem->FirstChildElement();
				while(property_elem) {
					assert(StageHelper::GetValue(property_elem)=="property");
					string name = StageHelper::GetAttribute(property_elem,"name");
					if(name == "collide_connected") {
						const char *value = property_elem->Attribute("value");
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="false" || att_value=="FALSE" || att_value=="f" || att_value=="F" || att_value=="False") {
							collide_connected = false;
						} else {
							collide_connected = true;
						}
					} else if(name == "enable_limit") {
						const char *value = property_elem->Attribute("value");
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="true" || att_value=="TRUE" || att_value=="t" || att_value=="T" || att_value=="True") {
							enable_limit = true;
						} else {
							enable_limit = false;
						}
					} else if(name == "enable_motor") {
						const char *value = property_elem->Attribute("value");
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="true" || att_value=="TRUE" || att_value=="t" || att_value=="T" || att_value=="True") {
							enable_motor = true;
						} else {
							enable_motor = false;
						}
					} else if(name == "lower_angle") {
						lower_angle = atof(property_elem->Attribute("value"));
					} else if(name == "upper_angle") {
						upper_angle = atof(property_elem->Attribute("value"));
					} else if(name == "max_motor_torque") {
						max_motor_torque = atof(property_elem->Attribute("value"));
					} else if(name == "motor_speed") {
						motor_speed = atof(property_elem->Attribute("value"));
					} else if(name == "reference_angle") {
						reference_angle = atof(property_elem->Attribute("value"));
					} else if(name == "is_enable") {
						string att_value = StageHelper::GetAttribute(property_elem,"value");
						if(att_value=="false" || att_value=="FALSE" || att_value=="f" || att_value=="F" || att_value=="False") {
							is_enable = false;
						} else {
							is_enable = true;
						}
					} else if(name == "name") {
						joint_name = StageHelper::GetAttribute(property_elem,"value");
					} else {
					}
					property_elem = property_elem->NextSiblingElement();
				}
			} else {

			}

			joint_elem = joint_elem->NextSiblingElement();
		}

		RevoluteJointHeader *revoluteJoint = new RevoluteJointHeader();
		DataHelper::ResetGameHeader(revoluteJoint);
		revoluteJoint->type = kStructRevoluteJoint;;
		revoluteJoint->anchor_qbu = anchor;
		revoluteJoint->body_name = body_name;
		revoluteJoint->enable_limit = enable_limit;
		revoluteJoint->enable_motor = enable_motor;
		revoluteJoint->lower_angle = lower_angle;
		revoluteJoint->upper_angle = upper_angle;
		revoluteJoint->name = joint_name;

		return BaseDataPtr(revoluteJoint);
		
	} 
	return NULL;
}
#endif