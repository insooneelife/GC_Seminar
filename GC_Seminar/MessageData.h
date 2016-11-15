#pragma once

struct MessageData
{
	enum Type
	{
		kNone, kCreateEntity, kHealEntity, kMoveEntity, kActivateTrigger
	};

	MessageData(int type) : type(type)
	{}

	int type;
};

struct CreateEntityData : public MessageData
{
	struct Member
	{
		Member(
			unsigned int creator_id,
			int entity_type,
			int breed_type,
			float wait_time)
			:
			creator_id(creator_id),
			entity_type(entity_type),
			breed_type(breed_type),
			wait_time(wait_time)
		{}

		unsigned int creator_id;
		int entity_type;
		int breed_type;
		float wait_time;
	};

	struct Param
	{
		Param() : x(0), y(0) {}
		Param(float x, float y) : x(x), y(y) {}
		float x, y;
	};

	inline void setParam(const Param& param) { this->param = param; }

	CreateEntityData(const Member& member)
		:
		MessageData(kCreateEntity),
		member(member)
	{}

	Member member;
	Param param;
};

struct HealEntityData : public MessageData
{
	struct Member
	{
		Member(unsigned int healer_id, int heal_hp)	: healer_id(healer_id),	heal_hp(heal_hp) {}
		unsigned int healer_id;
		int heal_hp;
	};

	struct Param
	{
		Param() : target_id(0) {}
		Param(unsigned int target_id) : target_id(target_id) {}
		unsigned int target_id;
	};

	inline void setParam(const Param& param) { this->param = param; }

	HealEntityData(const Member& member)
		:
		MessageData(kHealEntity),
		member(member)
	{}

	Member member;
	Param param;
};

struct MoveEntityData : public MessageData
{
	struct Member
	{
		Member(float destX, float destY) : destX(destX), destY(destY) {}
		float destX, destY;
	};

	struct Param
	{
		Param() : target_id(0) {}
		Param(unsigned int target_id) : target_id(target_id) {}
		unsigned int target_id;
	};

	inline void setParam(const Param& param) { this->param = param; }

	MoveEntityData(const Member& member)
		:
		MessageData(kMoveEntity),
		member(member)
	{}

	Member member;
	Param param;
};

struct ActivateTriggerData : public MessageData
{
	struct Member
	{
		Member(float wait_time) : wait_time(wait_time) {}
		float wait_time;
	};

	struct Param
	{
		Param() : target_id(0) {}
		Param(unsigned int target_id) : target_id(target_id) {}
		unsigned int target_id;
	};

	inline void setParam(const Param& param) { this->param = param; }

	ActivateTriggerData(Member member)
		:
		MessageData(kActivateTrigger),
		member(member)
	{}

	Member member;
	Param param;
};


