#pragma once
#include <vector>
#ifdef HUMIDAIR_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
/*
* LoadData функция загрузки данных 
*/
namespace Water
{
	const double WATER_M = 18.016;
	void LoadData();
	double VaporHeatCapacity(double t);
	double WaterHeatCapacity(double t);
	double HeatOfEvaporation(double t);
	int HeatOfSublimation();
	double HeatOfMelt();
	int IceHeatCapacity();
	double SaturatedPressure(double t);
	double SaturatedTemperature(double p);
	void clear();

	struct Data_t_c
	{
			double t;   // Температура 
			double cp;  // Теплоемкость

			Data_t_c(double t, double cp)
			{
				this->t = t;
				this->cp = cp;
			}
	};

	struct Data_t_r
	{
		double t;   // Температура 
		double r;  // теплота испарения

		Data_t_r(double t, double r)
		{
			this->t = t;
			this->r = r;
		}
	};

	struct Data_t_p
	{
		double t;   // Температура 
		double p;  // давление

		Data_t_p(double t, double p)
		{
			this->t = t;
			this->p = p;
		}
	};


}