#pragma once

namespace HumidAir
{
extern "C" __declspec(dllexport) double HumidityRatio(double p, double t, double R);
extern "C" __declspec(dllexport) double Enthalpy(double p, double t, double d);
extern "C" __declspec(dllexport) double Entropy(double p, double t, double var, char type_var);
extern "C" __declspec(dllexport) double Exergy(double p, double t, double d, double p_d, double t_d, double d_d);
extern "C" __declspec(dllexport) double RelativeHumidity(double p, double t, double d);
extern "C" __declspec(dllexport) double DewPointTemperature(double p, double d);
extern "C" __declspec(dllexport) double VaporPartialPressure(double p, double d, double R);
}

