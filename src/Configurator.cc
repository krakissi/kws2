#include "Configurator.h"

Configurator::Configurator(string path){
	this->path = path_original = path;

	build();
}

// Load configuration.
void Configurator::build(){
	ifstream cfg(path);
	string buffer;

	char *cbuf = NULL;
	size_t n = 0;

	while(1){
		getline(cfg, buffer);
		if(!cfg.good())
			break;
		int length = buffer.length();

		// The shortest meaningful config line is a single-character key name with no value. Lines less than 2 length are guaranteed to be unparseable.
		if(length < 2)
			continue;

		// The line is a comment.
		if(buffer[0] == '#')
			continue;

		// Manage memory for C-string ops.
		if(length > n){
			if(cbuf)
				free(cbuf);

			n = length + 1;
			cbuf = (char*) calloc(n, sizeof(char));
		}

		// Create a mutable copy.
		strcpy(cbuf, buffer.c_str());

		// Find the first occurrence of =; this is where we'll split.
		char *b = strchr(cbuf, '=');
		if(!b)
			continue;

		char *a = b - 1;
	   	char *c = b + 1;

		while((a > cbuf) && isspace(*a))
			a--;

		// keyname was all whitespace, or empty.
		if(a < cbuf)
			continue;
		*(a + 1) = 0;

		while((c < cbuf + length) && isspace(*c))
			c++;

		string key, value;
		key.assign(cbuf);
		value.assign(c);

		config[key] = value;
	}

	// Release manually allocated memory.
	if(cbuf)
		free(cbuf);
}

// Get a given value. Will return a valid string of zero length for unset values.
string Configurator::get(string key){
	return config[key];
}
