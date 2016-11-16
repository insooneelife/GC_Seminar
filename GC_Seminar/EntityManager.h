#pragma once
//------------------------------------------------------------------------
//
//  Name:		EntityManager.h
//
//  Desc:		For query entities by id and handle message between entities.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------


#include <map>
#include <memory>
#include <queue>
#include <chrono>
#include "Entity/GenericEntity.h"


class Message
{
public:
	enum MsgType
	{
		kNone, kIncrease, kDecrease, kDamage, kActivateTrigger
	};

	struct Compare
	{
		bool operator()(const Message& a, const Message& b)
		{
			return a.getDispatchTime() > b.getDispatchTime();
		}
	};

	// Handy helper function for dereferencing the getExtraInfo field of the Telegram to the required type.
	template <class T>
	static inline T voidToType(void* p) { return *static_cast<T*>(p); }

	// The entity that sent this telegram
	inline unsigned int getSender() const { return _sender; }
	inline unsigned int getReceiver() const { return _receiver; }
	inline MsgType getMsg() const { return _msg; }
	inline double getDispatchTime() const { return _dispatch_time; }
	inline void setDispatchTime(double time) { _dispatch_time = time; }
	inline void* getExtraInfo() const { return _extraInfo; }

	Message()
		:
		_sender(0),
		_receiver(0),
		_msg(MsgType::kNone),
		_dispatch_time(-1),
		_extraInfo(nullptr)
	{}

	Message(
		double dispatch_time,
		unsigned int sender,
		unsigned int receiver,
		MsgType msg,
		void* extraInfo = nullptr)
		:
		_sender(sender),
		_receiver(receiver),
		_msg(msg),
		_dispatch_time(dispatch_time),
		_extraInfo(extraInfo)
	{}

private:

	// The entity that sent this telegram
	unsigned int _sender;

	// The entity that is to receive this telegram
	unsigned int _receiver;

	// The message itself. These are all enumerated in the file
	MsgType _msg;

	double _dispatch_time;

	// Any additional information that may accompany the message
	void* _extraInfo;
};





class EntityManager
{
public:
	static void staticInit();
	static std::unique_ptr<EntityManager> instance;

	EntityManager();

	// Methods related with entity querying.
	GenericEntity* getEntity(unsigned int id) const;
	bool exists(unsigned int id) const;
	void registerEntity(GenericEntity* entity);
	void unregisterEntity(GenericEntity* entity);

	// Methods related with message dispatching.
	void dispatchMsg(
		double delay,
		unsigned int senderId,
		unsigned int receiverId,
		Message::MsgType msgType,
		void* extraInfo);

	inline void dispatchMsg(
		unsigned int senderId,
		unsigned int receiverId,
		Message::MsgType msgType,
		void* extraInfo)
	{
		return dispatchMsg(0.0f, senderId, receiverId, msgType, extraInfo);
	}

	// This method is utilized by DispatchMsg or DispatchDelayedMessages.
	// This method calls the message handling member function of the receiving
	// entity, pReceiver, with the newly created message
	void discharge(GenericEntity* receiver, const Message& msg);

	// In world update
	void dispatchDelayedMessages();

private:

	std::map <unsigned int, GenericEntity*> _entities;
	std::priority_queue<Message, std::vector<Message>, Message::Compare> _pque;
	std::chrono::duration<double> _start_time;
};
