#ifndef _TCSTATE_H_
#define _TCSTATE_H_

#include "TcCommons.h"

namespace ai {
	namespace tc {
		class TcState : public State {
		public:
			int X;
			int Y;
			int Z;
			int Charge;
		
			TcState();
			TcState(int x, int y, int z, int charge);
			TcState(const TcState& state);
			
			virtual ~TcState();
			virtual void Display() const;
			virtual bool IsEqual(const State* const state) const;
			
			TcState& operator=(const TcState& state);
		};
	}
}

#endif
