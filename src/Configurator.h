#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>

using namespace std;

class Configurator {
	unordered_map<string, string> m_config;
	string m_path_original;
	string m_path;

public:
	Configurator(string path);
	void build();
	string get(string key);
};

#endif
