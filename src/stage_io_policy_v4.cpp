// Ŭnicode please
#include "stage_io_policy_v4.h"
#include "stage_header.h"
#include "data_helper.h"
#if _WIN_
#include <tinyxml.h>
#else
#include "tinyxml/tinyxml.h"
#endif
#include "assert_include.h"
#include "struct_version_converter.h"

using namespace std;
using namespace qb;

void StageReadPolicy_v4::Read(TiXmlElement *root, StageHeader &stage)
{
	TiXmlElement *stage_elem = root->FirstChildElement();
	while(stage_elem) {
		//stage Properties
		string elem_value = StageHelper::GetValue(stage_elem);
		if(elem_value=="properties") {
			ReadStageProperties(stage_elem,&stage);
		} else if(elem_value == "comment_list") {
			ReadCommentList(stage_elem, &stage);
		} else if(elem_value == "entity_list") {
			ReadStructList(stage_elem, &stage);
		}
		stage_elem = stage_elem->NextSiblingElement();
	}
}

void StageReadPolicy_v4::ReadStageProperties(TiXmlElement *elem,StageHeader *stage)
{
	assert(StageHelper::GetValue(elem)=="properties");
	float height = 480;
	float width = 320;
	float start_x = 0;
	float start_y = 0;
	int suggested_clear_time = 60;
	int shake_num = 0;
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
		} else if(name == "suggested_clear_time") {
			const char *value = property_elem->Attribute("value");
			suggested_clear_time = (int)atoi(value);
		} else if(name == "shake_num") {
			const char *value = property_elem->Attribute("value");
			shake_num = (int)atoi(value);
		} else {
		}
		property_elem = property_elem->NextSiblingElement();
	}
	stage->height = height;
	stage->width = width;
	stage->qbu_initial_pos_x = start_x;
	stage->qbu_initial_pos_y = start_y;
	stage->background = background;
	stage->suggested_clear_time = suggested_clear_time;
	stage->shake_num = shake_num;
}

void StageReadPolicy_v4::ReadCommentList(TiXmlElement *elem, StageHeader *stage)
{
	auto child = elem->FirstChild();
	for(auto node = child ; node ; node = node->NextSibling()) {
		TiXmlElement *child_node = static_cast<TiXmlElement*>(node);
		CommentHeader cmt_header = ReadComment(child_node);
		stage->comments.push_back(cmt_header);
	}
}

void StageReadPolicy_v4::ReadStructList(TiXmlElement *elem, StageHeader *stage)
{
	auto child = elem->FirstChild();
	for(auto node = child ; node ; node = node->NextSibling()) {
		TiXmlElement *child_node = static_cast<TiXmlElement*>(node);
		if(child_node->Type() != TiXmlElement::TINYXML_ELEMENT) {
			continue;
		}

		BaseDataPtr result = DataHelper::XmlNodeToData(child_node);
		if(result.get() == NULL) {
			continue;
		}

		//result를 최신버전으로 변환하기
		result = StructVersionConverter::ConvertToLatest(result);

		//type 미리 기록하기
		int type_code = DataHelper::GetStructTypeCode(result.get());
		if(type_code == -1) {
			continue;
		}
		DataHelper::WriteType(result.get(), type_code);

		stage->entities.push_back(result);
	}
}

CommentHeader StageReadPolicy_v4::ReadComment(TiXmlElement *elem)
{
	assert(StageHelper::GetValue(elem)=="comment");
	TiXmlElement *comment_elem = elem->FirstChildElement();

	int size = 10;	//기본 크기
	std::string text;
	float top = 0;
	float left = 0;
	float width = 0;
	float height = 0;
	float init_alpha = 1.0f;
	std::string name;

	while(comment_elem) {
		if(StageHelper::GetValue(comment_elem)=="properties") {
			TiXmlElement *property_elem = comment_elem->FirstChildElement();
			while(property_elem) {
				assert(StageHelper::GetValue(property_elem)=="property");
				string key_name = StageHelper::GetAttribute(property_elem,"name");
				if(key_name == "size") {
					const char *value = property_elem->Attribute("value");
					size = atoi(value);
				} else if(key_name == "name") {
					const char *value = property_elem->Attribute("value");
					name = string(value);
				} else if(key_name == "init_alpha") {
					const char *value = property_elem->Attribute("value");
					init_alpha = atof(value);
				} else {
				}
				property_elem = property_elem->NextSiblingElement();
			}
		} else if(StageHelper::GetValue(comment_elem) == "text") {
			text = std::string(comment_elem->GetText());
		} else if(StageHelper::GetValue(comment_elem) == "rect") {
			top = (float)atof(comment_elem->Attribute("top"));
			left = (float)atof(comment_elem->Attribute("left"));
			width = (float)atof(comment_elem->Attribute("width"));
			height = (float)atof(comment_elem->Attribute("height"));
		}
		comment_elem = comment_elem->NextSiblingElement();
	}
	CommentHeader comment;
	comment.size = size;
	comment.text = text;
	comment.top_left_qbu.x = left;
	comment.top_left_qbu.y = top;
	comment.width = width;
	comment.height = height;
	comment.init_alpha = init_alpha;
	comment.name = name;
	return comment;
}

//////////////////////////////////

void StageWritePolicy_v4::Write(TiXmlElement *root, const StageHeader &stage)
{
	IUASSERT(root->Type() == TiXmlNode::TINYXML_ELEMENT);
	root->SetValue("stage");
	root->SetAttribute("version", 4);

	TiXmlElement *properties_node = new TiXmlElement("properties");
	WriteStageProperties(properties_node, stage);
	root->LinkEndChild(properties_node);

	TiXmlElement *cmt_node = new TiXmlElement("comment_list");
	WriteCommentList(cmt_node, stage);
	root->LinkEndChild(cmt_node);

	TiXmlElement *entity_list_node = new TiXmlElement("entity_list");
	WriteStructList(entity_list_node, stage);
	root->LinkEndChild(entity_list_node);
}

void StageWritePolicy_v4::WriteStageProperties(TiXmlElement *elem, const StageHeader &header)
{
	/*
    <property name="background" value="back01.png"/>
    <property name="height" value="480"/>
	<property name="width" value="320"/>
    <property name="start_x" value="0"/>
    <property name="start_y" value="0"/>
	*/
	const char *node_name = "property";
	const char *kName = "name";
	const char *kValue = "value";

	TiXmlElement *background = new TiXmlElement(node_name);
	background->SetAttribute(kName, "background");
	background->SetAttribute(kValue, header.background.c_str());
	elem->LinkEndChild(background);

	TiXmlElement *height = new TiXmlElement(node_name);
	height->SetAttribute(kName, "height");
	height->SetAttribute(kValue, header.height);
	elem->LinkEndChild(height);

	TiXmlElement *width = new TiXmlElement(node_name);
	width->SetAttribute(kName, "width");
	width->SetAttribute(kValue, header.width);
	elem->LinkEndChild(width);

	TiXmlElement *start_x = new TiXmlElement(node_name);
	start_x->SetAttribute(kName, "start_x");
	start_x->SetAttribute(kValue, header.qbu_initial_pos_x);
	elem->LinkEndChild(start_x);

	TiXmlElement *start_y = new TiXmlElement(node_name);
	start_y->SetAttribute(kName, "start_y");
	start_y->SetAttribute(kValue, header.qbu_initial_pos_y);
	elem->LinkEndChild(start_y);

	TiXmlElement *suggested_clear_time = new TiXmlElement(node_name);
	suggested_clear_time->SetAttribute(kName, "suggested_clear_time");
	suggested_clear_time->SetAttribute(kValue, header.suggested_clear_time);
	elem->LinkEndChild(suggested_clear_time);

	TiXmlElement *shake_num = new TiXmlElement(node_name);
	shake_num->SetAttribute(kName, "shake_num");
	shake_num->SetAttribute(kValue, header.shake_num);
	elem->LinkEndChild(shake_num);
}

void StageWritePolicy_v4::WriteCommentList(TiXmlElement *elem, const StageHeader &header)
{
	auto it = header.comments.begin();
	auto endit = header.comments.end();
	for( ; it != endit ; ++it) {
		const CommentHeader &comment = *it;
		/*
		<comment>
		<properties>
			<property name="size" value="20"/>
		</properties>
		<text>Slice to drop</text>
		<rect top="393.952" left="110.493" width="161.667" height="36.6667"/>
		</comment>
		*/
		TiXmlElement *node = new TiXmlElement("comment");

		TiXmlElement *properties = new TiXmlElement("properties");
		
		TiXmlElement *size_node = new TiXmlElement("property");
		size_node->SetAttribute("name", "size");
		size_node->SetAttribute("value", comment.size);
		properties->LinkEndChild(size_node);

		TiXmlElement *name_node = new TiXmlElement("property");
		name_node->SetAttribute("name", "name");
		name_node->SetAttribute("value", comment.name);
		properties->LinkEndChild(name_node);

		TiXmlElement *init_alpha_node = new TiXmlElement("property");
		init_alpha_node->SetAttribute("name", "init_alpha");
		init_alpha_node->SetDoubleAttribute("value", comment.init_alpha);
		properties->LinkEndChild(init_alpha_node);
		

		node->LinkEndChild(properties);

		TiXmlElement *text = new TiXmlElement("text");
		TiXmlText *text_area = new TiXmlText("");
		text_area->SetValue(comment.text.c_str());
		text->LinkEndChild(text_area);
		node->LinkEndChild(text);

		TiXmlElement *rect = new TiXmlElement("rect");
		rect->SetAttribute("top", comment.top_left_qbu.y);
		rect->SetAttribute("left", comment.top_left_qbu.x);
		rect->SetAttribute("width", comment.width);
		rect->SetAttribute("height", comment.height);
		node->LinkEndChild(rect);

		elem->LinkEndChild(node);
	}
}

void StageWritePolicy_v4::WriteStructList(TiXmlElement *elem, const StageHeader &header)
{
	auto it = header.entities.begin();
	auto endit = header.entities.end();
	for( ; it != endit ; it++) {
		BaseData *data = it->get();

		TiXmlElement *node = new TiXmlElement("empty");
		DataHelper::DataToXmlNode(data, node);

		elem->LinkEndChild(node);
	}
}
