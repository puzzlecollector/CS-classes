#include <iostream> 
#include <vector> 
using namespace std; 


void diceRoll(int n,vector<int> &v){
	if (n == 0){
		for (int i = 0; i < v.size();  i++){
			cout << v[i] << " "; 
		}
		cout << endl; 
		return; 
	}
	for (int i = 1; i <= 6; i++){
		v.push_back(i);  
		diceRoll(n-1,v);  
		v.pop_back(); 
	}
}

void diceSum(int dice,int sum,int target,vector<int> &collection){
	if (dice == 0){
		if (sum == target){
			for (int i = 0; i < collection.size(); i++){
				cout << collection[i] << " ";  
			}
			cout << endl; 
		}
		return;  
	}
	for (int i = 1; i <= 6; i++){
		collection.push_back(i);  
		diceSum(dice-1,sum+i,target,collection); 
		collection.pop_back(); 
	}
}


void diceSum2(int dice,int sum,int target,vector<int> &collection){ // with no repeats
	if (dice == 0){
		if (sum == target){
			for (int i = 0; i < collection.size(); i++){
				cout << collection[i] << " ";  
			}
			cout << endl; 
		}
		return;  
	}
	for (int i = 1; i <= 6; i++){
		collection.push_back(i);  
		for (int j = i; j <= 6;j++){
			collection.push_back(j);  
			diceSum(dice-2,sum+i+j,target,collection);  
			collection.pop_back(); 
		}
		collection.pop_back();  
	}
}

int main(){
	vector<int> v; 
	diceRoll(2,v);  
	cout << "======" << endl; 
	vector<int> collection;  
	diceSum(2,0,7,collection); 
	cout << "======" << endl; 
	collection = vector<int>(); 
	diceSum2(2,0,7,collection);  
	return 0;    
}
