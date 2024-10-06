/*
* Autores: 
*   Andrea Medina, 
*   Diego Lira
*   Imanol Muñiz
* Fecha: 05.10.2024
* Descripción: Programa que recibe distintas transmisiones de texto y busca patrones maliciosos
*     dentro de ellas.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
* Función: readFile()
* Descripción: Lee un archivo y regresa su contenido
* Parámetro: string, nombre del archivo a leer
* Regresa: string, contenido del archivo
*/
string readFile(string filename) {
    ifstream archivo(filename);
    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();
    return contenido;
};

/*
* Función: matrizZ()
* Descripción: Crea la matriz Z para el algoritmo de Z
* Parámetros: int, tamaño de la cadena
*    string, cadena de texto concatenada
* Regresa: vector<int>, matriz Z
*/
vector<int> matrizZ(int n, string s) {
    vector<int> z(n, 0);

    // Límites de ventana de coincidencia
    int left = 0;
    int right = 0; 
    int k;

    for (int i = 1; i < n; i++) {
        // Si no ha habido coincidencia
        if (i > right) {
            left = right = i;   // Ambos límites avanzan hacia posición actual

            while (right < n && s[right - left] == s[right]) {
                // La ventana de coincidencia se extiende a la derecha
                right++;    
            }
            z[i] = right - left;
            // Establece la ventana de coincidencia 
                // Si no hay, left y right serán iguales
            right--;

        } else {
            k = i - left;  // Número de coincidencias que lleva
            if (z[k] < right - i + 1) {
                // Copia el valor que ya se conocía
                z[i] = z[k];

            // Termina el arreglo    
            } else {
                left = i;
                while (right < n && s[right - left] == s[right]) {
                    right++;
                }
                z[i] = right - left;
                right--;
            }
        }
    }

    return z;
}

/*
* Función: AlgoritmoZ() 
* Descripción: Para encontrar si un patrón existe en una cadena y en qué posición
* Parámetros: string, cadena de texto de transmision
*    string, patron a buscar
* Regresa: pair<bool, int>, si el patrón existe y en qué posición
*/
pair<bool, int> algoritmoZ(string transmision, string mcode) {
    
    string s = mcode + "$" + transmision;
    int n = s.size();

    vector<int> z = matrizZ(n, s);

    for (int i = 0; i < n; i++) {
        if (z[i] == mcode.size()) {
            return make_pair(true, i);
        }
    }
}

/*
* Función AgregarGato()
* Descripción: Agrega un caracter especial a la cadena
* Parámetros: string, cadena de texto
* Regresa: string, cadena de texto con caracter especial
*/

string AgregarGato(string s) {
    string nueva = "#";
    for (int i = 0; i < s.size(); i++) {
        nueva += s[i];
        nueva += "#";
    }
    return nueva;
}


/*
 * Función Manacher()
 * Descripción: Encuentra el palíndromo más largo en una cadena
 * Parámetros: string, cadena de texto
 * Regresa: int, posición inicial del palíndromo
 *          int, posición final del palíndromo
 */

pair<int, int> Manacher(string s) {
    string t = AgregarGato(s);
    int n = t.size();
    vector<int> arregloP(n, 0);
    int centro, bordeDerecho, prima = 0;
    int maximo = 1;
    int posicionCentrada = 1; 

    for(int i = 1; i < n - 1; i++) {

        if(i < bordeDerecho) {
            prima = 2 * centro - i;
            arregloP[i] = min(bordeDerecho - i, arregloP[prima]);
        }

        while(i + arregloP[i] + 1 < n && i - arregloP[i] - 1 >= 0 && 
              t[i + arregloP[i] + 1] == t[i - arregloP[i] - 1]) {

            arregloP[i]++;

        }

        if(arregloP[i] > maximo) {
            maximo = arregloP[i];
            posicionCentrada = i;
        }

        if(i + arregloP[i] > bordeDerecho) {
            centro = i;
            bordeDerecho = i + arregloP[i];
        }

    }

    return make_pair((posicionCentrada - maximo) / 2, (posicionCentrada + maximo) / 2);
}
    


int main(){

    string cadena1 = readFile("cadena1.txt");
    string cadena2 = readFile("cadena2.txt");
    string cadena3 = readFile("cadena3.txt");
    string patron1 = readFile("patron1.txt");
    string patron2 = readFile("patron2.txt");
    string patron3 = readFile("patron3.txt");

    auto result1 = algoritmoZ(cadena1, patron1);
    auto result2 = algoritmoZ(cadena2, patron2);
    auto result3 = algoritmoZ(cadena3, patron3);

    if (result1.first == true) {
        cout << "true " << to_string(result1.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (result2.first == true) {
        cout << "true " << to_string(result2.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (result3.first == true) {
        cout << "true " << to_string(result3.second) << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}