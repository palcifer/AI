#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

void towers(int, char, char, char);
string printTowerSets(std::set<int> tower);

//map of names and sets of tiles of the pegs
std::map<char, set<int> > peg;
int counter;

int main()
{
    int num;

    cout<<"Enter the number of disks : ";
    cin>>num;

    //range condition
    if (num < 1 || num > 10) {
      cout<<"The number of disc must be an integer number between 2 and 10 (including)"<<endl;
    } else {
        //create initial sequence with three pegs
        set<int> setA;
        for (int i = num; i > 0; --i)
        {
            setA.insert(i);
        }
        peg.insert(pair<char, set<int> >('A', setA));
        set<int> setB;
        peg.insert(pair<char, set<int> >('B', setB));
        set<int> setC;
        peg.insert(pair<char, set<int> >('C', setC));

        cout<<"Initial sequence: " << "A:{"<<printTowerSets(peg['A'])<<"} B:{"<<printTowerSets(peg['B'])<<"} C:{"<<printTowerSets(peg['C'])<<"}"<<endl;
        towers(num, 'A', 'C', 'B');
    }
    return 0;
}

void towers(int num, char frompeg, char topeg, char auxpeg)
{
    //stopping condition for tile #1
    if (num == 1)
    {
        peg[frompeg].erase(1);
        peg[topeg].insert(1);
        counter++;
        cout<<to_string(counter) << ". Move disk 1 from peg "<<frompeg<<" to peg "<<topeg <<". A:{"<<printTowerSets(peg['A'])<<"} B:{"<<printTowerSets(peg['B'])<<"} C:{"<<printTowerSets(peg['C'])<<"}"<<endl;
        return;
    }

    //recursion step
    towers(num - 1, frompeg, auxpeg, topeg);
    peg[frompeg].erase(num);
    peg[topeg].insert(num);
    counter++;
    cout<<to_string(counter) << ". Move disk "<<num<<" from peg "<<frompeg<<" to peg "<<topeg<<". A:{"<<printTowerSets(peg['A'])<<"} B:{"<<printTowerSets(peg['B'])<<"} C:{"<<printTowerSets(peg['C'])<<"}"<<endl;
    towers(num - 1, auxpeg, topeg, frompeg);
}

//return the string of all integers in the set
string printTowerSets(std::set<int> tower){
    string s = "";
    for(int i : tower){
        s += to_string(i);
    }
    return s;
}