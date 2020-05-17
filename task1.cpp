#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <unordered_set>
using namespace std;

int combinationSize(string s)
{
    int output = 1;
    return (output << s.size() / 2) - 1;
}

void combination(string *arr, string s)
{
    int arrSize = 0;
    int counter = 1;
    while (counter <= combinationSize(s))
    {
        string s1 = "";
        for (int i = 0; i < s.size() / 2; i++)
        {
            if ((counter >> i) & 1)
            {
                s1 += s[2 * i];
                s1 += s[2 * i + 1];
            }
        }
        arr[arrSize++] = s1;
        counter++;
    }
}

string replace(string str, string replacable){
    for(int i = 1; i < replacable.size(); i+=2){
        int index = replacable[i] - '0';
        str[index] = '_';
    }
    
    str.erase(std::remove(str.begin(), str.end(), '_'), str.end());
    return str;
}

int main()
{
    int nLines;
    cin >> nLines;

    unordered_set<string> cfg;
    unordered_set<char> nullable;
    int cfgSize = 0;

    for (int i = 0; i < 2 * nLines; i = i + 2)
    {
        string production = "", tmp;

        cin >> tmp;
        production = production + tmp + " ";
        cin >> tmp;

        if (tmp == "_")
        {
            nullable.insert(production[0]);
            continue;
        }

        production = production + tmp;
        cfg.insert(production);
        cfgSize++;
    }

    for (int i = 0; i < cfgSize; i++){
        for (auto it = cfg.begin(); it != cfg.end(); ++it)
        {
            string rhs = (*it).substr(2);
            int tmpSize = 0;
            for (int j = 0; j < rhs.size(); j++)
            {
                if (nullable.find(rhs[j]) != nullable.end())
                    tmpSize++;
            }

            if (tmpSize == rhs.size())
                nullable.insert((*it)[0]);
        }
    }

    for (auto it = nullable.begin(); it != nullable.end(); ++it)
    {
     //   cout << *it << " ";
    }

    unordered_set<string> extraProductions;
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
        string replacable = "";
        string rhs = (*it).substr(2);
        for (int j = 0; j < rhs.size(); j++)
        {
            if (nullable.find(rhs[j]) != nullable.end())
            {
                replacable = replacable + rhs[j] + to_string(j);
            }
        }
        int size = combinationSize(replacable);
        string replacableCombination[size];
        combination(replacableCombination, replacable);
        for(int k = 0; k < size; k++){
            string newProduction = replace(rhs, replacableCombination[k]);
            string lhs;
            lhs = (*it)[0];
            lhs = lhs + " " + newProduction;
            if(newProduction == "" || newProduction.size() == 0){
                continue;
            }
            extraProductions.insert(lhs);
            cfgSize++;
        }
    }

    for (auto it = extraProductions.begin(); it != extraProductions.end(); ++it)
    {
      cfg.insert((*it));
    }

    cout<< cfgSize<<endl;
    for (auto it = cfg.begin(); it != cfg.end(); ++it)
    {
      cout<< *it <<endl;
    }

}
