#include<bits/stdc++.h>

using namespace std;

int main()
{
	ifstream infile("stopwords.txt");
	map<string,int> stopwordlist;
	string temp;
	int val=1;
	while(infile>>temp)
	{
		stopwordlist.insert(pair<string,int>(temp,val));
		val++;
	}
	string s;
	while(getline(cin,s))
	{
		//Removing any character other than alphabet and replacing upper case alphabets with lower case alphabets
		for(int i=2;i<s.length();i++)
		{
			if(s[i]==' ')
				s[i]=s[i];
			else if(s[i]>='a' && s[i]<='z')
				s[i]=s[i];
			else if(s[i]>='A' && s[i]<='Z')
				s[i]='a'+(s[i]-'A');
			else if(s[i]-' '==7)
			{
				s.erase(s.begin()+i);
				i=i-1;
			}
			else 
				s[i]=' ';
		}

		//Removing Stopwords
		string temp="";
		int start=-1;
		for(int i=2;i<s.length();i++)
		{
			if(s[i-1]==' ' && s[i]!=' ')
			{
				start=i;
				temp.push_back(s[i]);
			}
			else if(s[i]==' ' && temp.length()>0)
			{
				if(stopwordlist.find(temp)!=stopwordlist.end())
				{
					s.erase(s.begin()+start,s.begin()+i+1);
					i=start-1;
				}
				temp.clear();
			}
			else if(s[i]!=' ')
				temp.push_back(s[i]);
		}
		if(temp.length()>0)
		{
			if(stopwordlist.find(temp)!=stopwordlist.end())
				s.erase(s.begin()+start,s.end());
			temp.clear();
		}

		//Removing extra spaces
		start=-1;
		for(int i=2;i<s.length();i++)
		{
			if(s[i]==' ')
			{
				start=i;
				i++;
				while(s[i]==' ')
					i++;
				if(i-start>1)
				{
					s.erase(s.begin()+start+1,s.begin()+i);
					i=start+1;
				}
			}
		}
		cout<<s<<endl;
	}
	return 0;
}
