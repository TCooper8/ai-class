#include <iostream>
#include "TcCell.h"

namespace ai {
	namespace tc {
		TcCell::TcCell(
			int id,
			int x, int y, int z,
			TcCellInterface::T north,
			TcCellInterface::T south,
			TcCellInterface::T east,
			TcCellInterface::T west)
			: Id(id),
			  X(x), Y(y), Z(z),
			  North(north), South(south),
			  East(east), West(west)
		{ }
		
		TcCell::TcCell(const TcCell& cell)
			: Id(cell.Id), 
			  X(cell.X), Y(cell.Y), Z(cell.Z),
			  North(cell.North), South(cell.South),
			  East(cell.East), West(cell.West)
		{ }
		
		void TcCell::Display() const {
			std::cout 
				<< "Cell("
				<< Id << ','
				<< X << ','
				<< Y << ','
				<< Z << ','
				<< North << ','
				<< South << ','
				<< East << ','
				<< West << ')'
				<< std::endl;
		}
		
		TcCell& TcCell::operator=(const TcCell& cell) {
			this->Id = cell.Id;
			this->X = cell.X;
			this->Y = cell.Y;
			this->Z = cell.Z;
			this->North = cell.North;
			this->South = cell.South;
			this->East = cell.East;
			this->West = cell.West;
			
			return *this;
		}
	}
}
