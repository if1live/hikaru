// Ŭnicode please	
//데이터를 선언만 하지 직접인클루드 하지는 않을것

//반쯤 예제로 쓸 구조체
STRUCT_BEGIN(DemoStruct, 1)
	STRUCT_VAR_INT(a)
	STRUCT_VAR_FLOAT(b)
	STRUCT_VAR_BOOL(c)
	STRUCT_VAR_STRING(d)
	STRUCT_VAR_VEC2(e)
	STRUCT_VAR_STRING_LIST(f)
	STRUCT_VAR_VEC2_LIST(g)
STRUCT_END()

STRUCT_NEW_BEGIN(DemoStruct, 2)
	STRUCT_VAR_STR_ENUM_BEGIN(c)
		STRUCT_VAR_STR_ENUM_KEY(1)
		STRUCT_VAR_STR_ENUM_KEY(2)
		STRUCT_VAR_STR_ENUM_KEY(3)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()


//// 실제로 게임에서 사용할 자동생성 구조체를 적절히 정의하기
//string:name, int:type 은 컴포넌트에 따라서 공통속성
//type를 먼저두면 캐스팅한거에서 바로 접근 가능(오프셋이 0이니까)
//는 망한다(아래의 클래스는 가상함수 잇는거 상속이라서
//오프셋0으로 무식한 접근하면 뒤진다
STRUCT_NEW_BEGIN(TerrainHeader, 2)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)
	
	STRUCT_VAR_BOOL(is_bezier) //true 면 points에서 연속된3개씩 bezier point 로읽고
								//false 면 1개씩 polygon으로 읽는다.	
	STRUCT_VAR_VEC2_LIST(points) 
	STRUCT_VAR_STRING(texture_file)
	STRUCT_VAR_FLOAT(angle_editor) //에디터에서만 쓰는 angle 값
STRUCT_END()

//구버전 업그레이드가 지원되나 볼까
STRUCT_BEGIN(TerrainHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2_LIST(polygon)
	STRUCT_VAR_STRING(texture_file)
STRUCT_END()

STRUCT_NEW_BEGIN(TerrainBlockHeader, 1) //preset 지형
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_BOOL(tap_breakable)

	STRUCT_VAR_VEC2_LIST(polygon) 
	//polygon 은 게임 화면에서 qbu 좌표가 아니라,
	//file_name 이 가르키는 sprite 의 중심을 기준으로 하는 polygon 이다.
	//(TerrainHeader의 polygon이 게임화면의 qbu 좌표를 갖는것과 다름, 
	// 예전 SpriteBlock의 fixture와 비슷한 느낌)
	//따라서 게임에 들어갈때는 polygon도 위의 angle_deg, pos_qbu 값을 적용해서 변환한 좌표가 들어가야한다.
	STRUCT_VAR_STRING(file_name) //스프라이트 파일 이름
	STRUCT_VAR_INT(block_type_editor) //에디터에서만 사용
STRUCT_END()


STRUCT_NEW_BEGIN(PolyBlockHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2_LIST(polygon)
	STRUCT_VAR_STRING(texture_file)
	STRUCT_VAR_BOOL(tap_breakable)
	
	STRUCT_VAR_FLOAT(angle_editor) //에디터에서만 쓰는 angle 값
STRUCT_END()

STRUCT_NEW_BEGIN(SpriteBlockHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)

	STRUCT_VAR_BOOL(is_ani)//true 면 ani false 면 sprite
	STRUCT_VAR_STRING(drawable_name)
	STRUCT_VAR_STRING(physics_name)

	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_BOOL(flip)
	STRUCT_VAR_BOOL(tap_breakable)
STRUCT_END()

STRUCT_NEW_BEGIN(CheeseHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)	

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(GoalHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_BEGIN(CraneHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //레일 중심의위치
	STRUCT_VAR_FLOAT(angle_deg) //레일의 각도
	STRUCT_VAR_FLOAT(rail_length_qbu) //레일의 길이 제한없음
	STRUCT_VAR_FLOAT(rod_length_qbu) //막대의 길이 30~200
	STRUCT_VAR_BOOL(is_left_start) //처음에 막대+집게가 왼쪽끝에 붙어있나 오른쪽끝에붙어있나
STRUCT_END()

STRUCT_BEGIN(CraneHeader, 2)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //레일 중심의위치
	STRUCT_VAR_FLOAT(angle_deg) //레일의 각도
	STRUCT_VAR_FLOAT(rail_length_qbu) //레일의 길이 제한없음
	STRUCT_VAR_FLOAT(rod_length_qbu) //막대의 길이 30~200
	STRUCT_VAR_BOOL(is_left_start) //처음에 막대+집게가 왼쪽끝에 붙어있나 오른쪽끝에붙어있나
	STRUCT_VAR_BOOL(has_button)
STRUCT_END()

STRUCT_BEGIN(CraneHeader, 3)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //레일 중심의위치
	STRUCT_VAR_FLOAT(angle_deg) //레일의 각도
	STRUCT_VAR_FLOAT(rail_length_qbu) //레일의 길이 제한없음
	STRUCT_VAR_FLOAT(rod_length_qbu) //막대의 길이 30~200
	STRUCT_VAR_BOOL(is_left_start) //처음에 막대+집게가 왼쪽끝에 붙어있나 오른쪽끝에붙어있나
	STRUCT_VAR_BOOL(has_button)
	STRUCT_VAR_STR_ENUM_BEGIN(left_rail_drag)
		STRUCT_VAR_STR_ENUM_KEY(no_drag)
		STRUCT_VAR_STR_ENUM_KEY(left)
		STRUCT_VAR_STR_ENUM_KEY(right)
		STRUCT_VAR_STR_ENUM_KEY(both)
	STRUCT_VAR_STR_ENUM_END()
	STRUCT_VAR_STR_ENUM_BEGIN(right_rail_drag)
		STRUCT_VAR_STR_ENUM_KEY(no_drag)
		STRUCT_VAR_STR_ENUM_KEY(left)
		STRUCT_VAR_STR_ENUM_KEY(right)
		STRUCT_VAR_STR_ENUM_KEY(both)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()

STRUCT_BEGIN(CraneHeader, 4)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //레일 중심의위치
	STRUCT_VAR_FLOAT(angle_deg) //레일의 각도
	STRUCT_VAR_FLOAT(rail_length_qbu) //레일의 길이 제한없음
	STRUCT_VAR_FLOAT(rod_length_qbu) //막대의 길이 30~200
	STRUCT_VAR_BOOL(is_left_start) //처음에 막대+집게가 왼쪽끝에 붙어있나 오른쪽끝에붙어있나
	STRUCT_VAR_BOOL(has_button)
	STRUCT_VAR_STR_ENUM_BEGIN(rail_resize)
		STRUCT_VAR_STR_ENUM_KEY(no)
		STRUCT_VAR_STR_ENUM_KEY(left)
		STRUCT_VAR_STR_ENUM_KEY(right)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()

STRUCT_NEW_BEGIN(CraneHeader, 5)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //레일 중심의위치
	STRUCT_VAR_FLOAT(angle_deg) //레일의 각도
	STRUCT_VAR_FLOAT(rail_length_qbu) //레일의 길이 제한없음
	STRUCT_VAR_FLOAT(rod_length_qbu) //막대의 길이 30~200
	STRUCT_VAR_BOOL(is_left_start) //처음에 막대+집게가 왼쪽끝에 붙어있나 오른쪽끝에붙어있나
	STRUCT_VAR_BOOL(has_button)
	STRUCT_VAR_STR_ENUM_BEGIN(color)
		STRUCT_VAR_STR_ENUM_KEY(a)
		STRUCT_VAR_STR_ENUM_KEY(b)
		STRUCT_VAR_STR_ENUM_KEY(c)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()

STRUCT_NEW_BEGIN(PickerHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(start_qbu)
	STRUCT_VAR_VEC2(end_qbu)
	STRUCT_VAR_FLOAT(rod_length_qbu)
	STRUCT_VAR_BOOL(has_button)
	STRUCT_VAR_STR_ENUM_BEGIN(color)
		STRUCT_VAR_STR_ENUM_KEY(a)
		STRUCT_VAR_STR_ENUM_KEY(b)
		STRUCT_VAR_STR_ENUM_KEY(c)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()
STRUCT_NEW_BEGIN(RotatingPickerHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu) //몸통중심위치
	STRUCT_VAR_FLOAT(angle_deg) //각도, 아래를 향하는 방향이 0도
	STRUCT_VAR_BOOL(rotate_ccw) //회전방향, true 면 반시계방향 false면 시계방향
STRUCT_END()

STRUCT_NEW_BEGIN(FloorHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_FLOAT(x_qbu)
	STRUCT_VAR_FLOAT(y_qbu)
	STRUCT_VAR_FLOAT(width_qbu)
	STRUCT_VAR_FLOAT(height_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
STRUCT_END()


STRUCT_BEGIN(BeltHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_FLOAT(x_qbu)
	STRUCT_VAR_FLOAT(y_qbu)
	STRUCT_VAR_FLOAT(width_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_FLOAT(initial_speed_qbups)
STRUCT_END()

STRUCT_NEW_BEGIN(BeltHeader, 2)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_FLOAT(x_qbu)
	STRUCT_VAR_FLOAT(y_qbu)
	STRUCT_VAR_FLOAT(width_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_FLOAT(initial_speed_qbups)
	STRUCT_VAR_BOOL(has_button)
STRUCT_END()

STRUCT_NEW_BEGIN(SpikeHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_a_qbu)
	STRUCT_VAR_VEC2(pos_b_qbu)
STRUCT_END()


STRUCT_NEW_BEGIN(BalloonHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(CoinHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()


STRUCT_NEW_BEGIN(DispenserHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(dispense_delay)	//delay=0이면 클릭으로 생성하는거, 0보다 크면 시간기반으로 생성하는거
	STRUCT_VAR_STRING(dispense_type)	//어떤 물체를 뱉는가?
	STRUCT_VAR_INT(dispense_num)	 //최대 뱉는갯수 -1일경우 무제한
STRUCT_END()

STRUCT_NEW_BEGIN(CylinderScaleHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)
	
	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(left)
	STRUCT_VAR_FLOAT(right)
	STRUCT_VAR_FLOAT(width)
STRUCT_END()

STRUCT_NEW_BEGIN(JumpRampHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle)
STRUCT_END()

STRUCT_BEGIN(BoostHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle)
STRUCT_END()

STRUCT_NEW_BEGIN(BoostHeader, 2)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle)
	STRUCT_VAR_FLOAT(velocity_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(RevoluteJointHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(body_name) //a-b 를 가지면 두개연결 body_name을가지면 ground_static과 연결

	STRUCT_VAR_VEC2(anchor_qbu)
	STRUCT_VAR_BOOL(enable_limit)
	STRUCT_VAR_BOOL(enable_motor)
	STRUCT_VAR_FLOAT(lower_angle)
	STRUCT_VAR_FLOAT(upper_angle)
	STRUCT_VAR_FLOAT(motor_speed_deg)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()


STRUCT_NEW_BEGIN(RopeJointHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(body_a_name)
	STRUCT_VAR_STRING(body_b_name)

	STRUCT_VAR_VEC2(anchor_a_qbu)
	STRUCT_VAR_VEC2(anchor_b_qbu)
	STRUCT_VAR_FLOAT(length)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()


STRUCT_NEW_BEGIN(LinearJointHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(body_name) 
	
	STRUCT_VAR_VEC2(anchor)
	STRUCT_VAR_FLOAT(angle_rad)
	STRUCT_VAR_FLOAT(min_qbu)
	STRUCT_VAR_FLOAT(max_qbu)
	STRUCT_VAR_BOOL(enable_motor)
	STRUCT_VAR_FLOAT(motor_speed_qbu)
	STRUCT_VAR_BOOL(repeat)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(ButtonHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_STRING_LIST(trigger_list)
	STRUCT_VAR_STRING(image)
STRUCT_END()

STRUCT_NEW_BEGIN(ReverseGravityHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(ReverseElectroHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(PortalHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle_deg) //입구가 하늘을 향한 방향이 0도
STRUCT_END()

STRUCT_NEW_BEGIN(PortalConnectionHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(portal_a)
	STRUCT_VAR_STRING(portal_b)
	STRUCT_VAR_VEC2(pos_qbu) //에디터에서만 쓰는 값
STRUCT_END()

STRUCT_NEW_BEGIN(SwitchHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)
	
	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_STRING_LIST(trigger_list)
	STRUCT_VAR_STR_ENUM_BEGIN(color)
		STRUCT_VAR_STR_ENUM_KEY(random)
		STRUCT_VAR_STR_ENUM_KEY(red)
		STRUCT_VAR_STR_ENUM_KEY(yellow)
		STRUCT_VAR_STR_ENUM_KEY(blue)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()

STRUCT_NEW_BEGIN(TimerHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)
	
	STRUCT_VAR_VEC2(pos_qbu) //위치값 일단은 에디터에서만사용
							 //나중에 맵에 시간경과 등을 표시해줘야한다면 이값을 사용하자
	STRUCT_VAR_STRING_LIST(trigger_list)
							 
	STRUCT_VAR_INT(repeat_count) // 음수면 무한
	STRUCT_VAR_FLOAT(time_interval) // >0
STRUCT_END()

STRUCT_NEW_BEGIN(FanHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle) 
STRUCT_END()

STRUCT_NEW_BEGIN(RocketHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle_deg) //위를 향하는 방향이 0도
STRUCT_END()

STRUCT_NEW_BEGIN(TriggerHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STR_ENUM_BEGIN(condition_type)
		STRUCT_VAR_STR_ENUM_KEY(begin_contact)
		STRUCT_VAR_STR_ENUM_KEY(end_contact)
		STRUCT_VAR_STR_ENUM_KEY(during_contact)
		STRUCT_VAR_STR_ENUM_KEY(during_no_contact)
		STRUCT_VAR_STR_ENUM_KEY(begin_touch)
		STRUCT_VAR_STR_ENUM_KEY(end_touch)
	STRUCT_VAR_STR_ENUM_END()
	STRUCT_VAR_STRING(action_name)
	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()


STRUCT_NEW_BEGIN(ActionSetEnableMovePatternHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(pattern_name)
	STRUCT_VAR_BOOL(enable)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

//다양한 Object에 넣을수있는 통합 Action
//Belt - var1값으로 speed값조정
//Dispenser - 물체뱉기
STRUCT_NEW_BEGIN(ActionOperateHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(target_name)
	STRUCT_VAR_FLOAT(var1)
	STRUCT_VAR_FLOAT(var2)

	STRUCT_VAR_VEC2(pos_qbu)
STRUCT_END()

STRUCT_NEW_BEGIN(SubMovePatternHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(qbu_pos)
	STRUCT_VAR_FLOAT(delta_angle)
	STRUCT_VAR_FLOAT(duration)
STRUCT_END()

STRUCT_NEW_BEGIN(MovePatternHeader, 1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_FLOAT(inf_rotate_vel)	//무한회전의 각속도. 0이면 회전 없는거
	STRUCT_VAR_STRING_LIST(sub_list)
	STRUCT_VAR_VEC2(anchor)
	STRUCT_VAR_STRING(body_name)
	STRUCT_VAR_BOOL(inf_loop)
	STRUCT_VAR_BOOL(init_run)	//게임 시작되는 순간부터 작동할것인가?
	STRUCT_VAR_BOOL(draw_rail) //이동경로 레일을 그릴껀가
STRUCT_END()

STRUCT_NEW_BEGIN(PopupHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_STRING_LIST(on_list) //시작 시 on되어있는 기믹 리스트
	STRUCT_VAR_STRING_LIST(off_list) //시작 시 off되어있는 기믹 리스트
	STRUCT_VAR_STR_ENUM_BEGIN(color)
		STRUCT_VAR_STR_ENUM_KEY(r)
		STRUCT_VAR_STR_ENUM_KEY(g)
		STRUCT_VAR_STR_ENUM_KEY(b)
	STRUCT_VAR_STR_ENUM_END()
STRUCT_END()

STRUCT_NEW_BEGIN(ImageHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_STRING(file_name)
	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_BOOL(flip)
	STRUCT_VAR_FLOAT(init_alpha)
STRUCT_END()

STRUCT_NEW_BEGIN(FingerHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_BOOL(flip)
	STRUCT_VAR_FLOAT(init_alpha)
	STRUCT_VAR_BOOL(play_ani)
STRUCT_END()

STRUCT_NEW_BEGIN(ActionChangeAlphaHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_STRING_LIST(target_list) //Comment, Image, Finger만 연결됨
	STRUCT_VAR_FLOAT(duration) //최종 alpha 값까지 duration 시간동안 변화
	STRUCT_VAR_FLOAT(goal_alpha) //최종 alpha 값
STRUCT_END()

STRUCT_NEW_BEGIN(TriggerAreaHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_FLOAT(angle_deg)
	STRUCT_VAR_FLOAT(width)
	STRUCT_VAR_FLOAT(height)
	STRUCT_VAR_STRING_LIST(trigger_list)
STRUCT_END()

STRUCT_NEW_BEGIN(ActionFingerAniHeader,1)
	STRUCT_VAR_INT(type)
	STRUCT_VAR_STRING(name)

	STRUCT_VAR_VEC2(pos_qbu)
	STRUCT_VAR_STRING(finger_name)
	STRUCT_VAR_BOOL(is_press) //true면 누르는 애니, false면 떼는 애니 재생.
STRUCT_END()
////////////////////////////////////