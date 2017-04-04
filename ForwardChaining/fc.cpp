// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
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

void parseInput(){
  string line;
  ifstream input ("input.txt");

  parseState state = p_begin;
  int counter = 0;

  if (input.is_open())
  {
    while ( getline (input,line) )
    {
    	
    	bool skip = false;
		if(isdigit(line[0])){
			switch(line[3]){
				case 'R': state = p_rules;
					break;
				case 'F': state = p_facts;
					break;
				case 'G': state = p_end;
					break;
			}
			skip = true;
  		}
  		if(!skip){
  			//cout << counter << ":  " << line.length() << endl;
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
    }

    input.close();
  }

  else cout << "Unable to open file"; 
  
  return;
}

void printInitialSetting(){
	ofstream output;
  	output.open("output.txt");

  	output << "Rules :\n";
  	for (int i = 0; i < rules.size(); ++i)
  	{
  		rulesTmp = rules[i];
  		output << i << ": ";
  		while(!rulesTmp.empty()){
  			if (rulesTmp.size() == 1){
  				output << "-> " << rulesTmp.front() << endl;
	  			rulesTmp.pop_front();
  			} else {
	  			output << rulesTmp.front() << " ";
	  			rulesTmp.pop_front();
  			}
  		}
  	}


   	
  	output << "\nFacts :\n";

  	while(!facts.empty()){
  		output << facts.front() << " ";
  		facts.pop_front();
  	}
  	output << "\n\nEnd symbol :\n" << endsymbol;
  	output.close();
	return;
}

int main () {
  
  parseInput();

  printInitialSetting();

  return 0;
}