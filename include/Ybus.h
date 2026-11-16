#ifndef YBUS_H
#define YBUS_H

#include<vector>
#include<complex>
#include<string>

using ComplexMatrix = std::vector<std::vector<std::complex<double>>>;
using Matrix = std::vector<std::vector<double>>;

void print_ybus(const ComplexMatrix &Ybus);

void write_ybus(const ComplexMatrix& Ybus,
                const std::string& input_file);

ComplexMatrix Ybus(const std::string& input_file,int choice);

Matrix Bbus(const ComplexMatrix& Ybus);

Matrix Gbus(const ComplexMatrix& Ybus);

#endif
