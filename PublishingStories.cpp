/*
Problem 1: publishing stories 
This program accepts a story template, and we use a map 
in order to replace the strings in curly braces to the corresponding strings 
in the map.  

Sample input: 
enter number of keys in map : 3 
actor kaidi-yan 
restaurant reposado 
rating 5 
enter storyTemplate: {actor} gave {restaurant} a {rating}-star review.

Sample output: 
kaidi-yan gave reposado a 5-star review. 
*/  
#include <iostream>
#include <cstdlib>
#include <string> 
#include <map> 
#include <algorithm> 
using namespace std; 

string generateStory(string storyTemplate, map<string,string>& data){
	string s = storyTemplate;  
	int startIndex; 
	// one method is to start with a single story template 
	// and after we replace one bracket, we count all over again and continue until we find the next bracket 
	// because length changes all the time.  
	int cnt = 0; 
	for (int i = 0; i < s.length(); i++){
		if (s[i] == '{') ++cnt;  
	}
	while (cnt--){
		for (int i = 0; i < s.length(); i++){
			if (s[i] == '{') startIndex = i; 
			if (s[i] == '}'){
				s.replace(s.begin()+startIndex,s.begin()+i+1,data[s.substr(startIndex+1,i-startIndex-1)]);  
				break; 
			}
		}
	}
	return s; 
}


int main(){
	map<string,string> m; 
	int n; 
	string a,b,sentence; 
	cout << "enter number of keys in map:"; 
	cin >> n;  
	for (int i = 0; i < n; i++){
		cin >> a >> b; 
		m[a] = b; 
	}
	cout << "enter storyTemplate:";
	for (int i = 0; i < 2; i++){
		getline(cin,sentence); 
	}
	cout << generateStory(sentence,m) << endl; 
	return 0; 
}
