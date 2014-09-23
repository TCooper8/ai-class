#include <iostream>
#include "TcAction.h"

namespace ai {
	namespace tc {
		TcAction::TcAction(
			const std::string name,
			const TcAction::T type,
			const std::function<State*(const State* const)> func
			) : Type(type), Name(name), Func(func) {
		}
		
		TcAction::TcAction(const TcAction& action)
			: Type(action.Type), Name(action.Name), Func(action.Func) {
		}
		
		TcAction::~TcAction() {
		}
		
		void TcAction::Display() const {
			std::cout 
				<< "Action("
				<< Type << ','
				<< Name << ')'
				<< std::endl;
		}
		
		State* TcAction::Apply(const State* const state) const {
			return Func(state);
		}
		
		TcLightAction::TcLightAction(const TcAction::T type, const char* name) 
			: Type(type), Name(name) {
		}
		
		TcLightAction::TcLightAction(const TcAction& action)
			: Type(action.Type), Name(action.Name.c_str()) {
		}
		
		TcLightAction::~TcLightAction() {
		}
		
		void TcLightAction::Display() const {
			std::cout << "Action(" << Name << ')' << std::endl;
		}
	}
}
