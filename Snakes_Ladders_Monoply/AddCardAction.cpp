#include "AddCardAction.h"

#//include "card9.h"

AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer

	// Initialize cardNumber and cardPosition to default values
	pManager = pApp;
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Input* pIn = pManager->GetGrid()->GetInput();
	Output* pOut = pManager->GetGrid()->GetOutput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Enter card number (1-12): ");

	cardNumber = pIn->GetInteger(pOut);

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Select the cell");
	/*do
	{
		cardPosition = pIn->GetCellClicked();
	} while (cardPosition.GetCellNum() == 1 || cardPosition.GetCellNum() == 99);*/
	cardPosition = pIn->GetCellClicked();
	while (cardPosition.GetCellNum() == 1 || cardPosition.GetCellNum() == 99) {
		pManager->GetGrid()->PrintErrorMessage("Error! You cannot add cards at the Starting or the Ending Cell | Click to continue..");
		pOut->PrintMessage("Select another Cell");
		cardPosition = pIn->GetCellClicked();
	}

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type

	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;

		// A- Add the remaining cases
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new CardSeven(cardPosition);
		break;
	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:

		pCard = new CardNine(cardPosition);

		break;
	case 10:
		pCard = new CardTen(cardPosition);
		break;
	case 11:
		pCard = new CardEleven(cardPosition);
		break;
	case 12:
		pCard = new CardTwelve(cardPosition);
		break;
	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{

		// A- We get a pointer to the Grid from the ApplicationManager
		Grid* pGrid = pManager->GetGrid();
		Output* pOutput = pGrid->GetOutput();

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
		pCard->ReadCardParameters(pGrid);
		// C- Add the card object to the GameObject of its Cell:

		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar

		if (pGrid->AddObjectToCell(pCard))
		{
			pOutput->PrintMessage("Card Added");
		}
		else
			pOutput->PrintMessage("Invalid Cell");

	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}