#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;


void insert(char lhs, string rhs, unordered_map<char, vector<string>> & cfg){
    unordered_map<char,vector<string>>::const_iterator got = cfg.find(lhs);
    
    if(got == cfg.end()){
        vector<string> s;
        s.push_back(rhs);
        cfg.insert({lhs, s});
    }else{
        vector<string> v = got->second;
        v.push_back(rhs);
        cfg.erase(lhs);
        cfg.insert({lhs, v});
    }
}


int main()
{
    int nLines;
    cin >> nLines;
    int cfgSize = 0;

    unordered_map<char, vector<string>> cfg;
    unordered_map<char, char> unitProduction;


    for (int i = 0; i < 2 * nLines; i = i + 2)
    {
        char lhs;
        string rhs;

        cin >> lhs;
        cin >> rhs;
        if(rhs.size() > 1){
            rhs.erase(std::remove(rhs.begin(), rhs.end(), '_'), rhs.end());
        }
        
        //checking if this is the unitProduciton
        if(rhs.size() == 1 && (rhs[0] - 'A' >= 0) && (rhs[0] - 'A' < 26)) {
                unitProduction.insert({lhs, rhs[0]});
                continue;
        }
        
        insert(lhs, rhs, cfg);
    }

    unordered_map<char, vector<string>> newProductions = cfg;

    for (auto it = unitProduction.begin(); it != unitProduction.end(); ++it)
    {
        unordered_set<char> s;
        s.insert(it->first);
        char reach = it->second;

        while(s.find(reach) == s.end()){
            s.insert(reach);
            unordered_map<char,vector<string>>::const_iterator got = cfg.find(reach);
            if(got != cfg.end()){
                vector<string> v = got->second;
                for(auto it1 = v.begin(); it1 != v.end(); ++it1){
                    insert(it->first, *it1, newProductions);
                }
            }

            if(unitProduction.find(reach) != unitProduction.end()){
                unordered_map<char, char>::const_iterator r1 = unitProduction.find(reach);
                reach = r1->second;
            }
        }

    }

    cfg = newProductions;

    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
        for(auto it1 = (it->second).begin(); it1 != (it->second).end(); ++it1){
            cfgSize++;
        } 
    }
    cout<< cfgSize<<endl;
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
        for(auto it1 = (it->second).begin(); it1 != (it->second).end(); ++it1){
            cout<< it->first << " " << *it1 << endl;
        } 
    }
    return 0;
}
