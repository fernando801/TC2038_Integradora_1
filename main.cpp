#include <iostream>
#include <fstream>

std::string readFileIntoString(const std::string path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void patternSearch(){
    
}

void longestPalindromicSubstring(){

}

void longestCommonSubstring(){

}

int main(int argc, char const *argv[]){

    patternSearch();


    longestPalindromicSubstring();


    longestCommonSubstring();


    return 0;
}
