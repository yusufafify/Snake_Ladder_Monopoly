#pragma once

#include "CardNineToEleven.h"




class CardEleven :public CardNineToEleven
{


	static int Price_CardEleven;
	static int fees_CardEleven;
	static Player* cOwner_CardEleven;




public:




	CardEleven(const CellPosition& pos);
	CardEleven();
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);


	static Player* get_cOwner();
	static int getPrice();
	static Card* get_Copy(const CellPosition& pos);
	static void set_cOwner(Player* pplayer);
	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);

};

