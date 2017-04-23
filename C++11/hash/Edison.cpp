#include "Edison.h"

Edison::Edison() : _identifier(0), _osIdentifier(0), _updated(false){
	_ports.resize(0);
}

Edison::Edison(int identifier, int osIdentifier, vector<int> &ports,
	bool updated) : _identifier(identifier), _osIdentifier(osIdentifier),
	_ports(ports), _updated(updated){}
