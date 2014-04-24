#include <unittest++/UnitTest++.h>
#include "ParserState.hpp"
#include "SyntaxConstraint.hpp"

using namespace glPortal::map::parser;
TEST(getIsValidPrerequisiteStateForSingleState)
{
  SyntaxConstraint constraint;
  ParserState state = ParserState::READING_COMMAND;
  constraint.addPrerequisiteState(ParserState::READING_COMMAND);
  CHECK(constraint.getIsValidPrerequisiteState(state));
}

TEST(getIsValidPrerequisiteStateForMultipleStates)
{
  SyntaxConstraint constraint;
  ParserState state = ParserState::READING_COMMAND;
  constraint.addPrerequisiteState(ParserState::READING_PARAMETERS);
  constraint.addPrerequisiteState(ParserState::READING_COMMAND);
  constraint.addPrerequisiteState(ParserState::WAITING_TERMINATION);
  CHECK(constraint.getIsValidPrerequisiteState(state));
}

int main()
{
  return UnitTest::RunAllTests();
}
