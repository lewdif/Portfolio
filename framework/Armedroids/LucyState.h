#pragma once
#include "State.h"

class Lucy;

// Idle state------------------------------------
class LucyIdle : public State<Lucy>
{
	LucyIdle() {	}

	LucyIdle(const LucyIdle&);
	LucyIdle& operator = (const LucyIdle&);

public:

	//this is a singleton
	static LucyIdle* Instance();

	virtual void Enter(Lucy* lucy);

	virtual void Execute(Lucy* lucy);

	virtual void Exit(Lucy* lucy);
};
// ----------------------------------------------

// Move state------------------------------------
class LucyMove : public State<Lucy>
{
	LucyMove() {	}

	LucyMove(const LucyMove&);
	LucyMove& operator = (const LucyMove&);

public:

	//this is a singleton
	static LucyMove* Instance();

	virtual void Enter(Lucy* lucy);

	virtual void Execute(Lucy* lucy);

	virtual void Exit(Lucy* lucy);
};
// ----------------------------------------------

// Attack state----------------------------------
class LucyAttack : public State<Lucy>
{
	LucyAttack() {	}

	LucyAttack(const LucyAttack&);
	LucyAttack& operator = (const LucyAttack&);

public:

	//this is a singleton
	static LucyAttack* Instance();

	virtual void Enter(Lucy* lucy);

	virtual void Execute(Lucy* lucy);

	virtual void Exit(Lucy* lucy);
};
// ----------------------------------------------

// Damaged state---------------------------------
class LucyDamaged : public State<Lucy>
{
	LucyDamaged() {	}

	LucyDamaged(const LucyDamaged&);
	LucyDamaged& operator = (const LucyDamaged&);

public:

	//this is a singleton
	static LucyDamaged* Instance();

	virtual void Enter(Lucy* lucy);

	virtual void Execute(Lucy* lucy);

	virtual void Exit(Lucy* lucy);
};
// ----------------------------------------------