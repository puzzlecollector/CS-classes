#include <iostream>
#include <cstdio> 
using namespace std; 

int binaryRunCnt(int arr[],int key,int &cnt){
	int low = 0, high = 9; 
	while (low <= high){
		++cnt;  
		int mid = (low+high)/2;  
		if (arr[mid] == key) return mid;  // equality test. 
		else if (arr[mid] < key) low = mid+1;  
		else high = mid-1;  
	}
	return -1; // will never get here when key is in [1,10] 
}

int main(){
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};   
	int sum = 0; 
	for (int key = 1; key <= 10; key++){
		int cnt = 0;  
		binaryRunCnt(arr,key,cnt); 
		sum += cnt;  
		cout << key << ":" << cnt << endl; 
	}
	cout << "sum:" << sum << endl; 
	return 0; 
}

