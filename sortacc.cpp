#include<bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	int countp=0,countn=0;
	while(getline(cin,s))
	{
		if(countp<500)
		{
			if(s[0]=='+' && s.length()<=302)
			{
				cout<<s<<"\n"<<endl;
				countp++;
			}
		}
		if(countn<500)
		{
			if(s[0]=='-' && s.length()<=302)
			{
				cout<<s<<"\n"<<endl;
				countn++;
			}
		}
		if(countp>=500 && countn>=500)
			break;
	}
	//cout<<"positive="<<countp<<" , negative="<<countn<<endl;
	return 0;
}
