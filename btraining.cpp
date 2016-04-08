#include<bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	for(int i=0;i<10;i++)
	{
		map<string,int> vocabularypos,vocabularyneg,vocabulary,bvocabularypos,bvocabularyneg;
		int positive=0,negative=0;
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
			string previous="";
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
					if(previous!="" && previous!="-" && previous!="+")
					{
						string concat=previous+","+s;
						if(flag==-1)
						{
							if(bvocabularyneg.find(concat)!=bvocabularyneg.end())
							{
								map<string,int>::iterator it = bvocabularyneg.find(concat);
								it->second++;
							}
							else
								bvocabularyneg.insert(pair<string,int>(concat,1));
						}
						else if(flag==1)
						{
							if(bvocabularypos.find(concat)!=bvocabularypos.end())
							{
								map<string,int>::iterator it = bvocabularypos.find(concat);
								it->second++;
							}
							else
								bvocabularypos.insert(pair<string,int>(concat,1));
						}
					}
				}
				else if(s=="-")
				{
					flag=-1;
					negative++;
				}
				else if(s=="+")
				{
					flag=1;
					positive++;
				}
				previous=s;
			}
			fold.close();
		}
		//cout<<"positive="<<positive<<" , negative="<<negative<<endl;
		ofstream model;
		char filename[12]={'b','m','o','d','e','l',i+'0','.','t','x','t','\0'};
		model.open(filename);
		int countvocab=0,tcountpos=0,tcountneg=0;
		for(map<string,int>::iterator it=vocabulary.begin(); it!=vocabulary.end(); ++it)
			countvocab++;
		for(map<string,int>::iterator it=vocabularypos.begin(); it!=vocabularypos.end(); ++it)
			tcountpos+=it->second;
		for(map<string,int>::iterator it=vocabularyneg.begin(); it!=vocabularyneg.end(); ++it)
			tcountneg+=it->second;
		double denompos=countvocab+tcountpos,denomneg=countvocab+tcountneg;
		model<<"totalnumofreviews = "<<positive+negative<<endl;
		model<<"p(+) = "<<log10(positive/(double)(positive+negative))<<endl;
		model<<"p(-) = "<<log10(negative/(double)(positive+negative))<<endl;
		model<<"|V| = "<<countvocab<<endl;
		model<<"totalnumofwordsinnegative = "<<tcountpos<<endl;
		model<<"totalnumofwordsinpositive = "<<tcountneg<<endl;
		for(map<string,int>::iterator it=bvocabularypos.begin(); it!=bvocabularypos.end(); ++it)
		{
			double pro=(it->second+1)/denompos;
			if(it->second>=3)
			{
				model<<"p("<<it->first<<"|+) = "<<log10(pro)<<endl;
				istringstream ss(it->first);
				string token;
				while(std::getline(ss, token, ',')) {
					//model << token << '\n';
					if(vocabularypos.find(token)!=vocabularypos.end())
					{
						map<string,int>::iterator it1 = vocabularypos.find(token);
						it1->second-=it->second;
					}
				}
			}
		}
		for(map<string,int>::iterator it=bvocabularyneg.begin(); it!=bvocabularyneg.end(); ++it)
		{
			double pro=(it->second+1)/denomneg;
			if(it->second>=3)
			{
				model<<"p("<<it->first<<"|-) = "<<log10(pro)<<endl;
				istringstream ss(it->first);
				string token;
				while(std::getline(ss, token, ',')) {
					//model << token << '\n';
					if(vocabularyneg.find(token)!=vocabularyneg.end())
					{
						map<string,int>::iterator it1 = vocabularyneg.find(token);
						it1->second-=it->second;
					}
				}
			}
		}
		for(map<string,int>::iterator it=vocabularypos.begin(); it!=vocabularypos.end(); ++it)
		{
			double pro=(it->second+1)/denompos;
			if(it->second>0)
				model<<"p("<<it->first<<"|+) = "<<log10(pro)<<endl;
		}
		for(map<string,int>::iterator it=vocabularyneg.begin(); it!=vocabularyneg.end(); ++it)
		{
			double pro=(it->second+1)/denomneg;
			if(it->second>0)
				model<<"p("<<it->first<<"|-) = "<<log10(pro)<<endl;
		}
		model.close();
	}
	return 0;
}
