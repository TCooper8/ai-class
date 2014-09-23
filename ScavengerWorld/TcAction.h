#ifndef _TCACTION_H_
#define _TCACTION_H_

#include "TcCommons.h"
#include <string>
#include <functional>

namespace ai {
	namespace tc {
		class TcAction : public Action {
		public:
			enum T {
				None,
				Quit,
				North,
				South,
				East,
				West
			};
			
			const TcAction::T Type;
			const std::string Name;
			const std::function<State*(const State* const)> Func;
		
			TcAction(
				const std::string name,
				const TcAction::T type, 
				const std::function<State*(const State* const)> func
				);
				
			TcAction(const TcAction& action);
			virtual ~TcAction();
			
			virtual void Display() const;
			
			State* Apply(const State* const state) const;
		};
		
		class TcLightAction : public Action {
		public:
			const TcAction::T Type;
			const char* Name;
			
			TcLightAction(const TcAction::T type, const char* name);
			TcLightAction(const TcAction& action);
			
			virtual ~TcLightAction();
			
			virtual void Display() const;
		};
	}
}

#endif
