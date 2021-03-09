#pragma once
#include <string>
#include <vector>

void split(std::string line = std::string(), double* data = nullptr);
//template <typename T>
//void write_data(std::vector<T>* vec, std::string& filename);
double C_to_K(double t);
double K_to_C(double T);
