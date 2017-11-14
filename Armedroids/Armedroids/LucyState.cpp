#include "LucyState.h"
#include "headers.h"


// Idle state------------------------------------
LucyIdle* LucyIdle::Instance()
{
	static LucyIdle instance;

	return &instance;
}

void LucyIdle::Enter(Lucy* lucy)
{
}

void LucyIdle::Execute(Lucy* lucy)
{
}

void LucyIdle::Exit(Lucy* lucy)
{
}
// ----------------------------------------------


// Move state------------------------------------
LucyMove* LucyMove::Instance()
{
	static LucyMove instance;

	return &instance;
}

void LucyMove::Enter(Lucy* lucy)
{
}

void LucyMove::Execute(Lucy* lucy)
{
}

void LucyMove::Exit(Lucy* lucy)
{
}
// ----------------------------------------------


// Attack state----------------------------------
LucyAttack* LucyAttack::Instance()
{
	static LucyAttack instance;

	return &instance;
}

void LucyAttack::Enter(Lucy* lucy)
{
}

void LucyAttack::Execute(Lucy* lucy)
{
}

void LucyAttack::Exit(Lucy* lucy)
{
}
// ----------------------------------------------


// Damaged state---------------------------------
LucyDamaged* LucyDamaged::Instance()
{
	static LucyDamaged instance;

	return &instance;
}

void LucyDamaged::Enter(Lucy* lucy)
{
}

void LucyDamaged::Execute(Lucy* lucy)
{
}

void LucyDamaged::Exit(Lucy* lucy)
{
}
// ----------------------------------------------