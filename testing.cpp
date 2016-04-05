#include<bits/stdc++.h>

using namespace std;

int main()
{
	string s,eq;
	double val,treviews=0.0;
	int correct=0;
	for(int i=0;i<10;i++)
	{
		map<string,double> probpos,probneg;
		int countvocab,tcountpos,tcountneg;
		double positive,negative;
		ifstream model;
		char filename[11]={'m','o','d','e','l',i+'0','.','t','x','t','\0'};
		model.open(filename);
		while(model>>s>>eq>>val)
		{
			if(s=="p(+)")
				positive=val;
			else if(s=="p(-)")
				negative=val;
			else if(s=="|V|")
				countvocab=(int)val;
			else if(s=="totalnumofreviews")
				treviews=val;
			else if(s=="totalnumofwordsinnegative")
				tcountneg=(int)val;
			else if(s=="totalnumofwordsinpositive")
				tcountpos=(int)val;
			else if(s[s.length()-2]=='+')
				probpos.insert(pair<string,double>(s,val));
			else if(s[s.length()-2]=='-')
				probneg.insert(pair<string,double>(s,val));
		}
		model.close();
		double denompos=countvocab+tcountpos,denomneg=countvocab+tcountneg;
		char filename1[10]={'f','o','l','d',i+'0','.','t','x','t','\0'};
		ifstream fold;
		fold.open(filename1);
		int flag=0;
		double posprob=0,negprob=0;
		while(fold>>s)
		{
			if(s!="-" && s!="+")
			{
				s="p("+s+"|+)";
				if(probpos.find(s)!=probpos.end())
				{
					map<string,double>::iterator it = probpos.find(s);
					posprob+=it->second;
				}
				else
					posprob+=log10(1/denompos);
				s[s.length()-2]='-';
				if(probneg.find(s)!=probneg.end())
				{
					map<string,double>::iterator it = probneg.find(s);
					negprob+=it->second;
				}
				else
					negprob+=log10(1/denomneg);
			}
			else if(s=="-")
			{
				int ans=0;
				posprob+=positive;
				negprob+=negative;
				ans=(posprob<negprob)?(-1):(1);
				if(flag!=0 && ans==flag)
					correct++;
				flag=-1;
				posprob=0;
				negprob=0;
			}
			else if(s=="+")
			{
				int ans=0;
				posprob+=positive;
				negprob+=negative;
				ans=(posprob<negprob)?(-1):(1);
				if(flag!=0 && ans==flag)
					correct++;
				flag=1;
				posprob=0;
				negprob=0;
			}
		}
		int ans=0;
		posprob+=positive;
		negprob+=negative;
		ans=(posprob<negprob)?(-1):(1);
		if(flag!=0 && ans==flag)
			correct++;
		fold.close();
		remove(filename1);
	}
	ofstream myfile;
	myfile.open("README.md",ios_base::app);
	myfile<<"\nAccuracy of Multinomial Naive Bayes Model = "<<(correct)/(double)(((treviews*10)/9)/100)<<"%"<<endl;
	myfile.close();
	cout<<"\nAccuracy of Multinomial Naive Bayes Model = "<<(correct)/(double)(((treviews*10)/9)/100)<<"%"<<endl;
    return 0;
}
