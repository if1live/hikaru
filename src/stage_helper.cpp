// Ŭnicode please
#include "arch.h"
#include "stage_helper.h"
#if _WIN_
#include <tinyxml.h>
#else
#include "tinyxml/tinyxml.h"
#endif
#include "stage_header.h"
#include "template_lib.h"
#include "assert_include.h"
#include "data_helper.h"
#include "stage_io_policy_v4.h"
#include "stage_read_policy_v02.h"

using namespace qb;
using namespace std;

///////////////////////////////////////////////////////////////////
//스테이지 읽기에 기본적으로 사용되는 내용
//사실상 공용니니까 전역함수같이 만들엇다
string StageHelper::GetValue(TiXmlElement *elem)
{
	assert(elem);
	return string(elem->Value());

}
string StageHelper::GetAttribute(TiXmlElement *elem, const std::string &att_name)
{
	assert(elem);
	const char *value = elem->Attribute(att_name.c_str());
	if(value == NULL) {
		static string empty;
		return empty;
	} else {
		return string(value);
	}
}
bool StageHelper::ReadBool(const std::string boolStr,bool default_value)
{
	if(boolStr=="true" || boolStr=="TRUE" || boolStr=="t" || boolStr=="T" || boolStr=="True") {
		return true;
	} else if(boolStr=="false" || boolStr=="FALSE" || boolStr=="f" || boolStr=="F" || boolStr=="False") {
		return false;
	} else {
		return default_value;
	}
}


StageHelper::StageHelper()
{
	//read_policy_list_.push_back(new StageReadPolicy_v02());
	read_policy_list_.push_back(new StageReadPolicy_v4());

	write_policy_list_.push_back(new StageWritePolicy_v4());
}
StageHelper::~StageHelper()
{
	ClearSequenceContainer(read_policy_list_);	
	ClearSequenceContainer(write_policy_list_);
}
bool StageHelper::ReadStage(const char *xmlStr,StageHeader &stage)
{
	if(xmlStr == NULL) {
		return false;
	}
	TiXmlDocument doc;
	doc.Parse(xmlStr);
	if(doc.Error() == true) {
		//LOGD("%s", xmlStr);
		printf("%s", xmlStr);
		//LOGD("Xml Source END");
	}
	IUASSERT(doc.Error() == false);
	
	TiXmlElement *elem = doc.RootElement();

	if(GetValue(elem)=="stage") {
		string versionStr = GetAttribute(elem,"version");
		int version = atoi(versionStr.c_str());
		
		auto it = read_policy_list_.begin();
		auto endit = read_policy_list_.end();
		for( ; it != endit ; it++) {
			if((*it)->version() == version) {
				(*it)->Read(elem, stage);
				return true;
			}
		}
		IUASSERT(!"not valid version");
	}		
	return true;
}

TiXmlDocument StageHelper::WriteStage(const StageHeader &stage)
{
	//버전은 그냥 최신꺼 쓰자
	StageWritePolicy *policy = write_policy_list_[0];
	
	TiXmlElement *root = new TiXmlElement("root");
	policy->Write(root, stage);

	TiXmlDocument doc;
	doc.LinkEndChild(root);
	return doc;
}
