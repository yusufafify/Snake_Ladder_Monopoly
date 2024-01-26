#pragma once
#include "action.h"
class SwitchDesignAction :
	public Action
{
	Output* pOut;
public:
	SwitchDesignAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (startPos, endPos)

	virtual void Execute();
	virtual~SwitchDesignAction(void);
};

