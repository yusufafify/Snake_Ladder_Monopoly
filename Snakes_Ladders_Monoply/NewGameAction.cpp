#include "NewGameAction.h"
#include "Player.h"
#include "GameObject.h"
#include"CardNineToEleven.h"
#include"CardNine.h"
#include"CardTen.h"
#include"CardEleven.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}
void NewGameAction::ReadActionParameters()

{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("New Game Press To Continue ...");

	pIn->GetCellClicked();   // Just To Give Time For User
	pOut->ClearStatusBar();
}


void NewGameAction::Execute()
{
	ReadActionParameters();

	Grid* g = pManager->GetGrid();
	CardNine* pCardN=NULL;
	CardTen* pCardT=NULL;
	CardEleven* pCardE=NULL;

	CellPosition startCell(8,0); //Intializes The CellPosition TO (8,0) " First Cell "
	g->GetCurrentPlayer();
	while (g->GetCurrentPlayer()->getPlayerNum())
	{
		g->AdvanceCurrentPlayer();
	}

	for (int i = 0; i < MaxPlayerCount; i++) //to check the 4 players

	{
		//pGrid->setcurrentPlayernum(i)//

		Player* pl = g->GetCurrentPlayer(); // Returns The Current Player* "Turn"

		pl->SetWallet(100);

		g->UpdatePlayerCell(pl, startCell);
		pl->setturnCount(0);////////////////set prevented and prisoned to false when cards are added
		pl->SetInValidRoll(0);
		pCardN->set_cOwner(NULL);
		pCardT->set_cOwner(NULL); 
		pCardE->set_cOwner(NULL);

		g->AdvanceCurrentPlayer(); // Turn + 1

	}
	//pGrid->setCurrentPlayernum(0);//
	g->SetEndGame(false);
	g->UpdateInterface();


	g->GetOutput()->CreatePlayModeToolBar(); //To Reset Values "Wallet etc.."

}

NewGameAction::~NewGameAction(void)
{
}