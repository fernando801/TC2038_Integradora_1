// Situación problema I
// El siguiente código da solución de la situación problema acerca de la identificación de strings o patrones en archivos de texto,
// realiza diferentes actividades con los cinco archivos de texto mcode1.txt, mcode2.txt, mcode3.txt, transmission1.txt y transmission2.txt
// 
// Última modicación: 19 de octubre de 2022
//
// Autores:
//              Jorge Omar López Gemignini      A01769675
//              Fernando Reséndiz Bautista      A01769659
//              Carlos Eduardo Jiménez          A01769960

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

// Función que busca el palíndromo
void longestPalindromicSubstring(std::string file){
    // Formamos nuestro string con el caracter espcial | en medio de cada caracter, al inicio y al final del string
    std::string t = "|";
    std::string sep = "|";

    for (int i = 0; i < file.size(); i++){
        t = t + file[i];
        t = t + sep;  
    }
    
    // Hacemos N del tamaño de t para poder hacer nuestro arreglo L del mismo tamaño y no tener problemas en el recorrido, declaramos variables futuramente usadas
    int N = t.size();

    std::vector<int> L(N);

    L[0] = 0;
    L[1] = 1;

    int maxLong = 0;
    int maxCentro = 0;

    int C = 1;

    int Li = 0;


    // El ciclo for recorre todas las posiciones dentro del string
    for (int Ri = 2; Ri < N; Ri++){
        
        // Calculamos Li y empezamos a comparar para ver en que caso termina nuestro string, dependiendo del caso expand se volverá true o se quedará en false
        Li = C - (Ri - C);
        bool expansion = false;
        if ((C + L[C]) - Ri >= 0){
            // Caso 1
            if (L[Li] < (C + L[C]) - Ri){
                L[Ri] = L[Li];

            // Caso 2
            }else if((L[Li] == (C + L[C] - Ri)) && (C + L[C]) == N - 1){
                L[Ri] = L[Li];

            // Caso 3
            }else if ((L[Li] == (C + L[C]) - Ri) && ((C + L[C]) < N - 1)){
                L[Ri] = L[Li];
                expansion = true;

            // Caso 4
            }else if ((L[Li] > (C + L[C] - Ri) && (C + L[C]) < N - 1)){
                L[Ri] = (C + L[C]) - Ri;
                expansion = true;
            }
            
        }else{
            L[Ri] = 0;
            expansion = true;

        }

        // Si podemos expandir entonces entramos el ciclo while el cuál es el encargado de ir comparando caracter por caracter en la izquierda y derecha, si coindicen
        // entonces le aumenta 1 a valor en la posición Ri en el arrelgo de L
        if (expansion){
            
            while ((Ri + L[Ri] < N) && (Ri - L[Ri] > 0) && (t[Ri - L[Ri] - 1] == t[Ri + L[Ri] + 1])){
                L[Ri] = L[Ri] + 1;
            }

        }

        // Si superamos el límite de C entonces le damos el nuevo valor a C
        if (Ri > C + L[C]){
                
            C = Ri;
        }

        // Si superamos la longitud del palíndromo que calculamos anteriormente entonces cambiamos nuestro palíndromo más largo por el nuevo encontrado
        if (L[Ri] > maxLong){
            maxLong = L[Ri];
            maxCentro = Ri;
        }
    }

    // Calculamos la primera posición y asignamos la longitud
    int inicio = (maxCentro - maxLong) / 2;
    int m = maxLong;

    // Imprimimos los resutlados
    std::cout << inicio + 1 << " " << m << std::endl;
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

    std::string file1 = readFileIntoString("transmission1.txt");
    std::string file2 = readFileIntoString("transmission2.txt");
    longestPalindromicSubstring(file1);
    longestPalindromicSubstring(file2);

    longestCommonSubstring();


    return 0;
}
