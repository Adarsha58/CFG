#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
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

void insert(char lhs, char rhs, unordered_map<char, vector<char>> & cfg){
    unordered_map<char,vector<char>>::const_iterator got = cfg.find(lhs);
    
    if(got == cfg.end()){
        vector<char> s;
        s.push_back(rhs);
        cfg.insert({lhs, s});
    }else{
        vector<char> v = got->second;
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
    unordered_map<char, vector<char>> unitProduction;


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
                insert(lhs, rhs[0], unitProduction);
                continue;
        }
        
        insert(lhs, rhs, cfg);
    }

    unordered_map<char, vector<string>> newProductions = cfg;

    for (auto it = unitProduction.begin(); it != unitProduction.end(); ++it)
    {
       char lhs = it->first;
       list<char> tmp;
       tmp.push_front(lhs);
       unordered_set<char> visited;
       visited.insert(lhs);

        while(!tmp.empty()){
            lhs = tmp.front();
            tmp.remove(lhs);
            unordered_map<char,vector<char>>::const_iterator got = unitProduction.find(lhs);
            if(got != unitProduction.end()){
                vector<char> v = got->second;
                for(auto it1 = v.begin(); it1 != v.end(); it1++){
                    if(visited.find(*it1) == visited.end()){
                        visited.insert(*it1);
                        tmp.push_front((*it1));
                    }
                }
            }else{
                tmp.remove(lhs);
            }
        }

        for(auto it2 = visited.begin(); it2 != visited.end(); it2++){
            unordered_map<char,vector<string>>::const_iterator insertion = cfg.find(*it2);
            if(insertion != cfg.end()){
                vector<string> v1 = insertion->second;
                for(auto it3 = v1.begin(); it3 != v1.end(); ++it3){
                    insert(it->first, *it3, newProductions);
                }
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
            cout<< it->first << " "<< *it1<< endl;
        }
    }
    
    return 0;
}


/*
unordered_map<char,vector<string>>::const_iterator got = cfg.find(reach);
            if(got != cfg.end()){
                vector<string> v = got->second;
                for(auto it1 = v.begin(); it1 != v.end(); ++it1){
                    insert(it->first, *it1, newProductions);
                }
            }
        */