// Ŭnicode please
#pragma once

//옛날의 stage header역할의 일부를 맡는다
//구조체 생성은 자동화가 되엇기떄문에 여기에는 게임과 툴에서 공유할 enum
//과 아직 안옮긴 코드만 둿다

#include <string>
#include <vector>
#include "vector.h"

#include "data_define.h"
#include "typelist.h"
#include "assert_include.h"

enum
{
	kStructNone,

	kStructTerrain, //static 지형 polygon에 패턴입히기
	kStructTerrainBlock,
	kStructPolyBlock,
	kStructSpriteBlock,
	kStructSpike,
	kStructBalloon,
	kStructDispenser,
	kStructFloor,
	kStructBelt,
	kStructCoin,
	kStructCheese,
	kStructGoal,
	kStructCrane,
	kStructPicker,
	kStructRotatingPicker,
	kStructCylinderScale,
	kStructJumpRamp,
	kStructBoost,
	kStructFan,
	kStructRocket,
	kStructImage,
	kStructFinger,
	//조인트도 entity로 취급하자
	kStructRope,
	kStructPortal,
	kStructPortalConnection,
	//스위치트리거액션
	kStructReverseGravity,
	kStructReverseElectro,
	kStructButton,
	kStructSwitch,
	kStructTimer,
	kStructTrigger,
	kStructTriggerArea,
	kStructActionSetEnableMovePattern,
	kStructActionOperate,
	kStructActionChangeAlpha,
	kStructActionFingerAni,
	kStructPopup,

	//이동 패턴 구현용
	kStructSubMovePattern,
	kStructMovePattern,

	

	kStructTypeCount	//항상 마지막에 배치하기
};

template<typename T>
int GetStructType() { 
#if _WIN_
	static_assert(false, "not defined"); IUASSERT(!"not defined");
#endif
	return kStructNone; 
}
//inline를 안붙이면 LNK2005 중복 정의에러가 뜬다
template<> inline int GetStructType<TerrainHeader>() { return kStructTerrain; }
template<> inline int GetStructType<TerrainBlockHeader>() { return kStructTerrainBlock;}
template<> inline int GetStructType<PolyBlockHeader>() { return kStructPolyBlock; }
template<> inline int GetStructType<SpriteBlockHeader>() { return kStructSpriteBlock; }
template<> inline int GetStructType<SpikeHeader>() { return kStructSpike; }
template<> inline int GetStructType<BalloonHeader>() { return kStructBalloon; }
template<> inline int GetStructType<DispenserHeader>() { return kStructDispenser; }
template<> inline int GetStructType<FloorHeader>() { return kStructFloor; }
template<> inline int GetStructType<BeltHeader>() { return kStructBelt; }
template<> inline int GetStructType<CoinHeader>() { return kStructCoin; }
template<> inline int GetStructType<CheeseHeader>() { return kStructCheese; }
template<> inline int GetStructType<GoalHeader>() { return kStructGoal; }
template<> inline int GetStructType<RopeJointHeader>() { return kStructRope; }
template<> inline int GetStructType<CraneHeader>() { return kStructCrane; }
template<> inline int GetStructType<PickerHeader>() { return kStructPicker; }
template<> inline int GetStructType<RotatingPickerHeader>() { return kStructRotatingPicker;}
template<> inline int GetStructType<ImageHeader>(){ return kStructImage;}
template<> inline int GetStructType<FingerHeader>() { return kStructFinger;}

template<> inline int GetStructType<ReverseGravityHeader>() { return kStructReverseGravity; }
template<> inline int GetStructType<ReverseElectroHeader>() {return kStructReverseElectro; }
template<> inline int GetStructType<ButtonHeader>() {return kStructButton;}
template<> inline int GetStructType<SwitchHeader>() {return kStructSwitch;}
template<> inline int GetStructType<TimerHeader>() {return kStructTimer;} 
template<> inline int GetStructType<PortalHeader>() {return kStructPortal;}
template<> inline int GetStructType<PortalConnectionHeader>() {return kStructPortalConnection;}

template<> inline int GetStructType<TriggerHeader>() {return kStructTrigger;}
template<> inline int GetStructType<TriggerAreaHeader>() {return kStructTriggerArea;}
template<> inline int GetStructType<ActionSetEnableMovePatternHeader>() {return kStructActionSetEnableMovePattern;}
template<> inline int GetStructType<ActionOperateHeader>() {return kStructActionOperate;}
template<> inline int GetStructType<ActionChangeAlphaHeader>() {return kStructActionChangeAlpha;}
template<> inline int GetStructType<ActionFingerAniHeader>() {return kStructActionFingerAni;}

template<> inline int GetStructType<SubMovePatternHeader>() { return kStructSubMovePattern; }
template<> inline int GetStructType<MovePatternHeader>() { return kStructMovePattern; }
template<> inline int GetStructType<CylinderScaleHeader>() { return kStructCylinderScale; }
template<> inline int GetStructType<JumpRampHeader>() { return kStructJumpRamp; }
template<> inline int GetStructType<BoostHeader>() { return kStructBoost;}
template<> inline int GetStructType<FanHeader>() { return kStructFan; }
template<> inline int GetStructType<RocketHeader>() { return kStructRocket;}
template<> inline int GetStructType<PopupHeader>() {return kStructPopup;}

//typelist로 어떻게 위와 같은 코드를 자동화 시킬수 잇을거같은데..
//linear joint, movable block , cheese는 아직 구현되어잇지 않아서 여기에 넣으면 문제가 생긴다

typedef TYPELIST_39(
	TerrainHeader,
	TerrainBlockHeader,
	PolyBlockHeader,
	SpriteBlockHeader,
	SpikeHeader,
	BalloonHeader,
	DispenserHeader,
	CylinderScaleHeader,
	FloorHeader,
	BeltHeader,
	CoinHeader,
	JumpRampHeader,
	BoostHeader,
	RopeJointHeader,
	CheeseHeader,
	GoalHeader,
	CraneHeader,
	PickerHeader,
	RotatingPickerHeader,
	ImageHeader,
	FingerHeader,
	ReverseGravityHeader,
	ReverseElectroHeader,
	ButtonHeader,
	SwitchHeader,
	TimerHeader,
	PortalHeader,
	PortalConnectionHeader,
	TriggerHeader,
	TriggerAreaHeader,
	ActionSetEnableMovePatternHeader,
	ActionOperateHeader,
	ActionChangeAlphaHeader,
	ActionFingerAniHeader,
	SubMovePatternHeader,
	MovePatternHeader,
	FanHeader,
	RocketHeader,
	PopupHeader
	) StructHeaderTypeList;

struct CommentHeader
{
	qb::vec2 top_left_qbu;
	int size;	
	std::string text;
	std::string name;

	float width;
	float height;
	float init_alpha;
};

struct StageHeader
{
	float width;
	float height;
	float qbu_initial_pos_x;
	float qbu_initial_pos_y;

	int suggested_clear_time; //초단위
	int shake_num;

	std::string background;

	//레퍼런스 카운터 달면 생성 소멸 신경안쓰고 정신건강에 좋다
	//일반 객체와 조인트 모두 같은 형식으로 취급해서 구조를 단순화하자
	std::vector<BaseDataPtr> entities;

	//얼마 크기도 안큰데 그냥 정적으로 생성해버리자
	std::vector<CommentHeader> comments;
	~StageHeader()	{ }
};
