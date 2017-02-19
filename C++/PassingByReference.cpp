#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

int main(){
	map<int, int> firstMap;
	firstMap[1] = 2;
	firstMap[2] = 3;
	firstMap[3] = 4;
	firstMap[4] = 5;

	cout << "firstMap key: 1 " << firstMap[1] << endl;

	map<int, int> secondMap = firstMap;

	cout << "secondMap key: 1 " << secondMap[1] << endl;

	secondMap[1] = 50;

	cout << "firstMap key: 1 " << firstMap[1] << endl;
	cout << "secondMap key: 1 " << secondMap[1] << endl;

	map<int, int> *thirdMap = &firstMap;
	
	cout << "thirdMap key: 1 " << (*thirdMap)[1] << endl;
	cout << "thirdMap key: 1 " << thirdMap->operator[](1) << endl;

	thirdMap->operator[](1) = 1000;

	cout << "firstMap key: 1 " << firstMap[1] << endl;

}
