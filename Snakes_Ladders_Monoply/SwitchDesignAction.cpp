#include "SwitchDesignAction.h"
#include"Grid.h"

SwitchDesignAction::SwitchDesignAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchDesignAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	pOut = pGrid->GetOutput();

}

void SwitchDesignAction::Execute()
{
	this->ReadActionParameters();
	pOut->PrintMessage("Do you Wish to change to Design Mode? y/n: ");
	string choice = pManager->GetGrid()->GetInput()->GetSrting(pOut);
	if (choice == "y" || choice == "Y") {
		pOut->CreateDesignModeToolBar();
		pOut->ClearStatusBar();
	}
	else {
		pOut->ClearStatusBar();
		return;
	}
	// Executes action (code depends on action type so virtual)
}


SwitchDesignAction::~SwitchDesignAction(void)
{
}