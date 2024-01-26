#pragma once

#include "GameObject.h"

class Ladder :	public GameObject // inherited from GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

	CellPosition endCellPos; // here is the ladder's End Cell Position

public:

	Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos); // A constructor for initialization
	Ladder();
	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetPosition() const; // A getter for the endCellPos data member

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	virtual void Save(ofstream& OutFile, Type type);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed

	virtual ~Ladder(); // Virtual destructor
	virtual void Load(ifstream& InFile);
};

