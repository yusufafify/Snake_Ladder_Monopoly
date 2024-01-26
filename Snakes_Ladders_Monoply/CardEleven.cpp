#include "CardEleven.h"

int CardEleven::Price_CardEleven = 0;
int CardEleven::fees_CardEleven = 0;
Player* CardEleven::cOwner_CardEleven = NULL;
CardEleven::CardEleven(const CellPosition& pos) : CardNineToEleven(pos)
{
	cardNumber = 11;
}

CardEleven::CardEleven()
{
	cardNumber = 11;

}

void CardEleven::ReadCardParameters(Grid* pGrid)
{
	CardNineToEleven::ReadCardParameters(pGrid, Price_CardEleven, fees_CardEleven, cOwner_CardEleven);
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	CardNineToEleven::Apply(pGrid, pPlayer, Price_CardEleven, fees_CardEleven, cOwner_CardEleven);
}

Player* CardEleven::get_cOwner()
{
	return cOwner_CardEleven;
}

int CardEleven::getPrice()
{
	return Price_CardEleven;
}

Card* CardEleven::get_Copy(const CellPosition& pos)
{
	return new CardEleven(pos);
}

void CardEleven::set_cOwner(Player* pplayer)
{
	cOwner_CardEleven = pplayer;
}

void CardEleven::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);


			outFile <<Price_CardEleven << ' ' << fees_CardEleven << std::endl;

	}
}

void CardEleven::Load(ifstream& InFile) {
	Card::Load(InFile);
	
		int price;
		int rent;

		InFile >> price >> rent;
		Price_CardEleven = price;
		fees_CardEleven = rent;
	
}