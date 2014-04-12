#if 0
// Ŭnicode please
#pragma once

#include "stage_helper.h"
#include "unordered_map_include.h"

class TiXmlElement;

struct BaseData;
typedef std::tr1::shared_ptr<BaseData> BaseDataPtr;

class StageReadPolicy_v02 : public StageReadPolicy {
public:
	StageReadPolicy_v02() : StageReadPolicy(0) {}
	~StageReadPolicy_v02() {}
	void Read(TiXmlElement *root, StageHeader &stage);

private:
	void ReadStageProperties(TiXmlElement *elem,StageHeader *stage);
	void ReadLayers(TiXmlElement *elem,StageHeader *stage);

	CommentHeader ReadComment(TiXmlElement *elem);

	
	BaseDataPtr ReadBlock(TiXmlElement *elem);					
	BaseDataPtr ReadSpike(TiXmlElement *elem);
	BaseDataPtr ReadBalloon(TiXmlElement *elem);
	BaseDataPtr ReadMovableBlock(TiXmlElement *elem);
	BaseDataPtr ReadCandy(TiXmlElement *elem);
	BaseDataPtr ReadDispenser(TiXmlElement *elem);
	BaseDataPtr ReadPhysicalObject(TiXmlElement *elem);
	BaseDataPtr ReadFixedBlock(TiXmlElement *elem);
	BaseDataPtr ReadFloor(TiXmlElement *elem);	
	BaseDataPtr ReadBelt(TiXmlElement *elem);
	BaseDataPtr ReadJoint(TiXmlElement *elem);
};
#endif