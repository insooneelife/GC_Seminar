#include "EntityManager.h"
#include <chrono>

#include <iostream>

using namespace std::chrono;

std::unique_ptr<EntityManager> EntityManager::instance = nullptr;

void EntityManager::staticInit()
{
	instance.reset(new EntityManager());
}

EntityManager::EntityManager()
{
	_start_time = system_clock::now().time_since_epoch();
}

Entity* EntityManager::getEntity(unsigned int id) const
{
	auto ent = _entities.find(id);

	if (std::end(_entities) != ent)
	{
		return ent->second;
	}

	return nullptr;
}

bool EntityManager::exists(unsigned int id) const
{
	auto ent = _entities.find(id);

	if (std::end(_entities) != ent)
	{
		return true;
	}

	return false;
}

void EntityManager::registerEntity(Entity* entity)
{
	_entities.emplace(entity->getID(), entity);
}

void EntityManager::unregisterEntity(Entity* entity)
{
	_entities.erase(entity->getID());
}

void EntityManager::dispatchMsg(
	double delay,
	unsigned int senderId,
	unsigned int receiverId,
	Message::MsgType msgType,
	void* extraInfo)
{
	// Get a pointer to the receiver
	Entity* receiver = getEntity(receiverId);

	// Make sure the receiver is valid
	if (receiver == nullptr)
		return;

	// Create the telegram
	Message msg(0.0f, senderId, receiverId, msgType, extraInfo);

	// If there is no delay, route telegram immediately                       
	if (delay <= 0.0)
	{
		// Send the telegram to the recipient
		discharge(receiver, msg);
	}

	// Else calculate the time when the telegram should be dispatched.
	else
	{
		duration<double> current_time = system_clock::now().time_since_epoch();
		duration<double> delay_time = current_time - _start_time;

		msg.setDispatchTime(delay_time.count() + delay);

		//and put it in the queue
		_pque.push(msg);
	}

}

// This method is utilized by DispatchMsg or DispatchDelayedMessages.
// This method calls the message handling member function of the receiving
// entity, pReceiver, with the newly created telegram
void EntityManager::discharge(Entity* receiver, const Message& msg)
{
	if (receiver == nullptr)
		return;

	if (!receiver->handleMessage(msg))
	{}
}


void EntityManager::dispatchDelayedMessages()
{
	// First get current time
	duration<double> current_time = system_clock::now().time_since_epoch();
	duration<double> delay_time = current_time - _start_time;

	// Now peek at the queue to see if any telegrams need dispatching.
	// remove all telegrams from the front of the queue that have gone
	// past their sell by date
	while (!_pque.empty() &&
		(_pque.top().getDispatchTime() < delay_time.count()) &&
		(_pque.top().getDispatchTime() > 0))
	{
		//read the telegram from the front of the queue
		const Message& msg = _pque.top();

		//find the recipient
		Entity* const receiver = getEntity(msg.getReceiver());

		//send the telegram to the recipient
		discharge(receiver, msg);

		//remove it from the queue
		_pque.pop();
	}
}