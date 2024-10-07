string readFile(string filename) {
    ifstream archivo(filename);
    if(!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    string contenido((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    archivo.close();
    return contenido;
}

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

    return make_pair(false, 0);
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

    return make_pair((posicionCentrada - maximo) / 2 + 1, (posicionCentrada + maximo) / 2);
}

/*
* Función: lcs()
* Descripción: Encuentra la subcadena más larga común entre dos cadenas
* Parámetros: string, cadena de texto a
*    string, cadena de texto b
* Regresa: pair<int, int>, posición inicial y final de la subcadena
*/
pair<int, int> lcs(string a, string b) {
    int n = a.size();
    int m = b.size();

    vector<vector<int>> M(n + 1, vector<int>(m + 1, 0));

    int maximo = 0;
    int posicion = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            if (a[i - 1] == b[j - 1]) {

                M[i][j] = 1 + M[i - 1][j - 1];
                if (M[i][j] > maximo) {
                    maximo = M[i][j];
                    posicion = i;
                }
            } else {
                M[i][j] = 0;
            }
        }
    }
    return make_pair(posicion - maximo, posicion);
}
    


int main(){
    // Lectura de archivos
    string mcode01 = readFile("mcode01.txt");
    string mcode02 = readFile("mcode02.txt");
    string mcode03 = readFile("mcode03.txt");
    string transmission01 = readFile("transmission01.txt");
    string transmission02 = readFile("transmission02.txt");

    // Pruebas para Parte 1
    auto p1_result1 = algoritmoZ(transmission01, mcode01);
    auto p1_result2 = algoritmoZ(transmission01, mcode02);
    auto p1_result3 = algoritmoZ(transmission01, mcode03);
    auto p1_result4 = algoritmoZ(transmission02, mcode01);
    auto p1_result5 = algoritmoZ(transmission02, mcode02);
    auto p1_result6 = algoritmoZ(transmission02, mcode03);

    cout << "PARTE 1: \n \n";

    if (p1_result1.first == true) {
        cout << "true " << to_string(p1_result1.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (p1_result2.first == true) {
        cout << "true " << to_string(p1_result2.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (p1_result3.first == true) {
        cout << "true " << to_string(p1_result3.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (p1_result4.first == true) {
        cout << "true " << to_string(p1_result4.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (p1_result5.first == true) {
        cout << "true " << to_string(p1_result5.second) << endl;
    } else {
        cout << "false" << endl;
    }

    if (p1_result6.first == true) {
        cout << "true " << to_string(p1_result6.second) << endl;
    } else {
        cout << "false" << endl;
    }


    // Pruebas para Parte 2
    pair<int, int> p2_result1 = Manacher(transmission01);
    pair<int, int> p2_result2 = Manacher(transmission02);

    cout << "\nPARTE 2: \n \n";

    cout << "Transmission01: " << endl << to_string(p2_result1.first) << " " << to_string(p2_result1.second) << endl << endl;
    cout << "Transimssion02: " << endl << to_string(p2_result2.first) << " " << to_string(p2_result2.second) << endl << endl;


    // Pruebas para Parte 3
    pair<int, int> p3_result1 = lcs(transmission01, transmission02);
    cout << "PARTE 3: \n \n";

    cout << "LCS: " << to_string(p3_result1.first) << " " << to_string(p3_result1.second) << endl;
