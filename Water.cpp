#include "pch.h"
#include "Water.h"
#include <fstream>
#include <string>
#include "tools.h"

std::string FILE_WATER_HEAT_CAPACITY = "tables\\WaterHeatCapacity.dat";
const std::string FILE_HEAT_OF_EVAPORATION = "tables\\HeatofEvaporation.dat";
const std::string FILE_WATER_VAPOUR_HEAT_HAPACITY = "tables\\WaterVapourHeatCapacity.dat";
const std::string FILE_WATER_VAPOUR_SATURATION_PRESSURE = "tables\\WaterVapourSaturationPressure.dat";

std::vector<Water::Data_t_c>* water_heat_capacity = new std::vector<Water::Data_t_c>;
std::vector<Water::Data_t_r>* water_heat_of_evaporation = new std::vector<Water::Data_t_r>;
std::vector<Water::Data_t_c>* vapour_heat_capacity = new std::vector<Water::Data_t_c>;
std::vector<Water::Data_t_p>* vapour_saturation_pressure = new std::vector<Water::Data_t_p>;
void Water::LoadData()
{
	try
	{
		std::string line;		
		// Загрузка данных из FILE_WATER_HEAT_CAPACITY
		std::ifstream fin;
		fin.open(FILE_WATER_HEAT_CAPACITY);
		while (!fin.eof())
		{
			double* data = new double[2];
			getline(fin, line);
			split(line, data);
			Water::Data_t_c tc(data[0], data[1]);
			water_heat_capacity->push_back(tc);
			delete[] data;
		}
		fin.close();
		fin.clear();
		water_heat_capacity->shrink_to_fit();// Освобождаем пустые ячейки (запас)

		// Загрузка данных из FILE_HEAT_OF_EVAPORATION
		fin.open(FILE_HEAT_OF_EVAPORATION);
		while (!fin.eof())
		{
			double* data = new double[2];
			getline(fin, line);
			split(line, data);
			Water::Data_t_r tr(data[0], data[1]);
			water_heat_of_evaporation->push_back(tr);
			delete[] data;
		}
		fin.close();
		fin.clear();
		water_heat_of_evaporation->shrink_to_fit();// Освобождаем пустые ячейки (запас)

		// Загрузка данных из FILE_WATER_VAPOUR_HEAT_HAPACITY
		fin.open(FILE_WATER_VAPOUR_HEAT_HAPACITY);
		while (!fin.eof())
		{
			double* data = new double[2];
			getline(fin, line);
			split(line, data);
			Water::Data_t_c tr(data[0], data[1]);
			vapour_heat_capacity->push_back(tr);
			delete[] data;
		}
		fin.close();
		fin.clear();
		vapour_heat_capacity->shrink_to_fit();// Освобождаем пустые ячейки (запас)

		// Загрузка данных из FILE_WATER_VAPOUR_SATURATION_PRESSURE
		fin.open(FILE_WATER_VAPOUR_SATURATION_PRESSURE);
		while (!fin.eof())
		{
			double* data = new double[2];
			getline(fin, line);
			split(line, data);
			Water::Data_t_p tp(data[0], data[1]);
			vapour_saturation_pressure->push_back(tp);
			delete[] data;
		}
		fin.close();
		fin.clear();
		vapour_heat_capacity->shrink_to_fit();// Освобождаем пустые ячейки (запас)
	}
	catch (std::exception& ex)
	{

		//cout << "An error occurred while working with the file " << FILE_WATER_HEAT_CAPACITY << endl;
		//wstring error = L"An error occurred while working with the file WaterHeatCapacity.dat";
		//MessageBox(nullptr, error.c_str(), L"ERROR", 0x00000000L);

	}

	//cout << water_heat_capacity->size() << endl;

}

double Water::VaporHeatCapacity(double t)
{
	double t1 = 0, t3 = 0;
	double cp1 = 0, cp3 = 0;
	for (int i = 0;i < vapour_heat_capacity->size(); i++)
	{
		if (t >= vapour_heat_capacity->at(i).t)
		{
			t1 = vapour_heat_capacity->at(i).t;
			cp1 = vapour_heat_capacity->at(i).cp;
		}
		else if (t <= vapour_heat_capacity->at(i).t)
		{
			t3 = vapour_heat_capacity->at(i).t;
			cp3 = vapour_heat_capacity->at(i).cp;
			break; // Выходим так как найдено следующее значение после искомого
		}
	}
	return (cp1 + (((cp3 - cp1) * (t - t1)) / (t3 - t1)));
}

double Water::WaterHeatCapacity(double t)
{
	double t1 = 0, t3 = 0;
	double cp1 = 0, cp3 = 0;
	for (int i = 0;i < water_heat_capacity->size(); i++)
	{
		if (t >= water_heat_capacity->at(i).t)
		{
			t1 = water_heat_capacity->at(i).t;
			cp1 = water_heat_capacity->at(i).cp;
		}
		else if (t <= water_heat_capacity->at(i).t)
		{
			t3 = water_heat_capacity->at(i).t;
			cp3 = water_heat_capacity->at(i).cp;
			break; // Выходим так как найдено следующее значение после искомого
		}
	}
	return (cp1 + (((cp3 - cp1) * (t - t1)) / (t3 - t1)));
}
double Water::HeatOfEvaporation(double t)
{
	double t1 = 0, t3 = 0;
	double r1 = 0, r3 = 0;
	for (int i = 0;i < water_heat_of_evaporation->size(); i++)
	{
		if (t >= water_heat_of_evaporation->at(i).t)
		{
			t1 = water_heat_of_evaporation->at(i).t;
			r1 = water_heat_of_evaporation->at(i).r;
		}
		else if (t <= water_heat_of_evaporation->at(i).t)
		{
			t3 = water_heat_of_evaporation->at(i).t;
			r3 = water_heat_of_evaporation->at(i).r;
			break; // Выходим так как найдено следующее значение после искомого
		}
	}
	return (r1 + (((r3 - r1) * (t - t1)) / (t3 - t1)));
}

double Water::SaturatedPressure(double t)
{
	double t1 = 0, t3 = 0;
	double p1 = 0, p3 = 0;
	for (int i = 0;i < vapour_saturation_pressure->size(); i++)
	{
		if (t >= vapour_saturation_pressure->at(i).t)
		{
			t1 = vapour_saturation_pressure->at(i).t;
			p1 = vapour_saturation_pressure->at(i).p;
		}
		else if (t <= vapour_saturation_pressure->at(i).t)
		{
			t3 = vapour_saturation_pressure->at(i).t;
			p3 = vapour_saturation_pressure->at(i).p;
			break; // Выходим так как найдено следующее значение после искомого
		}
	}

	return (p1 + (((p3 - p1) * (t - t1)) / (t3 - t1)));
}

double  Water::SaturatedTemperature(double p)
{
	double t1 = 0, t3 = 0;
	double p1 = 0, p3 = 0;

	for (int i = 0;i < vapour_saturation_pressure->size(); i++)
	{
		if (p >= vapour_saturation_pressure->at(i).p)
		{
			t1 = vapour_saturation_pressure->at(i).t;
			p1 = vapour_saturation_pressure->at(i).p;
		}
		else if (p <= vapour_saturation_pressure->at(i).p)
		{
			t3 = vapour_saturation_pressure->at(i).t;
			p3 = vapour_saturation_pressure->at(i).p;
			break; // Выходим так как найдено следующее значение после искомого
		}
	}

	return (t1 + (((t3 - t1) * (p - p1)) / (p3 - p1)));
}

void  Water::clear()
{
	//delete water_heat_capacity;
}

int Water::HeatOfSublimation()
{
	return 2835;
}

double Water::HeatOfMelt()
{
	return 334.11;
}

int Water::IceHeatCapacity()
{
	return 2;
}