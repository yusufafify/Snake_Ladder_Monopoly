#pragma once

#include "CardNineToEleven.h"




class CardNine :public CardNineToEleven
{


	static int Price_CardNine;
	static int fees_CardNine;
	static Player* cOwner;




public:



	CardNine(const CellPosition& pos);
	CardNine();
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	static Player* get_cOwner();
	static int getPrice();
	static Card* get_Copy(const CellPosition& pos);
	static void set_cOwner(Player* pplayer);

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);


};

