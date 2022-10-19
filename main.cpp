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

void longestPalindromicSubstring(){

}

void longestCommonSubstring(){
    std::string trans1 = readFileIntoString("transmission1.txt");
    std::string trans2 = readFileIntoString("transmission2.txt");
    int n = trans1.length();
    int m = trans2.length();
    std::vector<std::vector<int>> LCS(n, std::vector<int>(m,0));
    int max=0;
    int finalPos=0;
    int firstPos=0;

    for (int i=0; i<trans1.length(); i++){
        if (trans1[i]==trans2[0]){
            LCS[i][0]=1;
            max=1;
        }
        else{
            LCS[i][0]=0;
        }
    }

    for (int j=0; j<trans2.length(); j++){
        if (trans2[j]==trans1[0]){
            LCS[0][j]=1;
            max=1;
        }
        else{
            LCS[0][j]=0;
        }
    }

    for (int i=1; i<trans1.length(); i++){
        for (int j=1; j<trans2.length(); j++){
            if (trans1[i]==trans2[j]){
                LCS[i][j]=LCS[i-1][j-1]+1;
                if(LCS[i][j]>max) {
                    max=LCS[i][j];
                    finalPos=i+1;
                    firstPos=finalPos-max+1;
                }
            }
            else{
                LCS[i][j]=0;
            }
        }
    }
    std::cout<<firstPos<<" "<<finalPos<<std::endl;
}

int main(int argc, char const *argv[]){

    patternSearch();


    longestPalindromicSubstring();


    longestCommonSubstring();


    return 0;
}
