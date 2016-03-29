#include<bits/stdc++.h>

using namespace std;

int main()
{
	ofstream myfile;
	string s;
	int countp=0,countn=0;
	for(int i=0;i<10;i++)
	{
		char filename[10]={'f','o','l','d',i+'0','.','t','x','t','\0'};
		myfile.open(filename);
		myfile.close();
	}
	while(getline(cin,s))
	{
		if(s[0]=='+')
		{
			//cout<<countp<<" "<<floor(countp/50)<<endl;
			char val=(countp/50)+'0';
			char filename[10]={'f','o','l','d',val,'.','t','x','t','\0'};
			//cout<<val<<endl;
			myfile.open(filename,ios_base::app);
			myfile<<s<<"\n"<<endl;
			myfile.close();
			countp++;
		}
		if(s[0]=='-')
		{
			//cout<<countn<<" "<<floor(countn/50)<<endl;
			char val=(countn/50)+'0';
			//cout<<val<<endl;
			char filename[10]={'f','o','l','d',val,'.','t','x','t','\0'};
			myfile.open(filename,ios_base::app);
			myfile<<s<<"\n"<<endl;
			myfile.close();
			countn++;
		}
	}
	return 0;
}
