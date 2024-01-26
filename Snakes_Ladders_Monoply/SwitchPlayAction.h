#pragma once
#include "action.h"
class SwitchPlayAction :
	public Action
{
	Output* pOut;
public:
	SwitchPlayAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // Reads AddLadderAction action parameters (startPos, endPos)

	virtual void Execute(); // Creates a new Ladder Object 
	// then Sets this Ladder object to the GameObject Pointer of its Cell
	virtual~SwitchPlayAction(void);
};
