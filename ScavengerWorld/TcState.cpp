
#include "ai_search.h"
#include <iostream>
#include "TcState.h"

namespace ai {
	namespace tc {
		TcState::TcState()
		{ }
	
		TcState::TcState(int x, int y, int z, int charge)
			: X(x), Y(y), Z(z), Charge(charge)
		{ }
		
		TcState::TcState(const TcState& state) 
			: X(state.X), Y(state.Y), Z(state.Z), Charge(state.Charge)
		{ }
		
		TcState::~TcState()
		{ }
		
		void TcState::Display() const {
			std::cout 
				<< "State"
				<< '(' << X 
				<< ',' << Y 
				<< ',' << Z
				<< ',' << Charge 
				<< ')' << std::endl;
		}
		
		bool TcState::IsEqual(const State* const stateIn) const {
			const TcState* const state = dynamic_cast<const TcState* const>(stateIn);
			
			return 
				(X == state->X) &&
				(Y == state->Y);
		}
		
		TcState& TcState::operator=(const TcState& state) {
			X = state.X;
			Y = state.Y;
			Z = state.Z;
			Charge = state.Charge;
			
			return *this;
		}
	}
}
