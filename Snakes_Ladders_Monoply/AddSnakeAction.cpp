#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
	check = true;
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	Snake* pSnake = new Snake(startPos, endPos);


	///TODO: Make the needed validations on the read parameters

	if (startPos.VCell() > endPos.VCell()) {
		pGrid->PrintErrorMessage("Error: The start vCell value is smaller than the end vCell value, please choose valid cell positions | click to continue...");
		pOut->ClearStatusBar();
		check = false;
		return;
	}

	if (startPos.HCell() != endPos.HCell()) {
		pGrid->PrintErrorMessage("Error: The start hCell value and the end hCell value are not the same, please choose valid cell positions | click to continue...");
		pOut->ClearStatusBar();
		check = false;
		return;
	}

	if (startPos.GetCellNum() == endPos.GetCellNum())
	{
		pGrid->PrintErrorMessage("ERROR: It is not possible for Start Cell and End Cell to be the same. | Click to continue ...");
		pOut->ClearStatusBar();
		check = false;
		return;
	}


	if (startPos.GetCellNum() == 99)
	{
		pGrid->PrintErrorMessage("ERROR: It is not possible to add any game object on the first cell or on the last cell! Click to continue ...");
		pOut->ClearStatusBar();
		check = false;
		return;
	}

	if (pGrid->isSnakeOverlap(pGrid, startPos, endPos)) {
		check = false;
	}


	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (!check) {
		return;
	}

	// Create a Ladder object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
