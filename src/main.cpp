#include<iostream>
#include<fstream>
#include "../include/Ybus.h"

int main(){

    std::cout<<"Enter file path for line data: ";
    std::string file_path;
    std::cin >> file_path; 

    std::ifstream file(file_path);

    
    if(!file.is_open()){
        std::cerr<<"Error: could not find the file\n";
        return 1;
    }
    Ybus(file,file_path);
}

