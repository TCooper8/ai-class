#
#
#
our $aps =
[
 {
   name => 'Snorlax',
   key  => 's',
   header => 'Snorlax.h',
   cpp    => ['Snorlax.cpp'],
   constructor => 'ai::Sample::Snorlax(opts)',
 },
 {
   name => 'TcAgent',
   key  => 't',
   header => 'TcAgent.h',
   cpp    => [ 'TcAction.cpp', 'TcAgent.cpp', 'TcWorld.cpp', 'TcProblem.cpp', 'TcCell.cpp', 'TcState.cpp', 'TcPerceptState.cpp' ],
   constructor => 'ai::tc::TcAgent(opts)',
 },
 {
   name => 'Manual',
   key  => 'm',
   header => 'Manual.h',
   cpp    => ['Manual.cpp'],
   constructor => 'ai::Sample::Manual()',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
