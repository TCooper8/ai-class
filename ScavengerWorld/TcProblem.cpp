#include "ai_search.h"
#include "TcProblem.h"
#include "TcPerceptState.h"

namespace ai {
	namespace tc {
		TcProblem::TcProblem(State* state)
			: ai::Search::Problem(state)
		{
		}
	
		TcProblem::TcProblem(ai::Search::State* state, TcWorld* world)
			: ai::Search::Problem(state) { 
			this->world = world;
		}
		
		TcProblem::~TcProblem() 
		{ }
		
		bool TcProblem::GoalTest(const State* const stateIn) const {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			
			return 
				state->Charge > 0 && 
				this->goal.IsEqual(state);
		}
		
		bool TcProblem::FindSuccessors(
			const State* const stateIn,
			std::vector<ActionStatePair>& results
				) const {
			
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			
			TcCell cell;
			if (world->GetCell(state->X, state->Y, cell)) {
				
				for (TcAction* action : actions) {
					if (IsValidDirInterface(action->Type, cell)) {
					
						Action* lAct = (Action*)(new TcLightAction(*action));
						ActionStatePair pair(action->Apply(stateIn), lAct);
						results.push_back(pair);
					}
				}
			} 
			
			return results.size() > 0;	
		}
		
		double TcProblem::StepCost(
			const State* const stateA,
			const Action* const action,
			const State* const stateB
				) const {
			
			return 1.0;		
		}
		
		double TcProblem::Heuristic(const State* const state) const {
			return 0.0;
		}
		
		void TcProblem::SetGoal(const TcState& state) {
			this->goal = state;
		}
		
		void TcProblem::AddAction(TcAction* action) {
			this->actions.push_back(action);
		}
		
		bool TcProblem::IsValidInterface(TcCellInterface::T i) const {
			switch (i) {
				case TcCellInterface::Mud:
				case TcCellInterface::Plain: 
					return true;
				case TcCellInterface::Rock:
					return true;
				default:
					return false;
			}
		}
		
		bool TcProblem::IsValidDirInterface(TcAction::T a, const TcCell& cell) const {
			switch(a) {
				case TcAction::North:
					return IsValidInterface(cell.North);
				case TcAction::South:
					return IsValidInterface(cell.South);
				case TcAction::East:
					return IsValidInterface(cell.East);
				case TcAction::West:
					return IsValidInterface(cell.West);
				default:
					return false;
			}
		}
	}
}







