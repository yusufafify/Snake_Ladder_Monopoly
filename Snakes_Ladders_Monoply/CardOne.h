#pragma once

#include "Card.h"

// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardOne :	public Card
{
	// CardOne Parameters:
	int walletAmount; // the wallet value to decrease from the player

public:
	CardOne(const CellPosition & pos); // A Constructor takes card position
	CardOne();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
	                         
	virtual void Save(ofstream& outFile, Type gameObj); //Saves the start cell and the end cell of Snake in a file

	virtual void Load(ifstream& InFile);
	
	// by decrementing the player's wallet by the walletAmount data member
	virtual ~CardOne(); // A Virtual Destructor

};

