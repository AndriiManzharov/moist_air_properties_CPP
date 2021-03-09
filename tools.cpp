

#include "pch.h"
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "tools.h"

void split(std::string line, double* data)
{
	std::string _line;
	int j = 0;
	for (int i = 0; i <= line.size(); i++)
	{
		if (line[i] == '\t' || i == line.size())
		{
			std::stringstream ss;
			ss << _line;
			ss >> data[j];
			if (ss.fail())
			{
				// Œ¡–¿¡Œ“¿“‹ Œÿ»¡ ”!!!!!!
			}
			_line = "";
			j++;
			continue;
		}
		_line += line[i];
	}
}

double C_to_K(double t)
{
	return t + 273.15;
}

double K_to_C(double T)
{
	return T - 273.15;
}
