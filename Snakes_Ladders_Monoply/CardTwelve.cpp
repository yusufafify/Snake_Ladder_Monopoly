#include "CardTwelve.h"

CardTwelve::CardTwelve(const CellPosition& pos) :Card(pos)
{
	cardNumber = 12;
}

CardTwelve::CardTwelve()
{
	cardNumber = 12;

}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	if (CardNine::get_cOwner() != pPlayer && CardTen::get_cOwner() != pPlayer && CardEleven::get_cOwner() != pPlayer)
	{
		pOut->PrintMessage("You own no crads");
		return;
	}

	if (pGrid->GetPoorestPlayer() == pPlayer)
	{
		pOut->PrintMessage("OH Dear! you are already the poorest Player!");
		return;
	}
	else if (CardNine::get_cOwner() == pPlayer || CardTen::get_cOwner() == pPlayer || CardEleven::get_cOwner() == pPlayer)
	{


		int NeededCard = MAX3((pGrid->GetCurrentPlayer() == CardNine::get_cOwner()) ? CardNine::getPrice() : 0, (pGrid->GetCurrentPlayer() == CardTen::get_cOwner()) ? CardTen::getPrice() : 0, (pGrid->GetCurrentPlayer() == CardEleven::get_cOwner()) ? CardEleven::getPrice() : 0);

		if (CardNine::getPrice() == NeededCard&& (pGrid->GetCurrentPlayer() == CardNine::get_cOwner()))
		{
			CardNine::set_cOwner(pGrid->GetPoorestPlayer());
			pGrid->PrintErrorMessage("Card transferred");
			pGrid->PrintErrorMessage("P" + to_string(pGrid->GetPoorestPlayer()->GetplayerNum()) + " is now the Owner Of Card Nine | Click to Continue..");

		}
		else if (CardTen::getPrice() == NeededCard && (pGrid->GetCurrentPlayer() == CardTen::get_cOwner())) {

			CardTen::set_cOwner(pGrid->GetPoorestPlayer());
			pGrid->PrintErrorMessage("Card transferred");
			pGrid->PrintErrorMessage("P" + to_string(pGrid->GetPoorestPlayer()->GetplayerNum()) + " is now the Owner Of Card Ten | Click to Continue..");
		}
		else if (CardEleven::getPrice() == NeededCard && (pGrid->GetCurrentPlayer() == CardEleven::get_cOwner()))
		{

			CardEleven::set_cOwner(pGrid->GetPoorestPlayer());
			pGrid->PrintErrorMessage("Card transferred");
			pGrid->PrintErrorMessage("P" + to_string(pGrid->GetPoorestPlayer()->GetplayerNum()) + " is now the Owner Of Card Eleven | Click to Continue..");

		}

	}
}

Card* CardTwelve::GetCopy(const CellPosition& pos)
{

	return new CardTwelve(pos);
}

void CardTwelve::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);
		outFile << std::endl;
	}
}


