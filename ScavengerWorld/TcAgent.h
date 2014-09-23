#ifndef _TCAGENT_H_
#define _TCAGENT_H_

#include <ai_scavenger.h>
#include <queue>
#include "TcCommons.h"
#include "TcState.h"
#include "TcAction.h"
#include "TcCellInterfaceT.h"
#include "TcWorld.h"
#include "TcProblem.h"

namespace ai
{
  namespace tc
  {
  	class AgentState {
  	public:
  		enum T {
  			SearchGoal,
  			SearchBase,
  			FollowPathIgnorant,
  			Waiting,
  			Quiting
  		};
  	};
  
    class TcAgent : public ai::Agent::AgentProgram
    {
    	enum SearchT {
    		GRAPH,
    		TREE
    	};
    	
    	enum FringeT {
    		BFS,
    		DFS,
    		UCS,
    		DLS
    	};
    
    public:
      TcAgent(ai::Agent::Options *opts);
      ~TcAgent();
      virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
      
    protected:
    private:
    
    	ai::Agent::Action* BranchSearchGoal();
    	ai::Agent::Action* BranchSearchBase();
    	ai::Agent::Action* BranchFollowPathIgnorant();
    	ai::Agent::Action* BranchWaiting();
    	ai::Agent::Action* BranchQuitting();
    
    	static State* northFunc(const State* const);
    	static State* southFunc(const State* const);
    	static State* eastFunc(const State* const);
    	static State* westFunc(const State* const);
    
    	AgentState::T state;
    	TcState startState;
    	TcState goalState;
    	SearchT searchT;
    	FringeT fringeT;
    	int dlsDepth;
    	
    	TcWorld world;
    	std::queue<TcAction::T> actionQueue;
    	bool fullyObservableWorld;
    	bool flagWatchPercepts;
    	
    	std::vector<TcAction*> actions;
    };
  }
}

#endif
