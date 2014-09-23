#ifndef _TCCELL_H_
#define _TCCELL_H_

#include "TcCellInterfaceT.h"

namespace ai {
	namespace tc {
		class TcCell {
		public:
			int Id, X, Y, Z;
			TcCellInterface::T North;
			TcCellInterface::T South;
			TcCellInterface::T East;
			TcCellInterface::T West;
		
			TcCell() { }
			TcCell(
				int id,
				int x, int y, int z, 
				TcCellInterface::T north,
				TcCellInterface::T south,
				TcCellInterface::T east,
				TcCellInterface::T west
				);
				
			TcCell(const TcCell& cell);
			
			void Display() const;
			TcCell& operator=(const TcCell& cell);
		};
	}
}

#endif
