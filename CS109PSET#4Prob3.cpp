/*
Problem: 
A robot is located at the center of a square world that is 10km on each side. A package is dropped 
off in the robot's world at point (x,y) that is uniformly (continuously) distributed in the square. 
If the robot's starting location is designated to be (0,0) and the robot can only move up/down/left/right
parallel to the sides of the square, the distance the robot must travel to get to the package at point (x,y)
is |x| + |y|. Let D = the distance the robot travels to get to the package. Compute E[D].  
*/
#include <iostream>
#include <cstdlib>
#include <cmath> 
using namespace std; 

double power(double a, int x){
	if (x == 0) return 1.0; 
	if (x == 1) return a;  
	return power(a,x/2)*power(a,x/2)*power(a,x%2); 
}

int main(){
	double val = 0.0;  
	for (int i = -10; i <= 10; i++){
		for (int j = -10; j <= 10; j++){
			val += power(0.25,abs(i))*power(0.25,abs(j))*(abs(i) + abs(j));    
		}
	}
	cout << val << endl;  // val is E[D]. 
	return 0; 
}
