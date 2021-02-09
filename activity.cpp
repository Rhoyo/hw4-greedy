#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct job{
int num;
int s;
int f;
};

//my mergesort algorithm from hw1
vector<job> merge(vector<job> v1, vector<job> v2){
		vector<job> vec;
		int iter1=0;
		int iter2=0;

	
		while(iter1<v1.size()&&iter2<v2.size()){
			if(v1[iter1].s<=v2[iter2].s){
				vec.push_back(v2[iter2]);
				iter2++;
			}
			else{	
				vec.push_back(v1[iter1]);
				iter1++;	
			}
		}
		while(iter1<v1.size()){
				vec.push_back(v1[iter1]);
				iter1++;	
		}
		while(iter2<v2.size()){
				vec.push_back(v2[iter2]);
				iter2++;
		}
	
		return vec;
}

vector<job> mergeSort(vector<job> vec){
	if(vec.size()>1){	

		vector<job> v1;
		vector<job> v2;
		vector<job> r;
		
		for(int i=0;i<vec.size()/2;i++){
			v1.push_back(vec[i]);
		}
		for(int i=vec.size()/2;i<vec.size();i++){
			v2.push_back(vec[i]);
		}

		v1=mergeSort(v1);
		v2=mergeSort(v2);
		
		r=merge(v1,v2);
		return r;
					
	}
	else{
		return vec;
	}
}



vector<int> greedy(vector<job> jobs){
	vector<int> out;

	//sort here for latest start times
	jobs=mergeSort(jobs);
	
	//start searching
	out.push_back(jobs[0].num);
	int iter=1;
	struct job j=jobs[0];
	while(iter!=jobs.size()){
		if(jobs[iter].f<=j.s){
			out.push_back(jobs[iter].num);
			j=jobs[iter];
		}
		iter++;
	}
	return out;	
}

int main(){
	int set=0;
	int size;
	ifstream act;
	act.open("act.txt");
	if(!act)
		return 1;

	while(act >> size){ //while input is still good, input size
		set++;
		vector<job> jobs;
	
		struct job x;
		for(int i=0; i<size;i++){ //filling task array from txt file
			act >> x.num;
			act >> x.s;
			act >> x.f;
			jobs.push_back(x);

		}
		vector<int> arr = greedy(jobs); //using greedy algorithm

		//printing output
		cout<<endl;
		cout<<"Set "<<set<<endl;
		cout<<"Num: "<<arr.size()<<endl;
		cout<<"Activities: ";
		for(int i=0;i<arr.size();i++)
			cout<<arr[i]<<" ";
		cout<<endl<<endl;

	}
	act.close();
}
