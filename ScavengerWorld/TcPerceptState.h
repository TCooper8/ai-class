#ifndef _TCPERCEPTSTATE_H_
#define _TCPERCEPTSTATE_H_

#include <vector>
#include <ai_scavenger.h>
#include "TcCommons.h"
#include "TcCell.h"
#include "TcCellInterfaceT.h"

namespace ai {
	namespace tc {
		class TcPerceptState {
		private:
			float charge;
			float hp;
			int xPos, yPos, zPos;
			int baseId;
			int goalX, goalY, goalZ;
			const char* look;
			std::vector<TcCell> cells; 
			std::vector<const char*> examine;
		
		public:
			TcPerceptState();
			TcPerceptState(const ai::Agent::Percept* percept, bool getCells);
			~TcPerceptState();
			
			void PushPercept(const ai::Agent::Percept* const percept, bool getCells);
			
			float GetCharge() const;
			float GetHP() const;
			int GetXPos() const;
			int GetYPos() const;
			int GetZPos() const;
			int GetBaseId() const;
			int GetGoalX() const;
			int GetGoalY() const;
			int GetGoalZ() const;
			const char* GetLook() const;
			std::vector<TcCell> GetCells() const;
			std::vector<const char*> GetExamine() const;
			
		private:
			void ParseGoalLoc(const char* input);
			int TranslateCoord(double v) const;
			TcCellInterface::T LexInterface(const char* str) const;
		};
	}
}

#endif
