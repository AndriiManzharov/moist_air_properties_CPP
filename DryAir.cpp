#include "pch.h"
#include "DryAir.h"
#include "tools.h"
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
#include <exception>
const std::string FILE_DRY_AIR_HEAT_CAPACITY = "tables\\DryAirHeatCapacity.dat";
std::vector<DryAir::Data>* dry_air_heat_capacity = new std::vector<DryAir::Data>;

void DryAir::LoadData()
{
	std::ifstream fin;
	try
	{
		std::string line;
		fin.open(FILE_DRY_AIR_HEAT_CAPACITY);
		double p = 0.0;
		while (!fin.eof())
		{
			getline(fin, line);
			if (line[0] == '#')
			{
				line.erase(line.begin());
				std::stringstream ss;
				ss << line;
				ss >> p;
				continue;
			}
				
			double* data = new double[2];
			split(line, data);
			DryAir::Data dt(p, data[0], data[1]);
			dry_air_heat_capacity->push_back(dt);
			delete[] data;
		}
		fin.close();
		dry_air_heat_capacity->shrink_to_fit();// Освобождаем пустые ячейки (запас)
	}
	catch (std::exception& ex)
	{

		//cout << "An error occurred while working with the file " << FILE_WATER_HEAT_CAPACITY << endl;
		//wstring error = L"An error occurred while working with the file WaterHeatCapacity.dat";
		//MessageBox(nullptr, error.c_str(), L"ERROR", 0x00000000L);

	}

	//cout << water_heat_capacity->size() << endl;

}
double DryAir::HeatCapacity(double p, double t)
{
	// Выход за диапазон
	if (t < -70 || t > 1500)
		throw std::exception();
	else if (p < 1000 || p > 10000000)
		throw std::exception();
	p = p*pow(10, -5);
	
	double p1 = 0, p3 = 0;

	double t1_p1 = 0, t3_p1 = 0;
	double cp1_p1 = 0, cp3_p1 = 0;
	
	double t1_p3 = 0, t3_p3 = 0;
	double cp1_p3 = 0, cp3_p3 = 0;

	
	for (int i = 0; i < dry_air_heat_capacity->size(); i++)
	{
		// Поиск давления p1 и значения температуры и теплоемкости
		if (p >= dry_air_heat_capacity->at(i).p && t >= dry_air_heat_capacity->at(i).t)
		{
			p1 = dry_air_heat_capacity->at(i).p;
			t1_p1 = dry_air_heat_capacity->at(i).t;
			cp1_p1 = dry_air_heat_capacity->at(i).cp;
		}
		// Поиск давления  значения температуры и теплоемкости при p1
		else if (p >= dry_air_heat_capacity->at(i).p && t <= dry_air_heat_capacity->at(i).t)
		{
			
			t3_p1 = dry_air_heat_capacity->at(i).t;
			cp3_p1 = dry_air_heat_capacity->at(i).cp;
		}
	}
	// Нахождение теплоемкости при давлении p1
	double cp_p1 = (cp1_p1 + (((cp3_p1 - cp1_p1) * (t - t1_p1)) / (t3_p1 - t1_p1)));
	
	for (int i = 0; i < dry_air_heat_capacity->size(); i++)
	{
		if (p <= dry_air_heat_capacity->at(i).p && t >= dry_air_heat_capacity->at(i).t)
		{
			p3 = dry_air_heat_capacity->at(i).p;
			t1_p3 = dry_air_heat_capacity->at(i).t;
			cp1_p3 = dry_air_heat_capacity->at(i).cp;
		}

		else if (p <= dry_air_heat_capacity->at(i).p && t <= dry_air_heat_capacity->at(i).t)
		{

			t3_p3 = dry_air_heat_capacity->at(i).t;
			cp3_p3 = dry_air_heat_capacity->at(i).cp;
		}
	}
	double cp_p3 = (cp1_p3 + (((cp3_p3 - cp1_p3) * (t - t1_p3)) / (t3_p3 - t1_p3)));
	
	// Нахождение теплоемкости при давлении p
	return (cp_p1 + (((cp_p3 - cp_p1) * (p - p1)) / (p3 - p1)));

}
