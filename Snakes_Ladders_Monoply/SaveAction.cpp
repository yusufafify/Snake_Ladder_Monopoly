#include "SaveAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"


SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	pManager = pApp;
}


void SaveAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Name the file to save: ");
	FileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void SaveAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	ofstream OutFile(FileName + ".txt");

		OutFile << pGrid->GetNumberOfGameObject(LADDERS) << std::endl;
		pGrid->SaveObjects(OutFile, LADDERS);

		OutFile <<pGrid->GetNumberOfGameObject(SNAKES) << std::endl;
		pGrid->SaveObjects(OutFile, SNAKES);

		OutFile <<pGrid->GetNumberOfGameObject(CARDS) << std::endl;
		pGrid->SaveObjects(OutFile, CARDS);

;

	OutFile.close();
}