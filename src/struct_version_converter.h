// Ŭnicode please
#pragma once

#include "stage_header.h"
#include <vector>
#include <tuple>

#include "class_dict.h"
#include "class_attribute.h"

#define CONVERTER_DEF() \
	public:	\
	BaseDataPtr Convert(BaseData *from) const {	\
	qb::ClassDict &dict = qb::ClassDict::GetInstance();	\
	/*from의 최고버전에 해당되는 객체 얻기*/	\
	qb::ClassAttribute *from_class_attr = dict.Get(from->class_hash);	\
	IUASSERT(from_class_attr != NULL);	\
	qb::ClassAttribute *to_class_attr = dict.Get(ToType::ClassHash());	\
	IUASSERT(to_class_attr != NULL);	\
	BaseDataPtr to_base_data(to_class_attr->Clone());	\
	FromType &from_data = static_cast<FromType&>(*from);	\
	ToType &to_data = static_cast<ToType&>(*to_base_data);	\
	Convert(from_data, to_data);	\
	return to_base_data;	\
}	

class StructVersionConverter;

struct StructConverterParam {
	unsigned int from_class_hash;
	unsigned int to_class_hash;
	StructVersionConverter *conveter;
};

class StructVersionConverter {
public:
	//최신버전으로 캐스팅하기
	static BaseDataPtr ConvertToLatest(BaseDataPtr from);
	template<typename T>
	static void RegisterConverter() {
		int from_class_hash = T::FromType::ClassHash();
		int to_class_hash = T::ToType::ClassHash();
		T *converter = new T();
		StructConverterParam param;
		param.from_class_hash = from_class_hash;
		param.to_class_hash = to_class_hash;
		param.conveter = converter;
		converter_list_.push_back(param);
	}
private:
	//from_class_hash
	//to_class_hash
	//converter
	static std::vector<StructConverterParam> &GetConverterList();
	static std::vector<StructConverterParam> converter_list_;

public:
	virtual BaseDataPtr Convert(BaseData *from) const = 0;
};

//자동 컨버터 예제
//매크로를 사용하고 FromType, ToType만 적절히 잡아주고
//convert하뭇만 잘 만들어주면 나머지는 알아서됨
class Converter_TerrainHeaderV1_TerrainHeaderV2 : public StructVersionConverter {
	//아래의 매크로를 선언해
	CONVERTER_DEF()
public:
	typedef TerrainHeader_v1 FromType;
	typedef TerrainHeader_v2 ToType;

public:
	static void Convert(const FromType &from, ToType &to);
};

class Converter_BoostHeaderV1_BoostHeaderV2 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef BoostHeader_v1 FromType;
	typedef BoostHeader_v2 ToType;

public :
	static void Convert(const FromType &from, ToType &to);
};

class Converter_CraneHeaderV1_CraneHeaderV2 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef CraneHeader_v1 FromType;
	typedef CraneHeader_v2 ToType;
public :
	static void Convert(const FromType &from, ToType &to);
};

class Converter_CraneHeaderV2_CraneHeaderV3 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef CraneHeader_v2 FromType;
	typedef CraneHeader_v3 ToType;
public :
	static void Convert(const FromType &from, ToType &to);
};

class Converter_CraneHeaderV3_CraneHeaderV4 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef CraneHeader_v3 FromType;
	typedef CraneHeader_v4 ToType;
public :
	static void Convert(const FromType &from, ToType &to);
};

class Converter_CraneHeaderV4_CraneHeaderV5 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef CraneHeader_v4 FromType;
	typedef CraneHeader_v5 ToType;
public :
	static void Convert(const FromType &from, ToType &to);
};


class Converter_BeltHeaderV1_BeltHeaderV2 : public StructVersionConverter {
	CONVERTER_DEF()
public :
	typedef BeltHeader_v1 FromType;
	typedef BeltHeader_v2 ToType;

public :
	static void Convert(const FromType &from, ToType &to);
};

