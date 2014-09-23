#include "TcWorld.h"
#include <utility>

namespace ai {
	namespace tc {
		TcWorld::TcWorld() { 
		}
		
		TcWorld::~TcWorld() {
		}
		
		void TcWorld::AddCell(const TcCell& cell) {
			std::pair<int, int> hash = this->HashCell(cell);
			
			cellMap.insert(
				std::pair<std::pair<int, int>, TcCell>(
					hash,
					TcCell(cell)
				)
			);
			
			idMap.insert(
				std::pair<int, std::pair<int, int>>(
					cell.Id, 
					hash
				)
			);
		}
		
		bool TcWorld::GetCell(const int x, const int y, TcCell& outRef) const {
			std::pair<int,int> index = this->HashCoord(x, y);
			std::map<std::pair<int, int>, TcCell>::const_iterator it;
			
			it = cellMap.find(index);
			if (it != cellMap.end()) {
				outRef = it->second;
				return true;
			}
			return false;
		}
		
		bool TcWorld::GetCellById(const int id, TcCell& outRef) const {
			std::map<int, std::pair<int, int>>::const_iterator it;
			
			it = this->idMap.find(id);
			if (it != this->idMap.end()) {
				return this->GetCell(it->second.first, it->second.second, outRef);
			}
			return false;
		}
		
		void TcWorld::PushPercept(const ai::Agent::Percept* const percept, bool getCells) {
			
		}
		
		std::pair<int, int> TcWorld::HashCell(const TcCell& cell) const {
			return this->HashCoord(cell.X, cell.Y);
		}
		
		std::pair<int, int> TcWorld::HashCoord(const int x, const int y) const {
			return std::pair<int, int>(x, y);
		}
	}
}
