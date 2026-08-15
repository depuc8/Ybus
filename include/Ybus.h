#ifndef YBUS_H
#define YBUS_H

#include<vector>
#include<complex>
#include<string>
#include<fstream>

void print_ybus(const std::vector<std::vector<std::complex<double>>>&Ybus);

void write_ybus(const std::vector<std::vector<std::complex<double>>>& Ybus,
                const std::string& input_file);

void Ybus(std::ifstream& file, const std::string& input_file);

#endif
