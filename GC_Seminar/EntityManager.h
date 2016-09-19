#pragma once

#include <map>
#include <memory>
#include "Entity.h"

class Message
{
public:
	enum MsgType
	{
		None, Damage
	};

	// Handy helper function for dereferencing the getExtraInfo field of the Telegram to the required type.
	template <class T>
	static inline T voidToType(void* p) { return *(T*)(p); }

	// The entity that sent this telegram
	unsigned int getSender() const		{ return _sender; }
	unsigned int getReceiver() const	{ return _receiver; }
	MsgType getMsg() const				{ return _msg; }
	void* getExtraInfo() const			{ return _extraInfo; }

	Message()
		:
		_sender(0),
		_receiver(0),
		_msg(MsgType::None),
		_extraInfo(nullptr)
	{}

	Message(
		unsigned int sender,
		unsigned int receiver,
		MsgType msg,
		void* extraInfo = nullptr)
		:
		_sender(sender),
		_receiver(receiver),
		_msg(msg),
		_extraInfo(extraInfo)
	{}

private:

	// The entity that sent this telegram
	unsigned int _sender;

	// The entity that is to receive this telegram
	unsigned int _receiver;

	// The message itself. These are all enumerated in the file
	MsgType _msg;

	// Any additional information that may accompany the message
	void* _extraInfo;
};





class EntityManager
{
public:
	enum { InvalidateId = 0 };

	static void staticInit();
	static std::unique_ptr<EntityManager> instance;

	EntityManager();
	unsigned int genID();

	// Methods related with entity querying.
	Entity* getEntity(unsigned int id) const;
	bool exists(unsigned int id) const;
	void registerEntity(Entity* entity);
	void unregisterEntity(Entity* entity);

	// Methods related with message dispatching.
	void dispatchMsg(
		unsigned int senderId,
		unsigned int receiverId,
		Message::MsgType msgType,
		void* extraInfo);

	// This method is utilized by DispatchMsg or DispatchDelayedMessages.
	// This method calls the message handling member function of the receiving
	// entity, pReceiver, with the newly created message
	void discharge(Entity* receiver, const Message& msg);

private:

	unsigned int _nextGenId;
	std::map <unsigned int, Entity*> _entities;
};
