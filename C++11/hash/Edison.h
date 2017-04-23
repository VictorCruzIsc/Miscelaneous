#ifndef EDISON_H
#define EDISON_H

#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class Edison{
public:
	Edison();
	Edison(int identifier, int osIdentifier, vector<int> &ports, bool updated);
	~Edison();

	int getIdentifier(){ return _identifier; }
	int getOsIdentifier(){ return _osIdentifier; }
	vector<int> getPorts(){ return _ports; }
	bool isUpdated(){ return _updated; }

private:
	int _identifier;
	int _osIdentifier;
	vector<int> _ports;
	bool _updated;
};
#endif