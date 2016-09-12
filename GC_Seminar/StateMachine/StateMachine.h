#pragma once
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30	// or whatever you need               
#define BOOST_MPL_LIMIT_MAP_SIZE 30		// or whatever you need 

#include <iostream>
#include <functional>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace 
{
	// This one is for visitor
	template <class Entity>
	struct AbstState
	{
		// signature of the accept function
		typedef msm::back::args<void, Entity&> accept_sig;

		// we also want polymorphic states
		virtual ~AbstState() {}

		// default implementation for states who do not need to be visited
		void accept(Entity&) {}
	};

	// Needs to give AbstState in state machine too.
	template <class Entity>
	struct Fsm_
		:
		public msm::front::state_machine_def<Fsm_<Entity>, AbstState<Entity> >
	{
		template <class Event, class FSM>
		void on_entry(Event const&, FSM&)
		{
			std::cout << "enter: [Wolf FSM]" << std::endl;
		}

		template <class Event, class FSM>
		void on_exit(Event const&, FSM&)
		{
			std::cout << "exit: [Wolf FSM]" << std::endl;
		}

		// Events
		template<class Entity> 
		struct inState
		{
			inState(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct hasDestination 
		{
			hasDestination(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct arrive 
		{
			arrive(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct enemyInView 
		{
			enemyInView(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct enemyOutView 
		{
			enemyOutView(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct enemyInRange 
		{
			enemyInRange(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct readyToAttack 
		{
			readyToAttack(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct doneAttack 
		{
			doneAttack(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct enemyOutRange 
		{
			enemyOutRange(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct hasToDie 
		{
			hasToDie(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		template<class Entity>
		struct hasToDead 
		{
			hasToDead(Entity& entity) : owner(entity) {}
			Entity& owner;
		};

		// States
		// Inherits AbstState for visit
		struct Patrol : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [Patrol]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [Patrol]" << std::endl; }

			void accept(Entity& owner) 
			{
				if (owner.getMove().getHasDestination())
				{
					owner.getFsm().process_event(hasDestination<Entity>(owner));
					return;
				}

				Entity* target = owner.getTargetSys().updateTarget();
				if (owner.getTargetSys().isViewable())
				{
					owner.getMove().setDestination(target->getPos());
					owner.getFsm().process_event(enemyInView<Entity>(owner));
				}

				std::cout << "accept: [Patrol]" << std::endl; 
			}
		};

		struct AttackToDestination : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [AttackToDestination]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [AttackToDestination]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [AttackToDestination]" << std::endl; }
		};

		struct ChaseEnemy : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [ChaseEnemy]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [ChaseEnemy]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [ChaseEnemy]" << std::endl; }
		};

		struct Attack : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [Attack]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [Attack]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [Attack]" << std::endl; }
		};

		struct WaitForNextAttack : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [WaitForNextAttack]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [WaitForNextAttack]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [WaitForNextAttack]" << std::endl; }
		};

		struct Dying : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [Dying]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [Dying]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [Dying]" << std::endl; }
		};

		struct Dead : public msm::front::state<AbstState<Entity>>
		{
			template <class Event, class FSM>
			void on_entry(Event const&, FSM&) { std::cout << "enter: [Dead]" << std::endl; }

			template <class Event, class FSM>
			void on_exit(Event const&, FSM&) { std::cout << "exit: [Dead]" << std::endl; }

			void accept(Entity& owner) { std::cout << "accept: [Dead]" << std::endl; }
		};

		// Initial state
		typedef Patrol initial_state;

		struct transition_table
			:
			mpl::vector
			<
			//		  Start					Event					Next 	
			//+--------------------------------------------------------------------------------+
			_row	< Patrol,				inState<Entity>,		Patrol>,
			_row	< Patrol,				hasDestination<Entity>, AttackToDestination>,
			_row	< Patrol,				enemyInView<Entity>,	ChaseEnemy>,
			_row	< Patrol,				hasToDie<Entity>,		Dying>,
			//+--------------------------------------------------------------------------------+
			_row	< AttackToDestination,	inState<Entity>,		AttackToDestination>,
			_row	< AttackToDestination,	arrive<Entity>,			Patrol >,
			_row	< AttackToDestination,	enemyInView<Entity>,	ChaseEnemy >,
			_row	< AttackToDestination,	hasToDie<Entity>,		Dying>,
			//+--------------------------------------------------------------------------------+
			_row	< ChaseEnemy,			inState<Entity>,		ChaseEnemy>,
			_row	< ChaseEnemy,			enemyOutView<Entity>,	AttackToDestination >,
			_row	< ChaseEnemy,			enemyInRange<Entity>,	Attack >,
			_row	< ChaseEnemy,			hasToDie<Entity>,		Dying>,
			//+--------------------------------------------------------------------------------+
			_row	< Attack,				inState<Entity>,		Attack>,
			_row	< Attack,				doneAttack<Entity>,		WaitForNextAttack >,
			_row	< Attack,				hasToDie<Entity>,		Dying>,
			//+--------------------------------------------------------------------------------+
			_row	< WaitForNextAttack,	inState<Entity>,		WaitForNextAttack>,
			_row	< WaitForNextAttack,	enemyOutRange<Entity>,	Patrol >,
			_row	< WaitForNextAttack,	readyToAttack<Entity>,	Attack >,
			_row	< WaitForNextAttack,	hasToDie<Entity>,		Dying>,
			//+--------------------------------------------------------------------------------+
			_row	< Dying,				inState<Entity>,		Dying>,
			_row	< Dying,				hasToDead<Entity>,		Dead >
			//+--------------------------------------------------------------------------------+
			> {};
	};

	// Testing utilities.
	static char const* const state_names[] =
	{
		"Patrol", "AttackToDestination", "ChaseEnemy",
		"Attack", "WaitForNextAttack", "Dying", "Dead"
	};

	template<typename T>
	const char* toString(const T& s)
	{
		return state_names[s.current_state()[0]];
	}
};