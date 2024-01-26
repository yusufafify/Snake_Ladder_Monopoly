#include "CardNineToEleven.h"

CardNineToEleven::CardNineToEleven(const CellPosition& pos) :Card(pos)
{

}

CardNineToEleven::CardNineToEleven()
{
}

void CardNineToEleven::ReadCardParameters(Grid* pGrid, int& Price, int& fees, Player*& cOwner)
{

    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();

    if (Price == 0 && fees == 0) {

        do {

            pOut->PrintMessage("Enter a valid the price of Card" + std::to_string(cardNumber) + " : ");
            Price = pIn->GetInteger(pOut);

        } while (Price < 0);

        do {
            do {
                pOut->PrintMessage("Enter a the valid fees to pay by passing players: ");
                fees = pIn->GetInteger(pOut);
            } while (fees >= Price);
        } while (fees < 0);

        pOut->ClearStatusBar();

    }
}

void CardNineToEleven::Apply(Grid* pGrid, Player* pPlayer, int& Price, int& fees, Player*& cOwner)
{
    Output* pOut = pGrid->GetOutput();
    Input* pIn = pGrid->GetInput();
    Card::Apply(pGrid, pPlayer);

    if (cOwner == nullptr)
    {
        pGrid->GetOutput()->PrintMessage("Do you want to buy this cell and all cells containing the same card " + std::to_string(cardNumber) + "? (1-Yes, 0-No)");
        int choice = pIn->GetInteger(pOut);
        if (choice == 1) {
            // IsValid = true;
            cOwner = pPlayer;
            pPlayer->SetWallet(pPlayer->GetWallet() - Price);

        }
        else {
            pGrid->GetOutput()->PrintMessage("Card has not been purchased");

        }

    }
    else if (cOwner != pPlayer) {
        pPlayer->SetWallet(pPlayer->GetWallet() - fees);
        cOwner->SetWallet(cOwner->GetWallet() + fees);
    }
}