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

void patternSearch(){
    
}

// Function that seeks the longest palindromic string and prints out the first position of the String and the length of this string
void longestPalindromicSubstring(std::string file){
    // We form our string with the special character in order to make it always an odd length stirng
    std::string t = "|";
    std::string sep = "|";

    for (int i = 0; i < file.size(); i++){
        t = t + file[i];
        t = t + sep;  
    }
    
    // We make N of the same size as t so we can make out L array as the same length as t (string with special character)
    // and we declare other variables for our for cycle
    int N = t.size();

    std::vector<int> L(N);

    L[0] = 0;
    L[1] = 1;

    int maxLong = 0;
    int maxCentro = 0;

    int C = 1;

    int Li = 0;


    // This for cycle makes de Ri go from the position 2 to de N-1 position in order to see all the positions
    for (int Ri = 2; Ri < N; Ri++){
        
        // We calculate Li and make expansion false so we can see each case that our string can land on and if its case 3, 4 or none, expansion turns true
        Li = C - (Ri - C);
        bool expansion = false;
        if ((C + L[C]) - Ri >= 0){
            // Case 1
            if (L[Li] < (C + L[C]) - Ri){
                L[Ri] = L[Li];

            // Case 2
            }else if((L[Li] == (C + L[C] - Ri)) && (C + L[C]) == N - 1){
                L[Ri] = L[Li];

            // Case 3
            }else if ((L[Li] == (C + L[C]) - Ri) && ((C + L[C]) < N - 1)){
                L[Ri] = L[Li];
                expansion = true;

            // Case 4
            }else if ((L[Li] > (C + L[C] - Ri) && (C + L[C]) < N - 1)){
                L[Ri] = (C + L[C]) - Ri;
                expansion = true;
            }
            
        }else{
            L[Ri] = 0;
            expansion = true;

        }

        // If it's possible to expand the palindromic string we enter on a while cycle, this while cycle verifies that we're still inside the string
        // and compares each character on the right and left from C in order to decide whether we can still expand or not
        if (expansion){
            
            while ((Ri + L[Ri] < N) && (Ri - L[Ri] > 0) && (t[Ri - L[Ri] - 1] == t[Ri + L[Ri] + 1])){
                L[Ri] = L[Ri] + 1;
            }

        }

        // If we surpass the C limit then that means we have encountered a new longest palindrome so we change C
        if (Ri > C + L[C]){
                
            C = Ri;
        }

        // If we surpass the length of the last longest palindromic stirng we had registered then we change the length of the longest palindrome
        if (L[Ri] > maxLong){
            maxLong = L[Ri];
            maxCentro = Ri;
        }
    }

    // We calculate the first position and take de length of the string
    int inicio = (maxCentro - maxLong) / 2;
    int m = maxLong;

    // Print out our results
    std::cout << "El codigo espejeado mas largo inicia en y termina en : " << std::endl;
    std::cout << inicio << " " << m << std::endl;
}

void longestCommonSubstring(){

}

int main(int argc, char const *argv[]){
    

    patternSearch();

    std::string file1 = readFileIntoString("transmission1.txt");
    std::string file2 = readFileIntoString("transmission2.txt");
    longestPalindromicSubstring(file1);
    longestPalindromicSubstring(file2);

    longestCommonSubstring();


    return 0;
}
