#pragma once
#include "Action.h"

class InputDiceAction : public Action
{
	int diceNumber;
	// No parameters for this action

public:

	InputDiceAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceAction();
};

