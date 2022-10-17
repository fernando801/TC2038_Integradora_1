#include <iostream>
#include <fstream>
#include <vector>

//Takes a file path as an argument and returns its contents as a string
std::string readFileIntoString(const std::string path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

// void patternSearch(){
    
// }

int longestPalindromicSubstring(){
    std::string file1 = readFileIntoString("transmission1.txt");
    std::string file2 = readFileIntoString("transmission2.txt");
    std::string t = "|";
    std::string sep = "|";

    for (int i = 0; i < file1.size(); i++){
        t = t + file1[i];
        t = t + sep;  
    }
    
    int N = t.size();

    std::vector<int> L(N);

    L[0] = 0;
    L[1] = 1;

    int maxLong = 0;
    int maxCentro = 0;

    int C = 1;

    int Ri = 0;
    int Li = 0;

    for (Ri = 2; Ri < N-1; Ri++){
        Li = C - (Ri - C);
        bool expansion = false;
        if ((C + L[C]) - Ri >= 0){
            if (L[Li] < (C + L[C]) - Ri){
                L[Ri] = L[Li];

            }else if((L[Li] = (C + L[C] - Ri)) && (C + L[C]) == N - 1){
                L[Ri] = L[Li];

            }else if ((L[Li] = (C + L[C]) - Ri) && ((C + L[C]) < N - 1)){
                L[Ri] = L[Li];
                expansion = true;

            }else if ((L[Li] > (C + L[C] - Ri) && (C + L[C]) < N - 1)){
                L[Ri] = (C + L[C]) - Ri;
                expansion = true;
            
            }else{
                L[Ri] = 0;
                expansion = true;

            }
            if (expansion){
                while (Ri + L[Ri] < N && Ri - L[Ri] > 0 && t[Ri - L[Ri] - 1] == t[Ri + L[Ri] + 1]){
                    L[Ri] = L[Ri] + 1;
                }
            }
            if (Ri > C + L[C]){
                C = Ri;
            }
            if (L[Ri] > maxLong){
                maxLong = L[Ri];
                maxCentro = Ri;
            }
        }
    }

    int inicio = (maxCentro - maxLong) / 2;
    int m = maxLong;

    std::cout << inicio << std::endl;
    std::cout << m << std::endl;

    return inicio, m;
}

// void longestCommonSubstring(){

// }

int main(int argc, char const *argv[]){

    // patternSearch();


    std::cout << longestPalindromicSubstring();


    // longestCommonSubstring();


    return 0;
}
