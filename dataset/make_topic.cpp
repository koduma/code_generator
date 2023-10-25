#include <vector>
#include <cfloat>
#include <cstdio>
#include <cstring>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <random>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>    

using namespace std;

#define TURN 2000
#define CODE_LENGTH 2000   

unordered_map<string,int>word;
unordered_map<int,string>unword;
unordered_map<int,int>prob;
multimap<int,int>words;
unordered_map<string,bool>history;

string output;

double d_rnd() {
	static mt19937 mt((int)time(0));
	uniform_real_distribution<double> dice(0.0, 1.0);
	return dice(mt);
}
int rnd(int mini, int maxi) {
	static mt19937 mt((int)time(0));
	uniform_int_distribution<int> dice(mini, maxi);
	return dice(mt);
}

struct node{
int cur;
unordered_map<int, int>v;
string str;
int ev;
int length;    
};

string ans;

int LP[CODE_LENGTH+5][CODE_LENGTH+5];

int distance(string x,string y){
  
  int j,k;
    
  memset(LP,0,sizeof(LP));  
    
  for(j=1;j<=(int)x.size();j++) LP[j][0] = j;
  for(k=1;k<=(int)y.size();k++) LP[0][k] = k;

  for(j=1;j<=(int)x.size();j++) {
    for(k=1;k<=(int)y.size();k++) {
      int m = min(LP[j-1][k]+1, LP[j][k-1]+1);
      if(x[j-1] == y[k-1]) {
        m = min(m,LP[j-1][k-1]);
        LP[j][k] = m;
      }else {
        m = min(m,LP[j-1][k-1]+1);
        LP[j][k] = m;
      }
    }
  }
  return LP[(int)x.size()][(int)y.size()];

}
node BEAM_SEARCH(node n) {
	vector<node>dque;
	dque.push_back(n);

	node bestAction=n;
	
	int maxvalue=-1000000;

	//2手目以降をビームサーチで探索
	for (int i = 0; i < TURN; i++) {
		int ks = (int)dque.size();
		vector<node>vn;
		for (int k = 0; k < ks; k++) {
			node temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=5){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
				node cand = temp;
				string s=unword[it->second];
				if(unword[it->second]==""){unword[it->second]=" ";}
				if(it->second==0){cand.ev=0;}
				cand.cur=it->second;
				cand.str=cand.str+unword[it->second];
				cand.ev=cand.ev+prob[it->second];
				vn.push_back(cand);
			}
		}
		//printf("depth=%d/%d\n",i+1,MAX_TRN);
		dque.clear();
		vector<pair<int,int> >vec;
		bool congrats=false;
		for (int j = 0; j < (int)vn.size(); j++) {
		vec.push_back(make_pair(-vn[j].ev,j));
		}
		sort(vec.begin(),vec.end());
		int push_node=0;
		for (int j = 0; push_node < 100 ;j++) {
			if(j>=(int)vec.size()){break;}
			int x=vec[j].second;
			node temp = vn[x];
			if(temp.ev>maxvalue){
			maxvalue=temp.ev;
			bestAction=temp;   
			}
			if (i < TURN) {
				dque.push_back(temp);
				push_node++;
			}
		}
	}
	return bestAction;
}

node BEAM_SEARCH2(node n) {
	
	vector<node>dque;
	dque.push_back(n);

	node bestAction=n;
	
	int maxvalue=-1000000;

	//2手目以降をビームサーチで探索
	for (int i = 0;i<TURN; i++) {
		int ks = (int)dque.size();
		vector<node>vn;
		for (int k = 0; k < ks; k++) {
			node temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=100){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
			node cand = temp;
			string s=unword[it->second];    
			if(s==""||s==" "||(it->second==0)){cand.ev=0;}
			cand.cur=it->second;   
			cand.str=cand.str+unword[it->second];    
			node n2=BEAM_SEARCH(cand);
			int a=(int)cand.str.size()-(int)unword[it->second].size();
			int b=(int)unword[it->second].size();
			if(a<0){a=0;}
			if(a>(int)ans.size()){a=(int)ans.size();}
			if(a+b>(int)ans.size()){b=(int)ans.size()-a;}
			if(b<0){b=0;} 
			string x=ans.substr(a,b);                
			string y=unword[it->second];
			int diff=distance(x,y);
			if(diff==rnd(0,1)){cand.ev=100000-diff;}
			else{cand.ev=0;}    
			cand.ev+=-diff+(i+1)*100;    
			vn.push_back(cand);    
			}
		}
		printf("depth=%d/%d\n",i+1,TURN);
		dque.clear();
		vector<pair<int,int> >vec;
		for (int j = 0; j < (int)vn.size(); j++) {
		vec.push_back(make_pair(-vn[j].ev,j));
		}
		sort(vec.begin(),vec.end());
		int push_node=0;
		bool congrats=false;
		for (int j = 0; push_node < 10;j++) {
			if(j>=(int)vec.size()){break;}
			int x=vec[j].second;
			node temp = vn[x];
			if(temp.ev>maxvalue){
				maxvalue=temp.ev;
				bestAction=temp;
				cout<<temp.str<<endl;
				congrats=true;
			}
			if (i < TURN) {
				dque.push_back(temp);
				push_node++;
			}
		}
		if(!congrats||i==(int)ans.size()-1){return bestAction;}
	}
	return bestAction;
}

int counter=0;

void reading(string s){
	
	string line;
	vector<string> t_path;
	ifstream myfile (s);
	while(getline(myfile,line)){    
	t_path.push_back(line+'&');    
	}
	myfile.close();    
	
	for(int i=0;i<(int)t_path.size();i++){
	
	for(int j=0;j<(int)t_path[i].size();j++){
        
	FILE *file;
	file = fopen("ascii.txt", "w");
	fprintf(file, "%c",t_path[i][j]);
	fclose(file);
        ifstream ifs("ascii.txt");    
        string w;
	ifs >> w;
        ifs.close();    
        counter++;
	if(word[w]==0){
	word[w]=counter;
	unword[counter]=w;
	}
	}
	}    
        vector<int>vec;
        for(int i=0;i<(int)t_path.size();i++){
        for(int j=0;j<(int)t_path[i].size();j++){
        
	FILE *file;
	file = fopen("ascii.txt", "w");
	fprintf(file, "%c",t_path[i][j]);
	fclose(file);
        ifstream ifs("ascii.txt");    
        string w;
	ifs >> w;
        ifs.close();
	vec.push_back(word[w]);
	prob[word[w]]++;
        }
    
	for(int r=0;r<(int)vec.size()-1;r++){
	int cur=vec[r];
	int nexthash=vec[r+1];
	bool find=false;
	auto p = words.equal_range(cur);
	for (auto it = p.first; it != p.second; ++it) {
	if(it->second==nexthash){find=true;break;}
	}
	if(!find){words.emplace(cur,nexthash);}
	}
    }
}
int main(){
	
	string start;
	
	getline(cin, start,'$');
	while(1){
	bool escape=true;
	for(int i=0;i<(int)start.size();i++){
        if(start[i]=='\n'){start.erase(i, 1);escape=false;break;}
	}
	if(escape){break;}
	}    
    
    
	int mind=1000000;
	int find=-1;
    
	for(int i=1;i<=21;i++){
	string s=to_string(i);
	reading(s+"_problem.txt");
	string line;
	string t_path="";
	ifstream myfile (s+".txt");
	while(getline(myfile,line)){
	t_path+=line;    
	}
	myfile.close();
	while(1){
	if((int)t_path.size()<CODE_LENGTH){t_path+="&";}
	else{break;}
	}   
	int d=distance(start,t_path);    
	if(mind>d){mind=d;find=i;}
	cout<<"i="<<i<<",d="<<d<<endl;
	}
	
	string line;
	string tmp="";
	string t_path="";
	ifstream myfile (to_string(find)+"_problem.txt");
	while(getline(myfile,line)){
	if(line!=""){    
	t_path+=line+'&';
	if(tmp==""){tmp=line[0];}
	}    
	}
	myfile.close();
	ans=t_path;
	cout<<find<<"_problem.txt"<<endl;
	
	string rrr;
	int cur;    
	cur=word[tmp];
	unordered_map<int, int>v2;
	node n;
	n.cur=cur;
	n.v=v2;
	n.str=unword[cur];
	n.ev=0;
	n=BEAM_SEARCH2(n);
	for(int i=0;i<(int)n.str.size();i++){
	if(n.str[i]=='&'){n.str[i]='\n';}
	}
	cout<<"miles="<<n.ev<<",output=\n"<<n.str;
	ofstream fi("gene.txt");
	fi<<n.str;
	fi.close();    
	return 0;
}
