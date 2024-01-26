#pragma once
#include "Card.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

template<typename T1, typename T2, typename T3>
constexpr auto MAX3(T1 x, T2  y, T3  z) { return ((x) > (y) ? ((x) > (z) ? (x) : (z)) : ((y) > (z) ? (y) : (z))); }

class  CardTwelve :public Card
{

public:
	CardTwelve(const CellPosition& pos);
	CardTwelve();
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual Card* GetCopy(const CellPosition&);

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file


};