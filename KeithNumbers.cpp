/*
CS106X first section
Problem 2: Keith Numbers 
This program simply prints all the Keith numbers between 1 and 10000 inclusive. 

Sample input: 
enter upper bound: 10000 

Sample output: 
1
2
3
4
5
6
7
8
9
14
19
28
47
61
75
197
742
1104
1537
2208
2580
3684
4788
7385
7647
7909
*/
#include <iostream>
#include <cstdio> 
#include <vector> 
#include <algorithm>
#include <numeric>  
using namespace std; 

bool isKeith(int n){
	vector<int> v; 
	int original_num = n; 
	while (n){
		v.push_back(n%10); 
		n /= 10; 
	}
	reverse(v.begin(),v.end()); 
	if (v.size() == 1) return true;  
	v.push_back(accumulate(v.begin(),v.end(),0));  
	int index = 0; 
	int sum = 0;
	while (v[v.size()-1] <= original_num){
		sum += v[index];  
		int new_val = accumulate(v.begin(),v.end(),0) - sum;  
		if (new_val == original_num) return true; 
		v.push_back(new_val);  
		++index; 
	}	
	return false; 
}

int main(){
	int n; 
	cout << "enter upper bound:"; 
	cin >> n; 
	for (int i = 1; i <= n; i++){
		if (isKeith(i)){
			cout << i << endl; 
		}
	}
	return 0; 
}
