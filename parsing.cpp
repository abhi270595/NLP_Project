#include<bits/stdc++.h>

using namespace std;

int main()
{
	string s,saves;
	while(getline(cin,s))
	{
		size_t find = s.find("[fullText]");
		if(find != string::npos)
			saves=s;
		else
		{
			size_t find1 = s.find("[rating]");
			if(find1 != string::npos)
			{
				float val=(s[9]-'0')+(0.1*(float)(s[11]-'0'));
				if(val<2.5)
					cout<<"- "<<saves.substr(11)<<"\n"<<endl;
				else
					cout<<"+ "<<saves.substr(11)<<"\n"<<endl;
			}
		}
	}
	return 0;
}