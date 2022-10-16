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

int findPattern(std::string pattern, std::string text){

    std::string concat = pattern + "$" + text;

    int n = concat.length();

    std::vector<int> z(n, 0);

    int l = 0;
    int r = 0;
    int k = 0;

    for(int i = 1; i < n; i++){
        if(i > r){
            l = i;
            r = i;

            while (r < n && concat[r - l] == concat[r]){
                r++;
            }

            z[i] = r - l;
            r--;
        }else{
            k = i - l;

            if(z[k] < r - i + 1){
                z[i] = z[k];
            }else{
                l = i;

                while (r < n && concat[r - l] == concat[r]){
                    r++;
                }

                z[i] = r - l;
                r--;
            }
        }

        if(z[i] == pattern.length()){
            return i - pattern.length() - 1;
        }
    }

    return -1;
}

void patternSearch(){

    std::vector<std::string> transmissions = {
        readFileIntoString("transmission1.txt"),
        readFileIntoString("transmission2.txt") 
    };

    std::vector<std::string> mcodes = {
        readFileIntoString("mcode1.txt"),
        readFileIntoString("mcode2.txt"),
        readFileIntoString("mcode3.txt")
    };

    int index;

    // Searches each mcode for each transmission file
    for(int i = 0; i < transmissions.size(); i++){
        for(int j = 0; j < mcodes.size(); j++){

            // gets the Index of the first match
            index = findPattern(mcodes[j],transmissions[i]);

            if(index < 0){
            // If there's no match it prints false
                std::cout<<"false"<<std::endl;
            }else{
            // If there's a match it prints true and the index of the first match
                std::cout<<"true "<<index<<std::endl;
            }
        }
    }

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
