#include "pch.h"
#include "humidair.h"
#include "Water.h"
#include "DryAir.h"
#include "tools.h"
#include <exception>
double HumidAir::HumidityRatio(double p, double t, double R)
{
    if (R < 0 || R > 1)
        throw std::exception();
    
    if (Water::SaturatedPressure(t) >= p && R != 1)
        return (Water::WATER_M / DryAir::DAIR_M) * ((R * p) / (p - R * p));

    return (Water::WATER_M / DryAir::DAIR_M) * ((R * Water::SaturatedPressure(t)) / (p - R * Water::SaturatedPressure(t)));
}

double HumidAir::Enthalpy(double p, double t, double d)
{
    t = t == 0 ? 0.02 : t;
    double h = 0;
    double dt = DewPointTemperature(p, d);
    if (RelativeHumidity(p, t, d) * (Water::SaturatedPressure(dt)) < Water::SaturatedPressure(dt))
    {
        
        if (dt >= 0.02)
        {
            h = DryAir::HeatCapacity(p, t) * t + d * (Water::WaterHeatCapacity(dt) * dt + Water::HeatOfEvaporation(dt) + Water::VaporHeatCapacity((0.5 * (t + dt))) * (t - dt));
        }
        else
        {
            h = DryAir::HeatCapacity(p, t) * t + d * (Water::IceHeatCapacity() * dt - Water::HeatOfMelt() + Water::HeatOfSublimation() + Water::VaporHeatCapacity((0.5 * (t + dt))) * (t - dt));
        }
    }
    else
    {
        if (t > 0.02)
        {
            h = DryAir::HeatCapacity(p, t) * t + d * (Water::IceHeatCapacity() * t + Water::HeatOfEvaporation(t));
        }
        else
        {
            
            h = DryAir::HeatCapacity(p, t) * t + d * (Water::WaterHeatCapacity(t) * t - Water::HeatOfMelt() + Water::HeatOfSublimation());
        }
    }
        return h;
}

double HumidAir::Entropy(double p, double t, double var, char type_var)
{
    double p_0 = 101325;
    double T_0 = 273.15;
    double s = 0;
    if (type_var == 'R')
    {
        s = DryAir::HeatCapacity(p, t) * log((C_to_K(t)) / T_0) - 0.287 * log(((p)-var * Water::SaturatedPressure(t)) / (p_0)) + HumidityRatio(p, t, var) * ((2500.64 / T_0)
            + Water::VaporHeatCapacity(t) * log((C_to_K(t)) / T_0) -
            0.4615 * log((var * Water::SaturatedPressure(t)) / 610));
    }
    else if (type_var == 'd')
    {
        s = DryAir::HeatCapacity(p, t) * log(C_to_K(t) / T_0) - 0.287 * log((p - RelativeHumidity(p, t, var) * Water::SaturatedPressure(t)) / p_0) + var * ((2500.64 / T_0) +
                    Water::VaporHeatCapacity(t) * log((C_to_K(t)) / T_0) -
                    0.4615 * log(RelativeHumidity(p, t, var) * Water::SaturatedPressure(t) / 610));
    }
        return s;
}

double HumidAir::Exergy(double p, double t, double d, double p_d, double t_d, double d_d)
{
    double e = C_to_K(t_d) * ((DryAir::HeatCapacity(p, t) + d * Water::VaporHeatCapacity(t)) * ((C_to_K(t) / (C_to_K(t_d))) - 1 - log(C_to_K(t) / C_to_K(t_d))) +
        0.4615 * ((0.622 + d) * log((p * (0.622 + d_d)) / (p_d * (0.622 + d))) + d * log(d / d_d)));
    return e;
}

double HumidAir::RelativeHumidity(double p, double t, double d)
{
   
    return (p * d) / (Water::SaturatedPressure(t) * ((Water::WATER_M / DryAir::DAIR_M) + d));
}

double HumidAir::DewPointTemperature(double p, double d)
{
    
    return Water::SaturatedTemperature((d * p) / 1 / ((Water::WATER_M / DryAir::DAIR_M) + d));
}

double HumidAir::VaporPartialPressure(double p, double d, double R)
{
    double pp = (d * p) / ((Water::WATER_M / DryAir::DAIR_M) + d);  
    return pp > p? p : pp;
}
