#include "InputDiceAction.h"
#include"Player.h"
#include "RollDiceAction.h"
#include"Grid.h"

InputDiceAction::InputDiceAction(ApplicationManager* pApp) : Action(pApp)
{
}

void InputDiceAction::ReadActionParameters()
{
}



void InputDiceAction::Execute()
{
	if (pManager->GetGrid()->GetEndGame())
		return;
	// -- If not ended, do the following --:

	{
		// 2- Generate a random number from 1 to 6 --> This step is done for you
		 // time is for different seed each run
		// from 1 to 6 --> should change seed

		// 3- Get the "current" player from pGrid
		Player* pPlayer;
		pPlayer = pManager->GetGrid()->GetCurrentPlayer();
		Output* pOut = pManager->GetGrid()->GetOutput();
		pOut->PrintMessage("For Player Number: " + to_string(pPlayer->GetplayerNum()) + ", Enter The Dice Value: ");
		int diceNumber = pManager->GetGrid()->GetInput()->GetInteger(pOut);
		while ((diceNumber < 0) || (diceNumber > 6)) {
			pOut->PrintMessage("Error! please enter a value between 0 and 6: ");
			diceNumber = pManager->GetGrid()->GetInput()->GetInteger(pOut);
		}
		// 4- Move the currentPlayer using function Move of class player

		pManager->GetGrid()->PrintErrorMessage("For Player Number: " + to_string(pPlayer->GetplayerNum()) + ", your Rolled dice Value is: " + to_string(diceNumber));

		pPlayer->Move(pManager->GetGrid(), diceNumber);


		// 5- Advance the current player number of pGrid
		pManager->GetGrid()->AdvanceCurrentPlayer();

		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).

	}
}

InputDiceAction::~InputDiceAction()
{}
