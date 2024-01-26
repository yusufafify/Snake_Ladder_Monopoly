#pragma once
#include "Action.h"
class CutCardAction : public Action
{
	CellPosition cutcell;



public:
	CutCardAction(ApplicationManager* pApp);

	void ReadActionParameters();

	void Execute();


	CutCardAction();
	virtual ~CutCardAction();
};

