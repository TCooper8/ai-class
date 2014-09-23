
#include <ai_agent.h>

#include "Snorlax.h"
#include "TcAgent.h"
#include "Manual.h"

namespace ai
{
  namespace Agent
  {
    AgentProgram *AgentProgramSelect(Options *opts)
    {
      AgentProgram *agent_program = 0;
      switch(opts->GetArgChr("agent"))
        {
        case 's':
          agent_program = new ai::Sample::Snorlax(opts);
          break;
        case 't':
          agent_program = new ai::tc::TcAgent(opts);
          break;
        case 'm':
          agent_program = new ai::Sample::Manual();
          break;

        default:
          std::cout << "Unknown agent program " << std::endl
                    << "s : Snorlax" << std::endl
                    << "t : TcAgent" << std::endl
                    << "m : Manual" << std::endl
      
		    << std::endl;
          exit(1);
          break;
        }
      return agent_program;
    }
  }
}
