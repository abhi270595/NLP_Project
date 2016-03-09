#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    map<string,int> vocabulary;
    while(cin>>s)
    {
        if(s!="-" && s!="+")
        {
            if(vocabulary.find(s)!=vocabulary.end())
            {
                map<string,int>::iterator it = vocabulary.find(s);
                it->second++;
            }
            else
                vocabulary.insert(pair<string,int>(s,1));
        }
    }
    for(map<string,int>::iterator it=vocabulary.begin(); it!=vocabulary.end(); ++it)
        if(it->second>1)
            cout << it->first << " " << it->second << endl;
    return 0;
}
