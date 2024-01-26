#pragma once
#include "action.h"
class PasteCardAction :public Action
{

	CellPosition Newcell;

public:


	PasteCardAction(ApplicationManager* pApp);

	void ReadActionParameters();

	void Execute();



	virtual ~PasteCardAction(void);
};


