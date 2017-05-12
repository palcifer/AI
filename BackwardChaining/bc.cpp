// reading a text file
#include <iostream>
#include <fstream>
#include <iomanip>  
#include <string>
#include <list>
#include <map>
#include <stack>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
using namespace std;

map<int, list<char> > rules;
list<char> rulesTmp;
list<char> facts;
char endsymbol;

stack<list<char> > rulerule;
char currentGoal;
list<char> processed;
list<char> originalFacts;

int counter;
int dotCounter;
int usedRules;

int pos[64] = {};

enum parseState {
  p_begin, 
  p_rules, 
  p_facts, 
  p_end
};

string path = "";

void parseInput(){
  string line;
  ifstream input ("input4.txt");

  parseState state = p_begin;
  int counter = 0;

  if (input.is_open())
  {
    while ( getline (input,line) )
    {
    if(isdigit(line[0])){
      switch(line[3]){
        case 'R': state = p_rules;
          break;
        case 'F': state = p_facts;
          break;
        case 'G': state = p_end;
          break;
      }
            continue;
      }
        if (state == p_rules) {
            for (int i = 0; i < line.length(); ++i)
            {
                char c = line.at(i);
                if(c == '/') break;
                if(c >= 'A' && c <= 'Z') rulesTmp.push_front(c);
                //cout << c << endl;
            }
            if(!rulesTmp.empty()){
                rules.insert(std::pair<int, list<char> >(counter, rulesTmp));
                counter++;
                rulesTmp.clear();
            }

        } else if (state == p_facts) {
            
            for (int i = 0; i < line.length(); ++i)
            {
                char c = line.at(i);
                if(c >= 'A' && c <= 'Z') facts.push_back(c);
            }

        } else if (state == p_end) {
            endsymbol = line.at(0);
            //cout << endsymbol << endl;
        }
    }

    input.close();
  }

  else cout << "Unable to open file\n"; 
  
  return;
}

char checkRule(list<char> rulesInit) {

  for (int i = 0; i < rulesInit.size(); ++i)
  {
    char c = rulesInit.front();
    rulesInit.pop_front();
    rulesInit.push_back(c);
    //check out, if c is in facts. If not, return c.
    bool tmp = false;
    for (int i = 0; i < facts.size(); ++i)
    {
      char ch = facts.front();
      facts.pop_front();
      facts.push_back(ch);
      if (c == ch) tmp = true;
    }
    if (!tmp) return c;
  }

  return '*';
}

bool checkEnd(char c){
  bool tmp = false;
  for (int i = 0; i < facts.size(); ++i)
    {
      char ch = facts.front();
      facts.pop_front();
      facts.push_back(ch);
      if (c == ch) tmp = true;
    }
  return tmp;
}

string returnDots(){
  string s = "";
  for (int i = 1; i < rulerule.size(); ++i)
  {
    s += '.';
  }
  return s;
}

bool contain(list<char> list, char c){
	bool containes = false;
	for (std::list<char>::const_iterator iterator = list.begin(), end = list.end(); iterator != end; ++iterator) {
      if (*iterator == c) containes = true;
    }
    return containes;
}

bool isSubset(list<char> list1, list<char> list2){
	bool notSub = true;
	for (std::list<char>::const_iterator iterator1 = list1.begin(), end1 = list1.end(); iterator1 != end1; ++iterator1) {
      	for (std::list<char>::const_iterator iterator2 = list2.begin(), end2 = list2.end(); iterator2 != end2; ++iterator2) {
      		if (*iterator1 == *iterator2){
      			notSub = false;
      			break;
      		}
    	}
    	if(notSub) return false;
    	else notSub = true;
    }
	return true;
}

string printRule(int i) {
	string s = "";
	stringstream ss, sr, st;
	list<char> rulesTmpr = rules[i];
	while(!rulesTmpr.empty()){
        if (rulesTmpr.size() == 1){
          st << "->" << rulesTmpr.front();
          rulesTmpr.pop_front();
        } else if (rulesTmpr.size() == 2){
          sr << rulesTmpr.front();
          rulesTmpr.pop_front();
        } else {
          ss << rulesTmpr.front() << ",";
          rulesTmpr.pop_front();
        }
      }

    s = ss.str() + sr.str() + st.str();
    return s;
}

void printFact(ofstream& output, char currentGoal){
	output << std::setfill(' ') << std::setw(3) << counter << ") " << returnDots() << "Goal " << currentGoal << ". Fact";
	if(contain(originalFacts, currentGoal)) output << " (initial)";
	else if(contain(facts, currentGoal)) output << " (presentaly obtained)";
	output<< ", as facts are ";
	for (std::list<char>::const_iterator iterator = facts.begin(), end = facts.end(); iterator != end; ++iterator) {
          output << *iterator << " ";
        }
	if (contain(originalFacts, currentGoal)) output << ". Back, OK." << endl;
	else if (contain(facts, endsymbol)) output << ". OK." << endl;
	else output << "." << endl;
}

void printFind(ofstream& output, list<char> list, int i) {
	list.pop_back();
	output << std::setfill(' ') << std::setw(3) << counter << ") " << returnDots() << "Goal " << currentGoal << ". Find R" << i << ":" << printRule(i) << ". New goals ";
	for (std::list<char>::const_iterator iterator = list.begin(), end = list.end(); iterator != end; ++iterator) {
      output << *iterator << ", ";
    }
    output << endl;
}

void deadEnd(){
	//facts.push_back(rulerule.top().front());
	rulerule.top().pop_front();
	if(rulerule.top().empty()){
		rulerule.pop();
		facts.push_back(rulerule.top().front());

	}
	//processed.pop_back();
	//path = path.substr(0, path.size()-2);
}

bool bc(ofstream& output){


		
	//we came to the end symbol
	currentGoal = rulerule.top().front();
	if(currentGoal == endsymbol) {
		facts.push_back(currentGoal);
		deadEnd();
		return true;
	}

		//current goal in facts
	if(contain(facts, currentGoal)){

		counter++;
		printFact(output, currentGoal);
		deadEnd();
		return bc(output);
	}

	//loop
	if(contain(processed, currentGoal)) {
		counter++;
		output << setfill(' ')  << setw(3) << counter << ") " << returnDots() << "Goal " << currentGoal << ". Loop. Back, FAIL." << endl;
		deadEnd(); 
		facts.pop_back();
		processed.remove(currentGoal);
		return false;
	}

	//find rule to match
	int i = 0;
	while (i < rules.size())
	{
		currentGoal = rulerule.top().front();
		
		if(pos[rulerule.size()] == 0) pos[rulerule.size()] = int(currentGoal);
		if(int(currentGoal) != pos[rulerule.size()]) {
			i = 0;
			pos[rulerule.size()] = int(currentGoal);
		}

	    rulesTmp = rules[i];
	    if(rulesTmp.back() == currentGoal) {
	    	counter++;
	    	path += "R" + to_string(i) + ", ";
	    	processed.push_back(currentGoal);
			printFind(output, rulesTmp, i);
	  		rulesTmp.pop_back();
	  		rulerule.push(rulesTmp);	  		
	  		if(bc(output)) return true;
		}
		++i;
	}

	//no matching rule, delete stack to the root
	counter++;
	output << setfill(' ')  << setw(3) << counter << ") " << returnDots() << "Goal " << currentGoal << ". No rules. Back, FAIL." << endl;
	rulerule.top().pop_front();
	if(rulerule.top().empty()){
		rulerule.pop();
		facts.push_back(rulerule.top().front());
	}
	//processed.remove(currentGoal);
	path = path.substr(0, path.size()-4);
	facts.remove(currentGoal); 
	return false;
}

bool calculateBackwardChaining(ofstream& output){

	output << "\nPART 2. Trace\n\n";

	counter = 0;
    usedRules = 0;

	list<char> goals;
    goals.push_back(endsymbol);

    rulerule.push(goals);

    originalFacts = facts;

    for (int i = 0; i < rules.size(); ++i)
	{
		stack<list<char> >().swap(rulerule);
	  	rulerule.push(goals);		
	  	currentGoal = rulerule.top().front();

	  	facts = originalFacts;
	  	path = "";
	  	processed.clear();

	    rulesTmp = rules[i];
	    if(rulesTmp.back() == currentGoal) {
	    	counter++;
	    	path += "R" + to_string(i) + ", ";
			printFind(output, rulesTmp, i);
	  		rulerule.push(rulesTmp); 	
	  		if(bc(output)) {
	  			counter++;
	  			printFact(output, endsymbol);
	  			return true;
	  		}	  			
		}
	}

	return false; 
}

void printInitialSetting(){
  ofstream output;
    output.open("output.txt");

    output << "PART 1. Data\n\n";

    output << "  1) Rules :\n";
    for (int i = 0; i < rules.size(); ++i)
    {
      rulesTmp = rules[i];
      output << "     R" << i << ": ";
      while(!rulesTmp.empty()){
        if (rulesTmp.size() == 1){
          output << "-> " << rulesTmp.front() << endl;
          rulesTmp.pop_front();
        } else if (rulesTmp.size() == 2){
          output << rulesTmp.front() << " ";
          rulesTmp.pop_front();
        } else {
          output << rulesTmp.front() << ", ";
          rulesTmp.pop_front();
        }
      }
    }


    
    output << "\n  2) Facts\n     ";

    for(int i = 0; i < facts.size(); i++){
      char ch = facts.front();
      if (i != facts.size()-1) output << ch << ", ";
      else output << ch;
      facts.pop_front();
      facts.push_back(ch);
    }
    output << "\n\n  3) Goal \n     " << endsymbol << endl;

    for (std::list<char>::const_iterator iterator = facts.begin(), end = facts.end(); iterator != end; ++iterator) {
      if (*iterator == endsymbol){
        output << "\nPART 3. Results\n" << "   1) Goal " << endsymbol << " in facts. Empty path.\n";
        output.close();
        return;
      }
    }


    if (calculateBackwardChaining(output)) {
      output << "\nPART 3. Results\n" << "   1) Goal " << endsymbol << " achieved.\n   2) Path: " << path.substr(0, path.size()-2) << "." << endl;
    } else {
      output << "\nPART 3. Results\n" << "   1) Goal " << endsymbol << " not achieved." << endl;
    }

    output.close();
  return;
}

int main () {
  
  parseInput();

  printInitialSetting();

  return 0;
}
