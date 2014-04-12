// Ŭnicode please
#include "struct_version_converter.h"
#include "class_dict.h"
#include "class_attribute.h"
#include "assert_include.h"

using namespace std;
using namespace qb;
using namespace std::tr1;

std::vector<StructConverterParam> StructVersionConverter::converter_list_;
std::vector<StructConverterParam> &StructVersionConverter::GetConverterList()
{
	if(converter_list_.empty()) {
		//converter 적절히 등록하기
		RegisterConverter<Converter_TerrainHeaderV1_TerrainHeaderV2>();
		RegisterConverter<Converter_BoostHeaderV1_BoostHeaderV2>();
		RegisterConverter<Converter_CraneHeaderV1_CraneHeaderV2>();
		RegisterConverter<Converter_BeltHeaderV1_BeltHeaderV2>();
		RegisterConverter<Converter_CraneHeaderV2_CraneHeaderV3>();
		RegisterConverter<Converter_CraneHeaderV3_CraneHeaderV4>();
		RegisterConverter<Converter_CraneHeaderV4_CraneHeaderV5>();
	}
	return converter_list_;
}
BaseDataPtr StructVersionConverter::ConvertToLatest(BaseDataPtr from)
{
	//최초에 적절히 생성하기. 여기에서 먼저 생성해준다
	std::vector<StructConverterParam> &converter_list = GetConverterList();
	ClassDict &dict = ClassDict::GetInstance();

	while(true) {
		//최신버전이면 적절히 종료
		ClassAttribute *from_class_attr = dict.Get(from->class_hash);
		if(dict.IsLatestClassName(from_class_attr->class_name())) {
			return from;
		}

		auto it = converter_list.begin();
		auto endit = converter_list.end();
		bool convert_occur = false;
		for( ; it != endit ; ++it) {
			if(it->from_class_hash == from->class_hash) {
				StructVersionConverter *convert = it->conveter;
				from = convert->Convert(from.get());
				convert_occur = true;
			}
		}
		IUASSERT(convert_occur == true);
	}
}

void Converter_TerrainHeaderV1_TerrainHeaderV2::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.is_bezier = false;
	to.points = from.polygon;
	to.texture_file = from.texture_file;
}


void Converter_BoostHeaderV1_BoostHeaderV2::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.pos_qbu = from.pos_qbu;
	to.angle = from.angle;
	to.velocity_qbu = 320; //기본값
}

void Converter_CraneHeaderV1_CraneHeaderV2::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.pos_qbu = from.pos_qbu;
	to.angle_deg = from.angle_deg;
	to.is_left_start = from.is_left_start;
	to.rail_length_qbu = from.rail_length_qbu;
	to.rod_length_qbu = from.rod_length_qbu;
	to.has_button = true;
}
void Converter_CraneHeaderV2_CraneHeaderV3::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.pos_qbu = from.pos_qbu;
	to.angle_deg = from.angle_deg;
	to.is_left_start = from.is_left_start;
	to.rail_length_qbu = from.rail_length_qbu;
	to.rod_length_qbu = from.rod_length_qbu;
	to.has_button = from.has_button;
	to.left_rail_drag = "no_drag";
	to.right_rail_drag = "no_drag";

}
void Converter_BeltHeaderV1_BeltHeaderV2::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.angle_deg = from.angle_deg;
	to.initial_speed_qbups = from.initial_speed_qbups;
	to.width_qbu = from.width_qbu;
	to.x_qbu = from.x_qbu;
	to.y_qbu = from.y_qbu;
	to.has_button = false;
}
void Converter_CraneHeaderV3_CraneHeaderV4::Convert(const FromType &from, ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.pos_qbu = from.pos_qbu;
	to.angle_deg = from.angle_deg;
	to.is_left_start = from.is_left_start;
	to.rail_length_qbu = from.rail_length_qbu;
	to.rod_length_qbu = from.rod_length_qbu;
	to.has_button = from.has_button;
	to.rail_resize = "no";
}
void Converter_CraneHeaderV4_CraneHeaderV5::Convert(const FromType &from,ToType &to)
{
	to.type = from.type;
	to.name = from.name;
	to.pos_qbu = from.pos_qbu;
	to.angle_deg = from.angle_deg;
	to.is_left_start = from.is_left_start;
	to.rail_length_qbu = from.rail_length_qbu;
	to.rod_length_qbu = from.rod_length_qbu;
	to.has_button = from.has_button;
	to.color = "a";	
}