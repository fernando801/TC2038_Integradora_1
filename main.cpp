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

    // Se concatena el patrón a buscar con un símbolo y el texto en el que
    // se va a buscar, para que de esta manera el patrón sea un prefijo
    std::string concat = pattern + "$" + text;

    int n = concat.length();

    std::vector<int> z(n, 0);


    // Se utiliza el algoritmo de la función Z para buscar substrings 
    // que a la vez sean prefijos
    
    int l = 0; // Limite inferior del substring que también es prefijo que llega más a la derecha 
    int r = 0; // Limite superior del substring que también es prefijo que llega más a la derecha
    int k = 0; // Posición en el prefijo que corresponde a la posición actual

    // Se recorre cada caracter del string
    for(int i = 1; i < n; i++){

        if(i > r){
            // Si el caracter actual se encuentra fuera de l y r se reinician los valores
            // de l y r a la posición actual
            l = i;
            r = i;

            // Se compara caracter por caracter para encontrar los nuevos valroes de l y r
            while (r < n && concat[r - l] == concat[r]){
                r++;
            }

            // Se asigna el valor de Z[i] como la diferencia entre l y r
            z[i] = r - l;
            r--;
        }else{
            // Si i se encuentra entre l y r

            // k se asigna a la posición correspondiente en el prefijo
            k = i - l;

            if(z[k] < r - i + 1){
                // Si el valor de Z[k] es menor al número de caracteres entre i y r, Z[i] = Z[k]
                z[i] = z[k];
            }else{
                // Si no se reinician los valores de l y r y se evalua caracter por caracter
                l = i;

                while (r < n && concat[r - l] == concat[r]){
                    r++;
                }

                z[i] = r - l;
                r--;
            }
        }

        // Si la longitud del substring encontrado es igual a la del patrón quiere decir
        // que se encontró el patrón
        if(z[i] == pattern.length()){

            // Se devuelve la posición del patrón en el texto original
            return i - pattern.length() - 1;
        }
    }

    // Si no se encuentra el patrón se devuelve -1
    return -1;
}

void patternSearch(){

    // Almacena los archivos transmission en un vector como string
    std::vector<std::string> transmissions = {
        readFileIntoString("transmission1.txt"),
        readFileIntoString("transmission2.txt") 
    };

    // Almacena los archivos mcode en un vector como string
    std::vector<std::string> mcodes = {
        readFileIntoString("mcode1.txt"),
        readFileIntoString("mcode2.txt"),
        readFileIntoString("mcode3.txt")
    };

    int index;

    // Busca cada mcode en cada transmission
    for(int i = 0; i < transmissions.size(); i++){
        for(int j = 0; j < mcodes.size(); j++){

            // obtiene el indice del primer match
            index = findPattern(mcodes[j],transmissions[i]);

            if(index < 0){
            // Si no encuentra el patrón imprime false
                std::cout<<"false"<<std::endl;
            }else{
            // Si encuentra el patrón imprime true, seguido de la posición en 
            // la que se encuentra
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
