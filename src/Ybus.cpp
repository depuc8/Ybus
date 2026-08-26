#include<iostream>
#include<complex>
#include<vector>
#include<fstream>
#include<algorithm>
#include<climits>
#include<string>
#include<iomanip>
#include<filesystem>

using ComplexDouble = std::complex<double>;
using ComplexVector = std::vector<ComplexDouble>;
using ComplexMatrix = std::vector<ComplexVector>;

struct Branch{
    int from;
    int to;
    double R;
    double X;
    double B;
    double tap;
};

void print_ybus(const ComplexMatrix &Ybus){
    std::cout << std::fixed << std::setprecision(4);
    for (const auto& row : Ybus) {
        for (const auto& val : row) {
            std::cout << std::setw(9) << val.real()
                      << (val.imag() >= 0 ? "+" : "")
                      << std::setw(7) << val.imag() << "j  ";
        }
        std::cout << '\n';
    }
}

void write_ybus(const ComplexMatrix& Ybus,
                const std::string& input_file) {
    namespace fs = std::filesystem;

    fs::path in_path(input_file);

    fs::path out_path = in_path.parent_path() /
                        ("ybus_" + in_path.stem().string() + ".txt");

    std::ofstream out(out_path);

    if (!out) {
        std::cerr << "Error creating output file.\n";
        return;
    }

    out << std::fixed << std::setprecision(4);

    for (const auto& row : Ybus) {
        for (const auto& val : row) {
            out << std::setw(10) << val.real()
                << (val.imag() >= 0 ? "+" : "")
                << std::setw(8) << val.imag() << "j  ";
        }
        out << '\n';
    }

    std::cout << "Ybus matrix written to: " << out_path << '\n';
}
ComplexMatrix Ybus(const std::string& input_file, int choice){
    if(choice < 0 || choice > 3){
        std::cerr<<"Error: Ybus choice must be 0,1,2,3";
        return {};
    }
    std::ifstream file(input_file);
    if(!file.is_open()){
        std::cerr<<"Error: Could not open file "<< input_file << '\n';
        return {};
    }
    std::vector<Branch> branches;
    Branch branch;
    int nbus = INT_MIN;

    while(file >> branch.from >> branch.to >> branch.R >> branch.X >> branch.B >> branch.tap){
        branches.push_back(branch);
        nbus = std::max(nbus,branch.from);
        nbus = std::max(nbus,branch.to);
    }

    if (file.fail() && !file.eof()) {
            std::cerr << "Error: Invalid data found in file. Expected numbers.\n";
            return {}; 
    }

    file.close();
    
    ComplexMatrix Ybus(nbus,ComplexVector(nbus, ComplexDouble(0.0,0.0)));

    for(const auto &branch:branches){
        int i = branch.from - 1;
        int j = branch.to - 1;
        
        ComplexDouble z(branch.R,branch.X);
        ComplexDouble y = 1.0/z;
        ComplexDouble ysh(0.0,branch.B);
        double t = (branch.tap == 0.0) ? 1.0:branch.tap;
        
        ComplexDouble yii = (y + ysh)/(t*t);
        ComplexDouble yij = -y/t;
        ComplexDouble yji = -y/t;
        ComplexDouble yjj = (y+ysh);

        if(i >= 0)           Ybus[i][i] += yii;
        if(i >= 0 && j >= 0) Ybus[i][j] += yij;
        if(i >= 0 && j >= 0) Ybus[j][i] += yji;
        if(j >= 0)           Ybus[j][j] += yjj;
    }
    if(choice == 1){
        print_ybus(Ybus);
    }
    else if(choice == 2){
        write_ybus(Ybus,input_file);
    }
    else if(choice == 3){
        print_ybus(Ybus);
        write_ybus(Ybus,input_file);
    }
    return Ybus;
}
