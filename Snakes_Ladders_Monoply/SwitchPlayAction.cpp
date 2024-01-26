#include "SwitchPlayAction.h"
#include "Grid.h"

SwitchPlayAction::SwitchPlayAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchPlayAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	pOut = pGrid->GetOutput();


}

void SwitchPlayAction::Execute()
{
	this->ReadActionParameters();
	pOut->PrintMessage("Do you Wish to change to Play Mode? y/n: ");
	string choice = pManager->GetGrid()->GetInput()->GetSrting(pOut);
	if (choice == "y" || choice == "Y") {
		pOut->CreatePlayModeToolBar();
		pOut->ClearStatusBar();
	}
	else {
		pOut->ClearStatusBar();
		return;
	}


}

SwitchPlayAction::~SwitchPlayAction(void)
{
}
