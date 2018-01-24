#pragma once
#include "State.h"
//#include <string>

template <class entityType>
class StateMachine
{
private:

	//a pointer to the agent that owns this instance
	entityType*          owner;

	State<entityType>*   currentState;

	//a record of the last state the agent was in
	State<entityType>*   previousState;

	//this is called every time the FSM is updated
	State<entityType>*   globalState;


public:

	StateMachine(entityType* owner) :owner(owner), currentState(NULL),
		previousState(NULL), globalState(NULL)
	{
	}

	virtual ~StateMachine() {}

	//use these methods to initialize the FSM
	void SetCurrentState(State<entityType>* s)	{ currentState = s; }
	void SetGlobalState(State<entityType>* s)	{ globalState = s; }
	void SetPreviousState(State<entityType>* s)	{ previousState = s; }

	//call this to update the FSM
	void  Update()const
	{
		//if a global state exists, call its execute method, else do nothing
		if (globalState)   globalState->Execute(owner);

		//same for the current state
		if (currentState) currentState->Execute(owner);
	}

	//change to a new state
	void  ChangeState(State<entityType>* pNewState)
	{
		assert(pNewState && "<StateMachine::ChangeState>:trying to assign null state to current");

		//keep a record of the previous state
		previousState = currentState;

		//call the exit method of the existing state
		currentState->Exit(owner);

		//change state to the new state
		currentState = pNewState;

		//call the entry method of the new state
		currentState->Enter(owner);
	}

	//change state back to the previous state
	void  RevertToPreviousState()
	{
		ChangeState(previousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	bool isInState(const State<entityType>& st)const
	{
		if (typeid(*currentState) == typeid(st)) return true;
		return false;
	}

	State<entityType>* CurrentState()	const { return currentState; }
	State<entityType>* GlobalState()	const { return globalState; }
	State<entityType>* PreviousState()	const { return previousState; }

	//only ever used during debugging to grab the name of the current state
	/*std::string GetNameOfCurrentState()const
	{
		std::string s(typeid(*currentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}*/
};