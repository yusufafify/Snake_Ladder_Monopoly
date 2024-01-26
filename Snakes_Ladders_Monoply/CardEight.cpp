#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (1 here)
}

CardEight::CardEight()
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (1 here)

}

CardEight::~CardEight(void)
{
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("New CardEight: Enter prison fee amount: ");
	PrisonFee = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	if (pPlayer->GetWallet() < PrisonFee)
	{
		pOut->PrintMessage("Busted!!! You are going to jail hahaha ");
		pPlayer->SetInValidRoll(3);
	}
	while (1)
	{
		pOut->PrintMessage("1- Pay the fees     2-Stay in prison for eternity!!! haha, Kidding, just for three turns");
			switch (pIn->GetInteger(pOut))
			{
			case 1:
				pPlayer->SetWallet(pPlayer->GetWallet() - PrisonFee);
				break;
			case 2:
				pPlayer->SetInValidRoll(3);
				break;
			default:
				pOut->PrintMessage("Choose a valid number you idiot!!");
				continue;
			}
			break;
	}
}


void CardEight::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);

			outFile << PrisonFee <<std::endl;
	}
}

void CardEight::Load(ifstream& InFile) {
	Card::Load(InFile);
		int price;

		InFile >> price;
		PrisonFee= price;
	
}