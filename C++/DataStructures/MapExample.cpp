#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Results{
	int initialUserAssigned;
	int finalUserAssigned;
	int totalErrors;
	int totalOk;
	void info();
};

void Results::info(){
	cout << initialUserAssigned << " ";
	cout << finalUserAssigned <<  " ";
	cout << totalErrors << " ";
	cout << totalOk << endl;
}

int main(){
	cout << "HW" << endl;
	map<int, string> users;

	users[1166711] = "NVCH";
	users[1166712] = "RRM";
	users[1166713] = "JAM";

	if(users.find(1166714) == users.end()){
		cout << "El valor 1166714 no esta en el mapa" << endl;
	}

	string s = users[1166711];
	cout << s << endl;

	Results *results =  new Results();
	results->initialUserAssigned = 0;
	results->finalUserAssigned = 1;
	results->totalErrors = 50;
	results->totalOk = 1000;

	//results->info();
	cout << results->totalOk << endl;

	map<int, Results*> resultsMap;
	
	resultsMap[1] = results;

	Results *x = new Results();
	x->initialUserAssigned = 100;
	x->finalUserAssigned = 200;        
	x->totalOk = 2000;

	Results *y = new Results();
	y->totalOk = 3000;
	y->initialUserAssigned = 800;
        y->finalUserAssigned = 900;

	resultsMap[300] = x;
	resultsMap[1700] = y;

	cout << resultsMap[300]->totalOk << endl;
        cout << resultsMap[1700]->totalOk  << endl;

	Results *current;
	current = resultsMap[300];
	current->totalOk = 1000;

	resultsMap[1700] -> totalOk = 5000;

	cout << resultsMap[300]-> totalOk << endl;
	cout << resultsMap[1700]->totalOk << endl;
}
