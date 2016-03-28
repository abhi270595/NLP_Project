#include<bits/stdc++.h>

using namespace std;

int main()
{
    string s;
	for(int i=0;i<10;i++)
	{
		map<string,int> vocabularypos,vocabularyneg,vocabulary;
		for(int val=0;val<10;val++)
		{
			if(val==i)
				val++;
			if(val>=10)
				break;
			char filename[10]={'f','o','l','d',val+'0','.','t','x','t','\0'};
			ifstream fold;
			fold.open(filename);
			int flag=0;
    		while(fold>>s)
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
					if(flag==-1)
					{
            			if(vocabularyneg.find(s)!=vocabularyneg.end())
            			{
                			map<string,int>::iterator it = vocabularyneg.find(s);
                			it->second++;
            			}
            			else
                			vocabularyneg.insert(pair<string,int>(s,1));
					}
					else if(flag==1)
					{
            			if(vocabularypos.find(s)!=vocabularypos.end())
            			{
                			map<string,int>::iterator it = vocabularypos.find(s);
                			it->second++;
            			}
            			else
                			vocabularypos.insert(pair<string,int>(s,1));
					}
        		}
				else if(s=="-")
					flag=-1;
				else if(s=="+")
					flag=1;
    		}
			fold.close();
		}
		ofstream model;
		char filename[11]={'m','o','d','e','l',i+'0','.','t','x','t','\0'};
		model.open(filename);
		int countvocab=0,tcountpos=0,tcountneg=0;
		for(map<string,int>::iterator it=vocabulary.begin(); it!=vocabulary.end(); ++it)
        	countvocab++;
		for(map<string,int>::iterator it=vocabularypos.begin(); it!=vocabularypos.end(); ++it)
        	tcountpos+=it->second;
		for(map<string,int>::iterator it=vocabularyneg.begin(); it!=vocabularyneg.end(); ++it)
        	tcountneg+=it->second;
		double denompos=countvocab+tcountpos,denomneg=countvocab+tcountneg;
		model<<"p(+) = "<<log10(0.5)<<endl;
		model<<"p(-) = "<<log10(0.5)<<endl;
		model<<"|V| = "<<countvocab<<endl;
		model<<"totalnumofwordsinnegative = "<<tcountpos<<endl;
		model<<"totalnumofwordsinpositive = "<<tcountneg<<endl;
		for(map<string,int>::iterator it=vocabularypos.begin(); it!=vocabularypos.end(); ++it)
        {
			double pro=(it->second+1)/denompos;
			model<<"p("<<it->first<<"|+) = "<<log10(pro)<<endl;
		}
		for(map<string,int>::iterator it=vocabularyneg.begin(); it!=vocabularyneg.end(); ++it)
        {
			double pro=(it->second+1)/denomneg;
			model<<"p("<<it->first<<"|-) = "<<log10(pro)<<endl;
		}
		model.close();
	}
    return 0;
}
