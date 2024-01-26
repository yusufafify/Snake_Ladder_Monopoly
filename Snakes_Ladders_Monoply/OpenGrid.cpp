#include "OpenGrid.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include"CardOne.h"
#include"CardTwo.h"
#include"CardThree.h"
#include"CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"CardSeven.h"
#include"CardEight.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"
#include"CardTwelve.h"
#include <fstream>

OpenGrid::OpenGrid(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

OpenGrid::~OpenGrid()
{
}

void OpenGrid::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->ClearGridArea();
	pGrid->DeleteAllGameObjects();

	pOut->PrintMessage("Please enter the filename: ");
	FileName = pIn->GetSrting(pOut);

	pOut->ClearStatusBar();
}

void OpenGrid::Execute()
{

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ReadActionParameters();

	ifstream InFile(FileName + ".txt");

	if (!InFile) {
		pGrid->PrintErrorMessage("ERROR: This File does not exist! Click to continue ... ");
		return;
	}

	int nrOfLadders;
	InFile >> nrOfLadders;
	GameObject* pNewObject;

	for (int i = 0; i < nrOfLadders; i++)
	{
		pNewObject = new Ladder;
		pNewObject->Load(InFile);
		pGrid->AddObjectToCell(pNewObject);
	}

	int nrOfSnakes;
	InFile >> nrOfSnakes;
	for (int i = 0; i < nrOfSnakes; i++)
	{
		pNewObject = new Snake;
		pNewObject->Load(InFile);
		pGrid->AddObjectToCell(pNewObject);
	}

	int nrOfCards;
	InFile >> nrOfCards;
	for (int i = 0; i < nrOfCards; i++)
	{
		int CardNumber;
		InFile >> CardNumber;
		switch (CardNumber)
		{
		case 1:
			pNewObject = new CardOne;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 2:
			pNewObject = new CardTwo;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 3:
			pNewObject = new CardThree;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 4:
			pNewObject = new CardFour;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 5:
			pNewObject = new CardFive;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 6:
			pNewObject = new CardSix;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 7:
			pNewObject = new CardSeven;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 8:
			pNewObject = new CardEight;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 9:
			pNewObject = new CardNine;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 10:
			pNewObject = new CardTen;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 11:
			pNewObject = new CardEleven;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		case 12:
			pNewObject = new CardTwelve;
			pNewObject->Load(InFile);
			pGrid->AddObjectToCell(pNewObject);
			break;
		}
	}
	InFile.close();
	pGrid->UpdateInterface();

}