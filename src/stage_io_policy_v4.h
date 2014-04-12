// Ŭnicode please
#pragma once

#include "stage_helper.h"

//읽기 방법 v4. 컴포넌트같은 느낌으로 자동화된 읽기
class StageReadPolicy_v4 : public StageReadPolicy {
public:
	StageReadPolicy_v4() : StageReadPolicy(4) {}
	~StageReadPolicy_v4() {}
	void Read(TiXmlElement *root, StageHeader &stage);

private:
	void ReadStageProperties(TiXmlElement *elem,StageHeader *stage);
	CommentHeader ReadComment(TiXmlElement *elem);
	void ReadCommentList(TiXmlElement *elem, StageHeader *stage);
	void ReadStructList(TiXmlElement *elem, StageHeader *stage);
};

class StageWritePolicy_v4 : public StageWritePolicy {
public:
	StageWritePolicy_v4() : StageWritePolicy(4) {}
	~StageWritePolicy_v4() {}
	void Write(TiXmlElement *root, const StageHeader &stage);

private:
	void WriteStageProperties(TiXmlElement *elem, const StageHeader &header);
	void WriteCommentList(TiXmlElement *elem, const StageHeader &header);
	void WriteStructList(TiXmlElement *elem, const StageHeader &header);
};
