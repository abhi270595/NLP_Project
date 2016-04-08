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
		char filename[12]={'b','m','o','d','e','l',i+'0','.','t','x','t','\0'};
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
		string prev="",prevprev="";
		int pus=-1,pup=-1,pupp=-1,nus=-1,nup=-1,nupp=-1;
		while(fold>>s)
		{
			pus=nus=-1;
			if(s!="-" && s!="+")
			{
				if(prev!="-" && prev!="-" && prev!="")
				{
					string concat="p("+prev+","+s+"|+)";
					if(probpos.find(concat)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(concat);
						posprob+=it->second;
						//cout<<"string="<<concat<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
						pus=pup=0;
					}
					else
					{
						pus=(pus==0)?(0):(1);
						pup=(pup==0)?(0):(1);
					}
					concat[concat.length()-2]='-';
					if(probneg.find(concat)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(concat);
						negprob+=it->second;
						//cout<<"string="<<concat<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
						nus=nup=0;
					}
					else
					{
						nus=(nus==0)?(0):(1);
						nup=(nup==0)?(0):(1);
					}
				}
				if(pupp==1 && prevprev!="-" && prevprev!="+")
				{
					string s1="p("+prevprev+"|+)";
					if(probpos.find(s1)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(s1);
						posprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
					}
					else
						posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
				}
				if(nupp==1 && prevprev!="-" && prevprev!="+")
				{
					string s1="p("+prevprev+"|-)";
					if(probneg.find(s1)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(s1);
						negprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
					}
					else
						negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
				}
			}
			else if(s=="-")
			{
				if(pupp==1)
				{
					string s1="p("+prevprev+"|+)";
					if(probpos.find(s1)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(s1);
						posprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
					}
					else
						posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
				}
				if(nupp==1)
				{
					string s1="p("+prevprev+"|-)";
					if(probneg.find(s1)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(s1);
						negprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
					}
					else
						negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
				}
				if(pup==1)
				{
					string s1="p("+prev+"|+)";
					if(probpos.find(s1)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(s1);
						posprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
					}
					else
						posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
				}
				if(nup==1)
				{
					string s1="p("+prev+"|-)";
					if(probneg.find(s1)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(s1);
						negprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
					}
					else
						negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
				}
				nus=pus=nup=pup=nupp=pupp=-1;
				int ans=0;
				posprob+=positive;
				negprob+=negative;
				ans=(posprob<negprob)?(-1):(1);
				if(flag!=0 && ans==flag)
					correct++;
				//cout<<"bigram correct="<<correct<<" , flag="<<flag<<" , pos="<<posprob<<" , neg="<<negprob<<endl;
				flag=-1;
				posprob=0;
				negprob=0;
			}
			else if(s=="+")
			{
				if(pupp==1)
				{
					string s1="p("+prevprev+"|+)";
					if(probpos.find(s1)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(s1);
						posprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
					}
					else
						posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
				}
				if(nupp==1)
				{
					string s1="p("+prevprev+"|-)";
					if(probneg.find(s1)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(s1);
						negprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
					}
					else
						negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
				}
				if(pup==1)
				{
					string s1="p("+prev+"|+)";
					if(probpos.find(s1)!=probpos.end())
					{
						map<string,double>::iterator it = probpos.find(s1);
						posprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
					}
					else
						posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
				}
				if(nup==1)
				{
					string s1="p("+prev+"|-)";
					if(probneg.find(s1)!=probneg.end())
					{
						map<string,double>::iterator it = probneg.find(s1);
						negprob+=it->second;
						//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
					}
					else
						negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
				}
				nus=pus=nup=pup=nupp=pupp=-1;
				int ans=0;
				posprob+=positive;
				negprob+=negative;
				ans=(posprob<negprob)?(-1):(1);
				if(flag!=0 && ans==flag)
					correct++;
				//cout<<"bigram correct="<<correct<<" , flag="<<flag<<" , pos="<<posprob<<" , neg="<<negprob<<endl;
				flag=1;
				posprob=0;
				negprob=0;
			}
			prevprev=prev;
			prev=s;
			pupp=pup;
			pup=pus;
			nupp=nup;
			nup=nus;
		}
		if(pupp==1)
		{
			string s1="p("+prevprev+"|+)";
			if(probpos.find(s1)!=probpos.end())
			{
				map<string,double>::iterator it = probpos.find(s1);
				posprob+=it->second;
				//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
			}
			else
				posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
		}
		if(nupp==1)
		{
			string s1="p("+prevprev+"|-)";
			if(probneg.find(s1)!=probneg.end())
			{
				map<string,double>::iterator it = probneg.find(s1);
				negprob+=it->second;
				//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
			}
			else
				negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
		}
		if(pup==1)
		{
			string s1="p("+prev+"|+)";
			if(probpos.find(s1)!=probpos.end())
			{
				map<string,double>::iterator it = probpos.find(s1);
				posprob+=it->second;
				//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<posprob<<endl;
			}
			else
				posprob+=log10(1/denompos);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denompos)<<" ---> totalpro="<<posprob<<endl;
		}
		if(nup==1)
		{
			string s1="p("+prev+"|-)";
			if(probneg.find(s1)!=probneg.end())
			{
				map<string,double>::iterator it = probneg.find(s1);
				negprob+=it->second;
				//cout<<"string="<<s1<<" ---> probab="<<it->second<<" ---> totalpro="<<negprob<<endl;
			}
			else
				negprob+=log10(1/denomneg);
////cout<<"string="<<s1<<" ---> probab="<<log10(1/denomneg)<<" ---> totalpro="<<negprob<<endl;
		}
		nus=pus=nup=pup=nupp=pupp=-1;
		int ans=0;
		posprob+=positive;
		negprob+=negative;
		ans=(posprob<negprob)?(-1):(1);
		if(flag!=0 && ans==flag)
			correct++;
		//cout<<"bigram correct="<<correct<<" , flag="<<flag<<" , pos="<<posprob<<" , neg="<<negprob<<endl;
		fold.close();
		remove(filename1);
	}
	ofstream myfile;
	myfile.open("README.md",ios_base::app);
	myfile<<"\nBigram accuracy of Multinomial Naive Bayes Model = "<<(correct)/(double)(((treviews*10)/9)/100)<<"%"<<endl;
	myfile.close();
	cout<<"\nBigram accuracy of Multinomial Naive Bayes Model = "<<(correct)/(double)(((treviews*10)/9)/100)<<"%"<<endl;
    return 0;
}
