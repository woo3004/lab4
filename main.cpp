#include <iostream>

#include "Parser.h"
#include "Interpreter.h"

// int main(int argc, char* argv[]) {

//   vector<Token> myTokens;
  
//   string fileName = argv[1];
  
//   Token t;

//   Scanner s = Scanner(s.ReadFile(fileName));

//   while(!(t.checkEnd())) {
//     t = s.scanToken();
//     myTokens.push_back(t);

//   }

//   Parser p = Parser(myTokens);

//   p.removeComment();

//   p.datalogProgram();

//   Interpreter i(p.getDataLog());
//   i.evalQueries();

//   return 0;

// }


int main() {

  Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));

  vector<string> studentValues[] = {
    {"'42'", "'Ann'", "'CS'"},
    {"'64'", "'Ned'", "'EE'"},
  };

  for (auto& value : studentValues)
    studentRelation.addTuple(Tuple(value));

  Relation courseRelation("courses", Scheme( {"ID", "Course"} ));

  vector<string> courseValues[] = {
    {"'42'", "'CS 100'"},
    {"'32'", "'CS 232'"},
  };

  for (auto& value : courseValues)
    courseRelation.addTuple(Tuple(value));

  studentRelation.join(courseRelation);
}