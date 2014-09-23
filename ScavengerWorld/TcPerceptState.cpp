
#include <iostream>
#include "TcPerceptState.h"

namespace ai {
	namespace tc {
	
		TcPerceptState::TcPerceptState() {
		}
	
		TcPerceptState::TcPerceptState(const ai::Agent::Percept* percept, bool getCells) {
			this->PushPercept(percept, getCells);
		}
		
		void TcPerceptState::PushPercept(const ai::Agent::Percept* percept, bool getCells) {
		
			this->xPos = TranslateCoord(
				atof(percept->GetAtom("X_LOC").GetValue().c_str())
				);
			this->yPos = TranslateCoord(
				atof(percept->GetAtom("Y_LOC").GetValue().c_str())
				);
			this->zPos = TranslateCoord(
				atof(percept->GetAtom("Z_LOC").GetValue().c_str())
				);
				
			this->charge = atof(percept->GetAtom("CHARGE").GetValue().c_str());
			
			std::cout << percept->GetAtom("BASE").GetValue() << std::endl;
			this->baseId = atoi(percept->GetAtom("BASE").GetValue().c_str());
				
			const char* goalPercept = percept->GetAtom("GOAL_LOC").GetValue().c_str();
			this->ParseGoalLoc(goalPercept);
		
			if (getCells) {
				for (unsigned int i = 0; i < percept->NumAtom(); i++) {
				
					ai::Agent::PerceptAtom a = percept->GetAtom(i);
					
					if (std::strncmp(a.GetName().c_str(), "CELL_", 5) == 0) {
						int id;
						double x, y, z;
						
						std::sscanf(a.GetName().c_str(), "CELL_%d", &id);
						const char* v = a.GetValue().c_str();
						
						char* values = new char[std::strlen(v) + 1];
						std::strcpy(values, v);
						
						char* s = std::strtok(values, ",");
						x = atof(s);
						
						s = std::strtok(NULL, ",");
						y = atof(s);
						
						s = std::strtok(NULL, ",");
						z = atof(s);
						
						char* north = std::strtok(NULL, ",");
						char *south = std::strtok(NULL, ",");
						char *east  = std::strtok(NULL, ",");
						char *west  = std::strtok(NULL, ",");
						
						delete [] values;
						
						
						this->cells.push_back(
							TcCell(
								id,
								TranslateCoord(x),
								TranslateCoord(y),
								TranslateCoord(z),
								LexInterface(north),
								LexInterface(south),
								LexInterface(east),
								LexInterface(west)
							)
						);
					}
				}
			}
		}
		
		TcPerceptState::~TcPerceptState() {
			for (const char* it : examine) {
			}
		}
		
		float TcPerceptState::GetCharge() const {
			return charge;
		}
		
		float TcPerceptState::GetHP() const {
			return hp;
		}
		
		int TcPerceptState::GetXPos() const {
			return xPos;
		}
		
		int TcPerceptState::GetYPos() const {
			return yPos;
		}
		
		int TcPerceptState::GetZPos() const {
			return zPos;
		}
		
		int TcPerceptState::GetBaseId() const {
			return baseId;
		}
		
		int TcPerceptState::GetGoalX() const {
			return goalX;
		}
		
		int TcPerceptState::GetGoalY() const {
			return goalY;
		}
		
		int TcPerceptState::GetGoalZ() const {
			return goalZ;
		}
		
		const char* TcPerceptState::GetLook() const {
			return look;
		}
		
		std::vector<TcCell> TcPerceptState::GetCells() const {
			return cells;
		}
		
		std::vector<const char*> TcPerceptState::GetExamine() const {
			return examine;
		}
		
		int TcPerceptState::TranslateCoord(double v) const {
			//return (int)(v / 1000.0);
			return (v > 0) ? (int)((v+1.0)/1000.0) : (int)((v-1.0)/1000.0);
		}
		
		void TcPerceptState::ParseGoalLoc(const char* input) {
			double x, y, z;
			
			char* values = new char[std::strlen(input) + 1];
			std::strcpy(values, input);
			
			char* s = std::strtok(values, ",");
			x = atof(s);
			
			s = std::strtok(NULL, ",");
			y = atof(s);
			
			s = std::strtok(NULL, ",");
			z = atof(s);
			
			this->goalX = TranslateCoord(x);
			this->goalY = TranslateCoord(y);
			this->goalZ = TranslateCoord(z);
		}
		
		TcCellInterface::T TcPerceptState::LexInterface(const char* str) const {
			if (strcmp(str, "plain") == 0) return TcCellInterface::Plain;
			else if (strcmp(str, "rock") == 0) return TcCellInterface::Rock;
			else if (strcmp(str, "cliff") == 0) return TcCellInterface::Cliff;
			else if (strcmp(str, "wall") == 0) return TcCellInterface::Wall;
			else if (strcmp(str, "mud") == 0) return TcCellInterface::Mud;
			else return TcCellInterface::Cliff;
		}
	}
}
