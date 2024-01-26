#pragma once

#include "Grid.h"
#include "Cell.h"

enum attacks { Ice, Fire, Poison, Lightning };
class Player
{
	Cell * pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	                       // player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	                       // and reset again when reached 3
	                       // it is used to indicate when to move and when to add to your wallet
	attacks type;
	bool isIce;
	bool isFire;
	bool isPoison;
	bool isLightning;

	bool IsBurnt;
	int burningCounter;

	bool IsPoisoned;
	int poisoncounter;

	bool IsIced;
	int freezCounter;

	bool IsLightned;

	int specialAttackCounter;

	bool ExtraDice;
	bool RollValid[3];
	int InvalidRoll_Counter;
	int NextTurnCounter;
	
public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet
	int GetDiceRolled();

	int GetTurnCount() const;		// A getter for the turnCount
	int GetplayerNum() const;

	void setNextTurn(int);
	int GetNextTurn();
	int getPlayerNum() const;

	bool IsRollValid();
	void SetInValidRoll(int);

	void isExtraDice(bool);
	///TODO: You can add setters and getters for data members here (if needed)
	void setturnCount(int count);
	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)


	/*Setters for attack types*/
	void setIce(bool isIce);
	void setFire(bool isFire);
	void setPoison(bool isPoison);
	void setLightning(bool isLightning);

	/*Checking if the attack type is used*/
	bool isIceUsed();
	bool isFireUsed();
	bool isPoisonUsed();
	bool isLightningUsed();


	/*Check if the player has applied on him the special attack*/

	bool isBurnt(bool isBurnt);
	void isIced(bool ice);
	void isPois(bool pois);

	bool SpecialAttacks(Grid* pGrid);
};

