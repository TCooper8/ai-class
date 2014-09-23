#ifndef _TCPROBLEM_H_
#define _TCPROBLEM_H_

#include "ai_search.h"
#include "TcWorld.h"
#include "TcCommons.h"
#include "TcAction.h"
#include "TcState.h"

namespace ai {
	namespace tc {
		class TcProblem : public ai::Search::Problem {
		private:
			TcWorld* world;
			TcState goal;
			std::vector<TcAction*> actions;
		
		public:
			TcProblem(State* state);
			TcProblem(ai::Search::State *initialState, TcWorld* world);
			virtual ~TcProblem();
			
			virtual bool GoalTest(
				const State* const state
				) const;
			
			virtual bool FindSuccessors(
				const State* const state,
				std::vector<ActionStatePair>& results
				) const;
				
			virtual double StepCost(
				const State* const stateA,
				const Action* const action,
				const State* const stateB
				) const;
				
			virtual double Heuristic(
				const State* const state
				) const;
				
			void SetGoal(const TcState& state);
			void AddAction(TcAction* action);
			
		private:
			bool IsValidInterface(TcCellInterface::T i) const;
			bool IsValidDirInterface(TcAction::T a, const TcCell& cell) const;
		};
	} 
}

#endif
