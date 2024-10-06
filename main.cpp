#include <iostream>
#include <fstream>
#include <string>

using namespace std;


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

//Funcion para regresar dos valores
pair<bool, int> algoritmoZ(string transmicion, string mcode) {
    
    string s = mcode + "$" + transmicion;
    int n = s.size();
    int z[n];
    z[0] = 0;
    int j = 1;
    bool continuar = true;
    for (int i = 1; i <= n; i++)
    {
        if(s[0] == s[i]){

            z[i] = 1;
            j = 1;
            while(continuar){
                if(s[0+j] == s[i+j]){
                    z[i]++;
                    j++;
                }else{
                    continuar = false;
                    if(z[i] == mcode.size()){
                        return make_pair(true, i);
                    }
                }
            }
            continuar = true;
        }   
    }
    return make_pair(false, 0);
}


int main(){

    string cadena1 = readFile("cadena1.txt");
    string cadena2 = readFile("cadena2.txt");
    string cadena3 = readFile("cadena3.txt");
    string patron1 = readFile("patron1.txt");
    string patron2 = readFile("patron2.txt");
    string patron3 = readFile("patron3.txt");


    cout << (algoritmoZ(cadena3, patron3).first ? "Si se encontro el patron en la cadena, en la posicion:" + to_string(algoritmoZ(cadena3, patron3).second) : "No se encontro el patron en la cadena\n");



    return 0;
}