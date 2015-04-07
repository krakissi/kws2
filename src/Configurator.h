#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>

using namespace std;

class Configurator {
	unordered_map<string, string> config;
	string path_original;
	string path;

public:
	Configurator(string path);
	void build();
	string get(string key);
};

#endif
