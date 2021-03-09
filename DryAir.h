#pragma once
/*
* HeatCapacity функция результатом которой
* есть изобарная теплоемкость воздуха
* t - температура в С
* p - давление в Па
*/
namespace DryAir
{
const double DAIR_M = 28.96;
double HeatCapacity(double p, double t);
void LoadData();
/*
* Data - структура для хранения данных 
*/
struct Data
{
public:
    double p;
    double t;
    double cp;
    Data(double p, double t, double cp)
    {
        this->p = p;
        this->t = t;
        this->cp = cp;
    }
};
}