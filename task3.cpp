#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <ctype.h>
using namespace std;


int sizeOfRhs(string rhs){
    int size = 0;
    for (int j = 0; j < rhs.size(); j++)
    {
        if(rhs[j] - 'A' < 26 && rhs[j] - 'A' >= 0){
            size++;
        }
    }
    return size;
}

string createNewName(string nTerminus)
{
    char letter = nTerminus[0];
    string digit1 = nTerminus.substr(1);
    int digit = stoi(digit1);
    if(digit < 9) digit++;
    
    if(digit >= 9 && letter == 'Z'){
        digit++;    
        
    }
    
    if (digit == 9){
        digit = 0;
        letter++;
    }
    string output = "";
    output += letter;
    output += to_string(digit);
    return output;
}
string reduceRhs(string rhs, unordered_set<string> & s, string & terminus)
{
    string copy = rhs;
    while(sizeOfRhs(copy) >2){
        string first = "";
        for (int j = 0; j < rhs.size(); j++)
        {
            first += rhs[j];
            if((j+1)< rhs.size() && isdigit(rhs[j+1])){
                first += rhs[j+1];
                j++;
            }

            if(sizeOfRhs(first) == 2){
                string tmp = terminus + " ";
                copy.replace(copy.find(first), first.size(), terminus);
                tmp += first;
                s.insert(tmp);
                terminus = createNewName(terminus);
                first = "";
            }
        }
        rhs = copy;
    }
    return copy; 
}

int main()
{
    int nLines;
    cin >> nLines;
    string newNTerminus = "A1";

    unordered_set<string> cfg;
    int cfgSize = 0;

    for (int i = 0; i < 2 * nLines; i = i + 2)
    {
        string production = "", tmp;

        cin >> tmp;
        production = production + tmp + " ";
        cin >> tmp;
        if(tmp.size() > 1){
            tmp.erase(std::remove(tmp.begin(), tmp.end(), '_'), tmp.end());
        }
        production = production + tmp;
        cfg.insert(production);
    }

    unordered_set<string> extraProductions = cfg;
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
        string rhs = (*it).substr(2);
        string newProduction, terminus;
        newProduction = (*it)[0];
        newProduction += " ";
        if(rhs.size() > 1){
            for (int j = 0; j < rhs.size(); j++)
            {
                if(rhs[j] - 'a' < 26 && rhs[j] - 'a' >= 0)
                {
                    newProduction += newNTerminus;
                    terminus = newNTerminus + " ";
                    terminus += rhs[j]; 
                    extraProductions.insert(terminus);
                    newNTerminus = createNewName(newNTerminus);
                }else{
                    newProduction += rhs[j];
                }
            }
            extraProductions.erase(*it);
            extraProductions.insert(newProduction);
        }
    }

    cfg = extraProductions;

    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
        string rhs = (*it).substr(2);
        if(sizeOfRhs(rhs) > 2){
            string lhs;
            lhs = (*it)[0];
            lhs += " ";
            extraProductions.erase(*it);
            string newRhs = reduceRhs(rhs, extraProductions, newNTerminus);
            lhs += newRhs;
            extraProductions.insert(lhs);
        }
    }
    cfg = extraProductions;
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
      cfgSize++;
    }

    cout<< cfgSize<<endl;
    string cfgS = "";
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
      cfgS = cfgS + *it + "\n";
    }
    cfgS = cfgS.substr(0, cfgS.size()-1);
    cout<< cfgS;

    return 0;
}
