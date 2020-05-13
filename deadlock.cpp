#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>



using namespace std;

class Node{
	
};
class NodeList{
	int nproc,nrec;
	int* rec;
	int** AdjMatrix;
	int mx,my;
	int cmx,cmy,crx;
	public:
	NodeList(){
		nproc=0;
		nrec=0;
		mx=0;
		my=0;
		cmx=0;
		cmy=0;
		crx=0;
		rec=NULL;
		//*AdjMatrix=NULL;
		AdjMatrix=NULL;
	}
	~NodeList(){
		DeleteMatrix();
		DeleteResource();
	}
	void UpdateMatrixSize(){
		int total=nproc+nrec;
		UpdateMatrixSize(total,total);
	}
	
	void UpdateMatrixSize(int x, int y){
		mx=x;
		my=y;
		AdjMatrix= new int*[x];
		for(int i=0;i<y;i++){
			AdjMatrix[i]=new int[y];
		}		
	}
	
	void UpdateResourceSize(){
		UpdateResourceSize(nrec);
	}
	
	void UpdateResourceSize(int x){
		rec=new int[x];
	}
	
	void DeleteMatrix(){
		if(AdjMatrix!=NULL){
			for(int i=0;i<mx;i++){
				delete AdjMatrix[i];
			}
			delete AdjMatrix;
		}
	}
	
	void DeleteResource(){
		if (rec!=NULL){
		delete rec;
		}
	}
	
	void UpdateMatrix(int term){
		AdjMatrix[cmx][cmy]=term;
		cmy=(cmy+1)%(my);
		if(cmy==0){
			cmx=(cmx+1)%(mx);
		}
	}
	
	void UpdateResource(int term){
		rec[crx]=term;
		crx+=1;
	}
	
	void Update(int term){
		if(crx==nrec){
			UpdateMatrix(term);
		}else{
			UpdateResource(term);
		}
	}
	
	string GetString() {
		string str="Number of resources: ";
		for(int i = 0; i<nrec;i++){
			str+=to_string(rec[i]);
			if(i!=nrec-1){
				str+=",";
			}
		}
		str+="\n";
		for(int i=0;i<mx;i++){
			for(int j=0;j<my;j++){
				str+=to_string(AdjMatrix[i][j]);
				if(j!=my-1){
					str+=",";
				}
			}
			str+="\n";
			
		}
		
		return str;
		
	}
	
	
	void SetProc(int p){
		nproc=p;
		if(nrec!=0){
			UpdateMatrixSize();
		}
	}
	
	void SetRec(int r){
		nrec=r;
		UpdateResourceSize();
		if(nproc!=0){
			UpdateMatrixSize();
		}
	}
	
	int FindSink(){
		for(int i = 0 ; i<nproc;i++){
			int requests=0;
			for(int j = nproc; j<nrec+nproc;j++){
				requests+=AdjMatrix[i][j];
			}
			if(requests==0){
				return i;
			}
			
		}
		return -1;
	}
	
};

NodeList readFile(string fname){
	NodeList list= NodeList();
	char c;
	ifstream in;
	in.open(fname);
	string t="";
	int nrec=0,nproc=0;
	int recsGot=0;
	int temp=0;
	while (in>>c){
		t+=c;
		if (c=='%'){
			t="";
			while(c!='\n'){
				in>>noskipws>>c;
				in>>skipws;
			}
			
		}else{
			if(t.compare("num_processes=")==0){//Get number of processes
				t="";
				in>>nproc;
				list.SetProc(nproc);
				////cout<<nproc<<endl;
			}
			
			if(t.compare("num_resources=")==0){//Get number of resources
				t="";
				in>>nrec;
				list.SetRec(nrec);
				////cout<<nrec<<endl;
			}
			if(c==','||c=='\n'){
				temp=stoi(t);
				list.Update(temp);
				////cout<<temp<<endl;
				t="";
				recsGot++;
				if(recsGot==nrec-1){//Extra rec left hanging
					in>>temp;
					list.Update(temp);
					////cout<<temp<<endl;
				}
				if(recsGot==nrec){//Delim on EOL (\n)
					in>>noskipws;
				}
			}
		}	
	}
	return list;

	
	
}

int main(){
	NodeList list = readFile("In.txt");
	cout<<"Found graph that looks like:\n"<<list.GetString();
	int sink = list.FindSink();
	if(sink!=-1){
		cout<<"Not deadlocked. Sink at node "<<sink+1<<".\n";
	} else {
		cout<<"Deadlocked\n";
	}
	return 0;
}

