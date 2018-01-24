#pragma once


template <class entityType>

class State
{
public:
	virtual ~State() {}
	virtual void Enter(entityType*) = 0;
	virtual void Execute(entityType*) = 0;
	virtual void Exit(entityType*) = 0;
};