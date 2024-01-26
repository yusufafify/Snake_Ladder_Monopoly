#pragma once

#include "Action.h"
#include <iostream>
#include "Input.h"
#include "Output.h"
#include "Ladder.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include"CardFive.h"
#include"CardSix.h"
#include"CardSeven.h"
#include"CardEight.h"
#include "CardEleven.h"
#include "CardTen.h"
#include "CardNine.h"
#include "CardTwelve.h"


class AddCardAction : public Action
{
	// [Action Parameters]
	int cardNumber;            // 1- the card number
	CellPosition cardPosition; // 2- cell position of the card

	// Note: These parameters should be read in ReadActionParameters()

public:
	AddCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	// and Reads the Parameters of This Card Number (if any)
	// then Sets this Card Object to GameObject Pointer of its Cell

	virtual ~AddCardAction(); // A Virtual Destructor
};
