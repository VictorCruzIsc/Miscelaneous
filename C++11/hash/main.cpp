#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <functional>
#include <iostream>
#include <string>

#include "Edison.h"

using namespace std;

int main(int argc, char** argv){
	vector<int> ports = {80, 94, 97};
	vector<int> portsSecond = {81, 104, 97};

	Edison *edisonOne = new Edison(534, 123, ports, false);
	Edison *edisonTwo = new Edison(534, 123, ports, false);
	Edison *edisonTree = new Edison(535, 123, ports, false);
	Edison *edisonFour = new Edison(535, 123, ports, false);
	Edison *edisonFive = new Edison(536, 124, portsSecond, true);

	hash<Edison *> comparingEdison;

	cout << "One - Two " << (comparingEdison(edisonOne) == comparingEdison(edisonTwo)) << endl; // True
	cout << "Tree - Four " << (comparingEdison(edisonTree) == comparingEdison(edisonFour)) << endl; // True
	cout << "One - Five " << (comparingEdison(edisonOne) == comparingEdison(edisonFive)) << endl; // True


	hash<int> hashingInt;
	size_t inthash = hashingInt(54);
	cout << "hash " << inthash << endl;

	hash<string> hashinString;
	size_t stringHash = hashinString("Something");
	cout << "hash string " << stringHash << endl;

	hash<Edison *> hashingEdison;
	hash<Edison *> hashingEdison2;
	size_t edisonHash = hashingEdison(edisonOne);
	cout << "hash Edison 1 " << edisonHash << endl;
	
	size_t edisonHash2 = hashingEdison2(edisonOne);
	cout << "hash Edison 2 " << edisonHash2 << endl;

	cout << (edisonHash == edisonHash2) << endl;
}
