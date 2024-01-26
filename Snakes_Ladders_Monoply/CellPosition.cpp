#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{

	///TODO: Implement this function as described in the .h file (don't forget the validation)
	vCell = -1;
	bool flag = false;
	if ((v >= 0) && (v <= 8)) {
		vCell = v;
		flag = true;
	}

	return flag; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	hCell = -1;
	bool flag = false;
	if ((h >= 0) && (h <= 10)) {
		flag = true;
		hCell = h;
	}

	return flag; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	///TODO: Implement this function as described in the .h file
	bool flag = false;
	if ((vCell >= 0) && (vCell <= 8) && (hCell >= 0) && (hCell <= 10))
	{
		flag = true;
	}

	return flag; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}
const int Cell_Reff = 89;
int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file

	int eq;

	if ((cellPosition.vCell >= 0) && (cellPosition.vCell <= 8) && (cellPosition.hCell >= 0) && (cellPosition.hCell <= 10)) {
		eq = Cell_Reff + cellPosition.hCell - cellPosition.vCell * NumHorizontalCells; //Using NumHorizontaCells pre defined constant as our constant number 11.
	}
	else {
		eq = -1;
	}
	return eq; // this line should be changed with your implementation

	//-->   Assuming that // hCell (right):   0    1   ...   10
						  // vCell (below):
						 //    0             C89  C90  ...  C99
						  //   1             C78  C79  ...  C88
						  //  ...            ...  ...  ...  ...
						  //   7             C12  C13  ...  C22
						  //   8             C1   C2   ...  C11  
/*--> we can see that cell 89 is at 0 and 0 vertical and horizontal
so lets say we have 89 as a constant number and our reference to the cells 89+0+0 this is the equation we could assume now to get cell 89.
lets try cell 78 which is at 0 h and 1 v --> 89+0+1--> this gives us 90 not 78, what  gives us 78 is if we subtracted 11 from the eq and 11
is our count of horizontal cells so 89+0-1*11=78
lets try again to check trying c12 which is at 7 v and 0 h--> 89+0-7*11=12. Therefore the derived equation for the cell number from there position is 89+hCell-Vcell*11  */
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file

	if (cellNum % 11 != 0)
	{
		position.SetVCell(8 - cellNum / 11);
		position.SetHCell((cellNum % 11) - 1);
	}
	else
	{
		position.SetVCell(9 - cellNum / 11);
		position.SetHCell(10);
	}

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file

	int newCellNum = GetCellNum() + addedNum;
	CellPosition newCellPos = GetCellPositionFromNum(newCellNum);

	// Update the vertical and horizontal cell positions of the current object with the new cell position
	SetVCell(newCellPos.VCell());
	SetHCell(newCellPos.HCell());



	// Note: this function updates the data members (vCell and hCell) of the calling object

}

void CellPosition::DecCellNum(int DecNum)
{
	int newCellNum = GetCellNum() - DecNum;
	CellPosition newCellPos = GetCellPositionFromNum(newCellNum);

	// Update the vertical and horizontal cell positions of the current object with the new cell position
	SetVCell(newCellPos.VCell());
	SetHCell(newCellPos.HCell());

}
