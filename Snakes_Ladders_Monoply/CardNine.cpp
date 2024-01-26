#include "CardNine.h"


int CardNine::fees_CardNine = 0;
int CardNine::Price_CardNine = 0;

//Player* CardNine::cOwner_CardNine = nullptr;

Player* CardNine::cOwner = NULL;




CardNine::CardNine(const CellPosition& pos) : CardNineToEleven(pos)
{
    cardNumber = 9;





}

CardNine::CardNine()
{
	cardNumber = 9;

}

void CardNine::ReadCardParameters(Grid* pGrid)
{
    CardNineToEleven::ReadCardParameters(pGrid, Price_CardNine, fees_CardNine, cOwner);
}



void CardNine::Apply(Grid* pGrid, Player* pPlayer) {
    CardNineToEleven::Apply(pGrid, pPlayer, Price_CardNine, fees_CardNine, cOwner);
}

Player* CardNine::get_cOwner()
{
    return cOwner;
}

int CardNine::getPrice()
{
    return Price_CardNine;
}

Card* CardNine::get_Copy(const CellPosition& pos)
{
    return new CardNine(pos);

}

void CardNine::set_cOwner(Player* pplayer)
{
    cOwner = pplayer;
}


void CardNine::Save(ofstream& outFile, Type gameObj)
{
	if (gameObj == CARDS)
	{
		Card::Save(outFile, gameObj);


		outFile << Price_CardNine << ' ' << fees_CardNine << std::endl;

	}
}

void CardNine::Load(ifstream& InFile) {
	Card::Load(InFile);

	int price;
	int rent;

	InFile >> price >> rent;
	Price_CardNine = price;
	fees_CardNine = rent;

}