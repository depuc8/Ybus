#include<iostream>
#include<string>
#include "../include/Ybus.h"

using ComplexMatrix = std::vector<std::vector<std::complex<double>>>;

int main(){

    std::cout<<"Enter file path for line data: ";
    std::string file_path;
    std::cin >> file_path; 

    ComplexMatrix ybus_0 = Ybus(file_path,0);
    std::cout<<"returns Ybus and Outputs nothing"<<std::endl;
    std::cout<<"\n";
    ComplexMatrix ybus_1 = Ybus(file_path,1);
    std::cout<<"\n";
    std::cout<<"\nreturns Ybus and prints Ybus in the terminal"<<std::endl;

    std::cout<<"\n";

    ComplexMatrix ybus_2 = Ybus(file_path,2);

    std::cout<<"\n";
    std::cout<<"\nreturns Ybus and writes Ybus to a file in the file_path"<<std::endl;

    std::cout<<"\n";
    ComplexMatrix ybus_3 = Ybus(file_path,3);

    std::cout<<"\n";
    std::cout<<"\ndoes all of the above"<<std::endl;

    std::cout<<"\n";

    std::cout<<ybus_0[0][0]<<std::endl;
    std::cout<<ybus_1[0][0]<<std::endl;
    std::cout<<ybus_2[0][0]<<std::endl;
    std::cout<<ybus_3[0][0]<<std::endl;

    std::cout<<"\nall the options return Ybus"<<std::endl;

    return 0;
}

