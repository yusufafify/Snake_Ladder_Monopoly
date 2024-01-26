#pragma once
#include "Card.h"
#include "Player.h"

#include "UI_Info.h"
#include "Input.h"


#pragma once

#include "CardNineToEleven.h"




class CardTen :public CardNineToEleven
{


	static int Price_CardTen;
	static int fees_CardTen;
	static Player* cOwner_CardTen;




public:



	CardTen(const CellPosition& pos);
	CardTen();
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	static Player* get_cOwner();
	static int getPrice();
	static void set_cOwner(Player* pplayer);
	static Card* get_Copy(const CellPosition& pos);

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);

};

