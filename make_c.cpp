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

#define TURN 1000 

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
bool dot;
int length;    
};

int dot_value=0;

void callpy(){
    
    system("python3 compile.py");
    
    /*
    
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(-1);
	} else if (pid == 0) {
		// 子プロセスで別プログラムを実行
		execl("python3 intel.py", "python3 intel.py");
		exit(-1);
	}

	// 親プロセス
	int status;
	pid_t r = waitpid(pid, &status, 0); //子プロセスの終了待ち
    
    */
    
}

node BEAM_SEARCH(node n) {
    if(n.dot){return n;}
	vector<node>dque;
	dque.push_back(n);

	node bestAction=n;
    
    int maxvalue=0;

	//2手目以降をビームサーチで探索
	for (int i = 0; i < TURN; i++) {
		int ks = (int)dque.size();
		vector<node>vn;
		for (int k = 0; k < ks; k++) {
			node temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=2){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
				node cand = temp;
				string s=unword[it->second];
				if(s==""||s==" "||(it->second==0)){cand.ev=0;}
				cand.cur=it->second;
				cand.str=cand.str+'\n'+unword[it->second];
				cand.ev=cand.ev+prob[it->second];
				if(cand.dot){cand.ev+=dot_value;}
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
	
	int maxvalue=0;

	//2手目以降をビームサーチで探索
	for (int i = 0;i<TURN; i++) {
		int ks = (int)dque.size();
		vector<node>vn;
		for (int k = 0; k < ks; k++) {
			node temp = dque[k];
			(temp.v)[temp.cur]++;
			if((temp.v)[temp.cur]>=2){continue;}
			auto p = words.equal_range(temp.cur);
			for (auto it = p.first; it != p.second; ++it) {
			node cand = temp;
			string s=unword[it->second];    
			if(s==""||s==" "||(it->second==0)){cand.ev=0;}
			cand.cur=it->second;
			cand.str=cand.str+'\n'+unword[it->second];
			node n2=BEAM_SEARCH(cand);
			ofstream fi("gene.cpp");
			fi<<n2.str;
			fi.close();
			callpy();
			cand.ev=n2.ev+prob[it->second];
			int number;
			FILE *file;
			file = fopen("log.txt", "r");
			fscanf(file, "%d", &number);
			fclose(file);
			if(number==0){cand.ev=0;}    
			if(cand.dot){cand.ev+=100000;}
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
		for (int j = 0; push_node < 10 ;j++) {
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

int counter=0;

void reading(string s){

    string line;
	vector<string> t_path;
	ifstream myfile (s);
	while(getline(myfile,line)){

	t_path.push_back(line);

	}
	myfile.close();

	for(int i=0;i<(int)t_path.size();i++){
	
        bool space=false;
        string www="";
        for(int j=0;j<(int)t_path[i].size();j++){
        
        char w=t_path[i][j];
            
        if(j==(int)t_path[i].size()-1){
        counter++;
        www+=w;    
        bool isword=true;  
        if(isword&&word[www]==0){    
        word[www]=counter;
        unword[counter]=www;    
        }
        www="";
        }
        else{
        www+=w;
        }
            
        }
	}
	
	vector<int>vec;
    	
	for(int i=0;i<(int)t_path.size();i++){
	
        bool space=false;
        string www="";
            
        for(int j=0;j<(int)t_path[i].size();j++){
            
        char w=t_path[i][j];
            
        if(j==(int)t_path[i].size()-1){
        www+=w;    
        vec.push_back(word[www]);
        prob[word[www]]++;
        if(prob[word[www]]>dot_value){dot_value=prob[word[www]]+1;}    
        www="";
        }
        else{
        www+=w;
        }
           
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
    
    for(int i=1;i<=17;i++){
    string s=to_string(i);
    reading(s+".txt");
    }
	
	string rrr;
	int cur;
	cur=1;
	unordered_map<int, int>v2;
	//g_str2(cur,0,v2,rrr,0);
	node n;
	n.cur=cur;
	n.v=v2;
	n.str=unword[cur];
	n.ev=0;
	n.dot=false;
	n=BEAM_SEARCH2(n);
	cout<<"ev="<<n.ev<<",output=\n"<<n.str<<endl;
	ofstream fi("gene.cpp");
	fi<<n.str;
	fi.close();
	return 0;
}
