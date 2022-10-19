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
    //Crea los strings trans 1 y 2, leyendo los .txt de transmission con la función readFileIntoString
    std::string trans1 = readFileIntoString("transmission1.txt");
    std::string trans2 = readFileIntoString("transmission2.txt");
    //Crea las variables n y m conteniendo las longitudes de los previos strings
    int n = trans1.length();
    int m = trans2.length();
    //Inicializa la matriz LCS como un vector de vectores de n x m, inicado todo en ceros
    std::vector<std::vector<int>> LCS(n, std::vector<int>(m,0));
    //Inicializa en 0 las variables
    int max=0;        //contiene el tamaño del maximo común substring actual
    int finalPos=0;   //contiene la posición final en el archivo 1 del máxino común substring encontrado
    int firstPos=0;   //contiene la posición inicial en el archivo 1 del máximo común substring encontrado

    //recorre el string trans1 y si en algun punto coincide con la posición incial de trans2 añade un 1 a la matriz en [i][0] y asigna max=1
    //De no coincidir, añade 0 a la misma posición
    for (int i=0; i<trans1.length(); i++){
        if (trans1[i]==trans2[0]){
            LCS[i][0]=1;
            max=1;
        }
        else{
            LCS[i][0]=0;
        }
    }

    //recorre el string trans2 y si en algun punto coincide con la posición incial de trans1 añade un 1 a la matriz en [0][j] y asigna max=1
    //De no coincidir, añade 0 a la misma posición
    for (int j=0; j<trans2.length(); j++){
        if (trans2[j]==trans1[0]){
            LCS[0][j]=1;
            max=1;
        }
        else{
            LCS[0][j]=0;
        }
    }

    //compara las siguientes posiciones entre ambos strings con el doble ciclo
    for (int i=1; i<trans1.length(); i++){
        for (int j=1; j<trans2.length(); j++){
            //Si trans1[i] coincide con trans2[j], suma al valor de coincidencia anterior un 1 y lo añade a la matriz
            //de modo que si hay coincidencias previas, el tamaño de coincidencia aumenta
            if (trans1[i]==trans2[j]){
                LCS[i][j]=LCS[i-1][j-1]+1;
                if(LCS[i][j]>max) {  //si el valor actual de coincidencia es mayor al máximo actual
                    max=LCS[i][j];   //asigna el valor de coincidencia actual al máximo actual, reemplazando el anterior
                    finalPos=i+1;    //asigna como posición final la posición actual en trans1+1, para que tome las posiciones a partir de 1
                    firstPos=finalPos-max+1;  //calcula la posición inicial del máximo encontrado restando la posición final el tamaño del máximo y sumando 1
                }
            }
            else{
                LCS[i][j]=0;  //si no hubo coincidencia, añade 0 a la matriz
            }
        }
    }
    std::cout<<firstPos<<" "<<finalPos<<std::endl; //Imprime la posición inicial y final empezando por 1
}

int main(int argc, char const *argv[]){

    patternSearch();


    longestPalindromicSubstring();


    longestCommonSubstring();


    return 0;
}
