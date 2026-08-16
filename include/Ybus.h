#ifndef YBUS_H
#define YBUS_H
#include<vector>
#include<complex>
#include<string>
#include<fstream>

using ComplexMatrix = std::vector<std::vector<std::complex<double>>>;

void print_ybus(const ComplexMatrix &Ybus);

void write_ybus(const ComplexMatrix& Ybus,
                const std::string& input_file);

ComplexMatrix Ybus(const std::string& input_file,int choice);

#endif
