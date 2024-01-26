#pragma once

#include "Card.h"

class CardSeven : public Card
{


public:
	CardSeven(const CellPosition& pos); // A Constructor takes card position
	CardSeven();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	// by decrementing the player's wallet by the walletAmount data member

	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);

	virtual ~CardSeven(); // A Virtual Destructor
};

