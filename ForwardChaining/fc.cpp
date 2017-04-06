// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
using namespace std;

map<int, list<char> > rules;
list<char> rulesTmp;
list<char> facts;
char endsymbol;

enum parseState {
	p_begin, 
	p_rules, 
	p_facts, 
	p_end
};

string path = "";

void parseInput(){
  string line;
  ifstream input ("input.txt");

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
                if(c >= 'A' && c <= 'Z') rulesTmp.push_back(c);
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

  else cout << "Unable to open file"; 
  
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

bool calculateForwardChaining(ofstream& output){
    int counter = 0;
    output << "\nPART 2. Trace\n";

    int flags[rules.size()];
    memset( flags, 0, rules.size()*sizeof(int) );


    while(true){
        if ((std::find(facts.begin(), facts.end(), endsymbol) != facts.end())) {
          output << "     Goal achieved.\n\n";
          break;
        } 
        output << "\n  ITERATION " << counter << endl;
        for (int i = 0; i < rules.size(); ++i)
        {
          output << "     R" << i << ":";
          list<char> rulesInit = rules[i];
          rulesInit.pop_back();
          char rulesEnd = rules[i].back();
          for (int j = 0; j < rulesInit.size(); ++j)
          {
            if(j!=0) output << ", "; 
            char ch = rulesInit.front();
            output << ch;           
            rulesInit.pop_front();
            rulesInit.push_back(ch);
          }
          output << "->" << rulesEnd << " ";
          
          if(flags[i] == 1) {
            output << "skip, because flag1 raised.\n";
            continue;
          }

          if(flags[i] == 2) {
            output << "skip, because flag2 raised.\n";
            continue;
          }

          char c = checkRule(rulesInit);
          if(c =='*'){

            if(checkEnd(rulesEnd)){
              flags[i]=2;
              output << "not applied, because RHS in facts. Raise flag2.\n";
              continue;
            }

            facts.push_back(rulesEnd);
            flags[i]=1;
            path += "R" + to_string(i) + ", ";
            output << "apply. Raise flag1. Facts ";
            for (int j = 0; j < facts.size(); ++j)
            {
              if(j==3) output << " and ";
              else if(j!=0) output << ", "; 

              char ch = facts.front();
              output << ch;           
              facts.pop_front();
              facts.push_back(ch);
            }
            output << "." << endl;
            break;
          } else {
            output << "not applied, because of lacking " << c << ".\n";
          }
          
        }
        counter++;
        if(counter == 7) facts.push_back(endsymbol);
    } 

    return (facts.back() == 'Z') ? true : false;
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


    if (calculateForwardChaining(output)) {
      output << "PART 3. Results\n" << "   1) Goal " << endsymbol << " achieved.\n   2) Path: " << path.substr(0, path.size()-2) << "." << endl;
    } else {
      output << "PART 3. Results\n" << "   1) Goal " << endsymbol << " not achieved." << endl;
    }

  	output.close();
	return;
}

int main () {
  
  parseInput();

  printInitialSetting();

  return 0;
}
