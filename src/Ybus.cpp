#include<iostream>
#include<complex>
#include<vector>
#include<fstream>
#include<algorithm>
#include<climits>
#include<string>
#include<iomanip>
#include<filesystem>

struct Branch{
    int from;
    int to;
    double R;
    double X;
    double B;
    double tap;
};

void print_ybus(const std::vector<std::vector<std::complex<double>>>&Ybus){
    int m = Ybus.size();
    int n = Ybus[0].size();
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std::cout<<Ybus[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void write_ybus(const std::vector<std::vector<std::complex<double>>>& Ybus,
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
void Ybus(std::ifstream& file, const std::string& input_file){
    std::vector<Branch> branches;
    Branch branch;
    int nbus = INT_MIN;

    while(file >> branch.from >> branch.to >> branch.R >> branch.X >> branch.B >> branch.tap){
        branches.push_back(branch);
        nbus = std::max(nbus,branch.from);
        nbus = std::max(nbus,branch.to);
    }

    file.close();
    
    std::vector<std::vector<std::complex<double>>> Ybus(nbus,std::vector<std::complex<double>>(nbus, std::complex<double>(0.0,0.0)));

    for(const auto branch:branches){
        int i = branch.from - 1;
        int j = branch.to - 1;
        
        std::complex<double> z(branch.R,branch.X);
        std::complex<double> y = 1.0/z;
        std::complex<double> ysh(0.0,branch.B);
        double t = (branch.tap == 0.0) ? 1.0:branch.tap;
        
        std::complex<double> yii = (y + ysh)/(t*t);
        std::complex<double> yij = -y/t;
        std::complex<double> yji = -y/t;
        std::complex<double> yjj = (y+ysh);

        Ybus[i][i] += yii;
        Ybus[i][j] += yij;
        Ybus[j][i] += yji;
        Ybus[j][j] += yjj;
    }
    int choice;
    while(true){

        std::cout << "1. Print Ybus Matrix\n"
                 << "2. Write Ybus Matrix to file (recommended)\n"
                 << "3. Print and Write to file"
                 << "Enter your choice (1 or 2 or 3): ";
        if(std::cin >> choice &&(choice == 1 || choice == 2 || choice == 3)) break;
        std::cout<<"Invalid choice. Please enter 1 or 2 or 3.\n";
        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(choice == 1){
        print_ybus(Ybus);
        return;
    }
    else if(choice == 2){
        write_ybus(Ybus,input_file);
    }
    else if(choice == 3){
        print_ybus(Ybus);
        write_ybus(Ybus,input_file);
    }

}

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
