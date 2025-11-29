
/* #include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("input.txt");
    std::string line;
    
    while (std::getline(input, line)) {
        std::cout << line << std::endl;
    }
    
    return 0;
} */



/* #include <fstream>
#include <string>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string line;
    
    while (std::getline(input, line)) {
        output << line << std::endl;
    }
    
    return 0;
} */



#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    std::string line;

    int N, M;
    input >> N >> M;
    
    while (std::getline(input, line)) {

        std::string item;
        std::stringstream stream(line);
        
        for (int j = 0; j < M; j++) {
            if (j < M - 1) {
                std::getline(stream, item, ',');
            } else {
                std::getline(stream, item);
            }
            
            std::cout << std::setw(10) << item;
            if (j < M - 1) {
                std::cout << " ";
            }
            
        }
        std::cout << std::endl;
    }


    
    return 0;
}