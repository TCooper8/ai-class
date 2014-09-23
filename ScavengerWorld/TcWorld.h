#ifndef _TCWORLD_H_
#define _TCWORLD_H_

#include <map>
#include <utility>
#include "TcCell.h"
#include "TcPerceptState.h"

namespace ai {
	namespace tc {
		class TcWorld {
		private:
			std::map<std::pair<int, int>, TcCell> cellMap;
			std::map<int, std::pair<int, int>> idMap;
			
		public:
			TcPerceptState CurPercept;
			
			TcWorld();
			~TcWorld();
			
			void AddCell(const TcCell& cell);
			bool GetCell(const int x, const int y, TcCell& outRef) const;
			bool GetCellById(const int id, TcCell& outRef) const;
			
			void PushPercept(const ai::Agent::Percept* const percept, bool getCells);
			
		private:
			std::pair<int, int> HashCell(const TcCell& cell) const;
			std::pair<int, int> HashCoord(const int x, const int y) const;
		};
	}
}

#endif
