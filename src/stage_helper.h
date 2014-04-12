// Ŭnicode please
#pragma once

#include <vector>
#include <string>

class TiXmlElement;
class TiXmlDocument;
struct StageHeader;
class StageReadPolicy;
struct CommentHeader;

class StageReadPolicy {
public:
	StageReadPolicy(int version) : version_(version) {}
	virtual ~StageReadPolicy() {}
	virtual void Read(TiXmlElement *root, StageHeader &stage) = 0;

public:
	int version() const { return version_; }
private:
	int version_; 
};

class StageWritePolicy {
public:
	StageWritePolicy(int version) : version_(version) {}
	virtual ~StageWritePolicy() {}
	virtual void Write(TiXmlElement *root, const StageHeader &stage) = 0;
public:
	int version() const { return version_; }
private:
	int version_;
};

class StageHelper {
public :
	StageHelper();
	~StageHelper();
	//맵포맷이 xml을 벗어나지는 않을테니까 xml노드파싱해서
	//세부 구현체로 넘기는 역할만 수행하자
	bool ReadStage(const char *xmlStr,StageHeader &stage);
	bool ReadStage(TiXmlElement *elem, StageHeader &stage);
	TiXmlDocument WriteStage(const StageHeader &stage);

private:
	std::vector<StageReadPolicy*> read_policy_list_;
	std::vector<StageWritePolicy*> write_policy_list_;	

public:
	static std::string GetValue(TiXmlElement *elem);
	static std::string GetAttribute(TiXmlElement *elem, const std::string &att_name);
	static bool ReadBool(const std::string boolStr,bool default_value);
};
