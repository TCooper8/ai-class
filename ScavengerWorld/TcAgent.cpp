
#include <cstdio>
#include <cstring>
#include "TcAgent.h"
#include "TcPerceptState.h"

namespace ai
{
	namespace tc
	{
	        /* For more on options look at the files:
		 * ai-lib/include/Agent/Options.h
		 * ai-lib/src/Agent/Options.cpp
		 * al-lib/src/Agent/AgentDriver.cpp
		 */
	        /*
		 * Run with:
		 * ./RunProg ./SA_Test -a s -U 1
		 */
		TcAgent::TcAgent(ai::Agent::Options *opts)
		{
			SetName("TcAgent");
			std::cout << "The value of the -U option is: " << opts->GetArg("user1") << std::endl;
			
			std::string op = opts->GetArg("user1");
			
			/*this->fringeT = opts->GetArgInt("user1");
			this->searchT = opts->GetArgInt("user2");
			this->dlsDepth = opts->GetArgInt("user3");*/
			
			
			if (op == "BFS" || op == "bfs")
				this->fringeT = BFS;
			else if (op == "DFS" || op == "dfs")
				this->fringeT = DFS;
			else if (op == "UCS" || op == "ucs")
				this->fringeT = UCS;
			else if (op == "DLS" || op == "DLS") {
				this->fringeT = DLS;
				
				op = opts->GetArg("user3");
				
				if (op != "") 
					this->dlsDepth = atof(op.c_str());
				else
					this->dlsDepth = 25;
			}
			else 
				this->fringeT = BFS;
			
			op = opts->GetArg("user2");
			
			if (op == "GRAPH" || op == "graph")
				this->searchT = GRAPH;
			else 
				this->searchT = TREE;
			
			fullyObservableWorld = true;
			flagWatchPercepts = true;
			
			std::function<State*(const State* const)> fNorth = northFunc;
			std::function<State*(const State* const)> fSouth = southFunc;
			std::function<State*(const State* const)> fEast = eastFunc;
			std::function<State*(const State* const)> fWest = westFunc;
	
			TcAction* northAction = new TcAction("North", TcAction::North, fNorth);
			TcAction* southAction = new TcAction("South", TcAction::South, fSouth);
			TcAction* eastAction = new TcAction("East", TcAction::East, fEast);
			TcAction* westAction = new TcAction("West", TcAction::West, fWest);
			
			this->actions.push_back(northAction);
			this->actions.push_back(southAction);
			this->actions.push_back(eastAction);
			this->actions.push_back(westAction);
			
			this->state = AgentState::SearchGoal;
		}

		TcAgent::~TcAgent()
		{
		}

		ai::Agent::Action * TcAgent::Program(const ai::Agent::Percept * percept)
		{
			world.CurPercept.PushPercept(percept, true);
		
			switch (this->state) {
				case AgentState::SearchGoal:
					return this->BranchSearchGoal();
					
				case AgentState::SearchBase:
					return this->BranchSearchBase();
					
				case AgentState::FollowPathIgnorant:
					return this->BranchFollowPathIgnorant();
					
				default:
				case AgentState::Waiting:
					return this->BranchWaiting();
			}
		}
    	
    	ai::Agent::Action* TcAgent::BranchSearchGoal() {
			
			const TcPerceptState& p = world.CurPercept;
			
			int cX, cY, cZ; 
			cX = p.GetXPos();
			cY = p.GetYPos(); 
			cZ = p.GetZPos();
			
			int gX, gY, gZ; 
			gX = p.GetGoalX();
			gY = p.GetGoalY(); 
			gZ = p.GetGoalZ();
			
			std::cout << "CurrentPos:(" << cX << ',' << cY << ',' << cZ << ')' << std::endl;
			std::cout << "GoalPos:(" << gX << ',' << gY << ',' << gZ << ')' << std::endl;
			
			for (TcCell it : p.GetCells()) {
				world.AddCell(it);
			}
	
			TcState* startState = new TcState(cX, cY, cZ, p.GetCharge());
			TcState goalState = TcState(gX, gY, gZ, 0);
			
			this->startState = *startState;
			this->goalState = goalState;
	
			TcProblem* problem = new TcProblem(
				startState,
				&world
				);
		
			problem->SetGoal(goalState);
			
			for (TcAction* act : actions) {
				act->Display();
				problem->AddAction(act);
			}
	
			ai::Search::Fringe* fringe;
			
			switch (this->fringeT) {
				default:
				case BFS:
					std::cout << "Using fringe: BFS" << std::endl;
					fringe = new ai::Search::BFFringe();
					break;
				case DFS:
					std::cout << "Using fringe: DFS" << std::endl;
					fringe = new ai::Search::DFFringe();
					break;
				case UCS:
					std::cout << "Using fringe: UCS" << std::endl;
					fringe = new ai::Search::UCFringe();
					break;
				case DLS:
					std::cout << "Using fringe: DLS" << std::endl;
					fringe = new ai::Search::DLFringe(this->dlsDepth);
					break;
			}
			ai::Search::Algorithm* search;
			
			switch (this->searchT) {
				default:
				case GRAPH:
					std::cout << "Using search: Graph" << std::endl;
					search = (ai::Search::Algorithm*)(new ai::Search::Graph(problem, fringe));
					break;
				case TREE:
					std::cout << "Using search: Tree" << std::endl;
					search = (ai::Search::Algorithm*)(new ai::Search::Tree(problem, fringe));
					break;
			}
		
			std::cout << "Searching" << std::endl;
			if (search->Search()) {
				std::cout << "Found goal." << std::endl;
		
				std::list<ai::Search::Node*>* solution = search->GetSolution().GetList();
				std::list<ai::Search::Node*>::const_iterator it;
		
				for (it = solution->begin(); it != solution->end(); it++) {
					TcLightAction* action = dynamic_cast<TcLightAction*>((*it)->GetAction());
				
					if (action) {
						std::cout << "Pushing action: " << action->Type << std::endl;
						actionQueue.push(action->Type);
					}
				}
				delete search;
				search = 0;
					
				this->state = AgentState::FollowPathIgnorant;
				
				return this->BranchFollowPathIgnorant();
			} 
			else {
				delete search;
				search = 0;
				
				std::cout << "Unable to find goal" << std::endl;
				return this->BranchQuitting();
			}
    	}
    	
    	ai::Agent::Action* TcAgent::BranchSearchBase() {
			
			const TcPerceptState& p = world.CurPercept;
			
			int cX, cY, cZ; 
			cX = p.GetXPos();
			cY = p.GetYPos(); 
			cZ = p.GetZPos();
			
			std::cout << "CurrentPos:(" << cX << ',' << cY << ',' << cZ << ')' << std::endl;
			
			for (TcCell it : p.GetCells()) {
				world.AddCell(it);
			}
	
			TcState* curState = new TcState(cX, cY, cZ, p.GetCharge());

			TcProblem* problem = new TcProblem(
				curState,
				&world
				);
			
			for (TcAction* act : actions) {
				problem->AddAction(act);
			}
	
			problem->SetGoal(this->startState);

			ai::Search::Fringe* fringe;
		
			switch (this->fringeT) {
				default:
				case BFS:
					std::cout << "Using fringe: BFS" << std::endl;
					fringe = new ai::Search::BFFringe();
					break;
				case DFS:
					std::cout << "Using fringe: DFS" << std::endl;
					fringe = new ai::Search::DFFringe();
					break;
				case UCS:
					std::cout << "Using fringe: UCS" << std::endl;
					fringe = new ai::Search::UCFringe();
					break;
				case DLS:
					std::cout << "Using fringe: DLS" << std::endl;
					fringe = new ai::Search::DLFringe(this->dlsDepth);
					break;
			}
			ai::Search::Algorithm* search;
		
			switch (this->searchT) {
				default:
				case GRAPH:
					std::cout << "Using search: Graph" << std::endl;
					search = (ai::Search::Algorithm*)(new ai::Search::Graph(problem, fringe));
					break;
				case TREE:
					std::cout << "Using search: Tree" << std::endl;
					search = (ai::Search::Algorithm*)(new ai::Search::Tree(problem, fringe));
					break;
			}
	
			std::cout << "Searching" << std::endl;
			if (search->Search()) {
				std::cout << "Found goal." << std::endl;
	
				std::list<ai::Search::Node*>* solution = search->GetSolution().GetList();
				std::list<ai::Search::Node*>::const_iterator it;
	
				for (it = solution->begin(); it != solution->end(); it++) {
					TcLightAction* action = dynamic_cast<TcLightAction*>((*it)->GetAction());
			
					if (action) {
						std::cout << "Pushing action: " << action->Type << std::endl;
						actionQueue.push(action->Type);
					}
				}
				
				actionQueue.push(TcAction::T::Quit);
				
				delete search;
				search = 0;
				
				this->state = AgentState::FollowPathIgnorant;
			
				return this->BranchFollowPathIgnorant();
			} 
			else {
				delete search;
				search = 0;
			
				std::cout << "Unable to find goal" << std::endl;
			}
			
			std::cout << "Unable to find base from baseId" << std::endl;
			return this->BranchWaiting();
    	}
    	
    	ai::Agent::Action* TcAgent::BranchFollowPathIgnorant() {
			if (actionQueue.size() > 0) {
				ai::Scavenger::Action *action = new ai::Scavenger::Action;
				TcAction::T actionT = actionQueue.front();
			
				std::cout << "Taking action: " << actionT << std::endl;
			
				switch (actionT) {
					case TcAction::North:
						action->SetCode(ai::Scavenger::Action::GO_NORTH);
						break;
					case TcAction::South:
						action->SetCode(ai::Scavenger::Action::GO_SOUTH);
						break;
					case TcAction::West:
						action->SetCode(ai::Scavenger::Action::GO_WEST);
						break;
					case TcAction::East:
						action->SetCode(ai::Scavenger::Action::GO_EAST);
						break;
					case TcAction::Quit:
						action->SetCode(ai::Scavenger::Action::QUIT);
						break;
					default:
						break;
				}
				actionQueue.pop();
				
				return action;
			}
			return this->BranchWaiting();
    	}
    	
    	ai::Agent::Action* TcAgent::BranchWaiting() {
			ai::Scavenger::Action *action = new ai::Scavenger::Action;
			
			const TcPerceptState& p = world.CurPercept;
			
			int cX, cY, cZ; 
			cX = p.GetXPos();
			cY = p.GetYPos(); 
			cZ = p.GetZPos();
			
			for (TcCell it : p.GetCells()) {
				world.AddCell(it);
			}
			
			std::cout << "Current state: " << cX << ',' << cY << ')' << std::endl;
			
			/*for (TcCell it : p.GetCells()) {
				world.AddCell(it);
			}*/
			if (cX == goalState.X &&
				cY == goalState.Y) {
				
				std::cout << "Switching to look for base!" << std::endl;
				
				this->state = AgentState::SearchBase;
			}
			else {
				std::cout << "Current state is not goal." << std::endl;
			}
			
			return action;
    	}
    	
    	ai::Agent::Action* TcAgent::BranchQuitting() {
			ai::Scavenger::Action *action = new ai::Scavenger::Action;
			
			action->SetCode(ai::Scavenger::Action::QUIT);
			
			return action;
    	}
	
		State* TcAgent::northFunc(const State* const stateIn) {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			State* newState = (State*)(new TcState(state->X, state->Y+1, state->Z, state->Charge - 1));
			return newState;
		}
	
		State* TcAgent::southFunc(const State* const stateIn) {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			State* newState = (State*)(new TcState(state->X, state->Y-1, state->Z, state->Charge - 1));
			return newState;
		}
	
		State* TcAgent::eastFunc(const State* const stateIn) {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			State* newState = (State*)(new TcState(state->X+1, state->Y, state->Z, state->Charge - 1));
			return newState;
		}
	
		State* TcAgent::westFunc(const State* const stateIn) {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			State* newState = (State*)(new TcState(state->X-1, state->Y, state->Z, state->Charge - 1));
			return newState;
		}
	}
}




















