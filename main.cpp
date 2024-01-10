#include <iostream>
#include <cassert>
#include <string>
#include <cctype>           // Necesario para tolower
#include <algorithm>        // Necesario para transform
#include <vector>
#include <sstream>


using namespace std;

string obtenerFrase();
string obtenerModo();
string seleccionarConversor(string, string);
string codificar(string);
string decodificar(string);
vector<string> quitarEspacios(string);
wchar_t mapearACaracter(string);
void testCodificar();
void testDecodificar();


struct codigoTabla
{
    wchar_t letra;
    string codigo;
};

vector<codigoTabla> tabla{
    {L'a', "“#"}, {L'b', "%$"}, {L'c', "/("}, {L'd', ")="}, {L'e', "¿¡"},
    {L'f', "|!"}, {L'g', "}["}, {L'h', "{]"}, {L'i', "**"}, {L'j', "^`"}, 
    {L'k', "_.?"}, {L'l',"%_"}, {L'm', "$!”"}, {L'n', "¿?"}, {L'ñ', "¿?^"}, {L'o', "@"}, {L'p', "|@"},
    {L'q', "@|"}, {L'r', "=!"}, {L's', ";*"}, {L't', "¡_"}, {L'u', "^)"},
    {L'v', "(/"}, {L'w', "((//"}, {L'x', "||"}, {L'y', "|(/"}, {L'z', "_/_" },

    {L'0', "="}, {L'1', "¡"}, {L'2', "“"}, {L'3', "#"}, {L'4', "$"},
    {L'5', "%"}, {L'6', "^"}, {L'7', "/"}, {L'8', "("}, {L'9', ")"}, 
    {L' ', "&_&"}
};

int main()
{       
    {
    //PRUEBAS
    testCodificar();
    testDecodificar(); //TONY
    }
    
   
   {
    //PROGRAMA
    string frase = obtenerFrase();
    string modo = obtenerModo();
    cout << seleccionarConversor(frase, modo) << endl;
   }
}

string obtenerFrase()
{
    cout << "Ingrese una frase" << endl;
    string frase;
    getline(cin, frase);
    return frase;
}

string obtenerModo()
{
    cout << "¿Desea codificarla o decodificarla? (codificar/decodificar)" << endl;
    string modo;
    getline(cin, modo);
    transform(modo.begin(), modo.end(), modo.begin(), ::tolower);
    if (modo != "codificar" && modo != "decodificar")
    {
        cout << "Ingrese una opcion valida" << endl;
        obtenerModo();
    }
    return modo;
}

string seleccionarConversor(string frase, string modo){
    return (modo == "decodificar") ? decodificar(frase): codificar(frase);
    
}

string codificar(string frase){
    string fraseCodificada;
    transform(frase.begin(), frase.end(), frase.begin(), ::tolower);
    for(const auto& letra : frase)
    {
        
       for(const auto& encriptacion : tabla)
       {        
              if(letra == encriptacion.letra)
              {
                fraseCodificada += encriptacion.codigo + " ";
              }
       }
    }

    return fraseCodificada.substr(0, fraseCodificada.size() - 1);
}



string decodificar(string frase) {
    vector<string> codigos = quitarEspacios(frase);
    string fraseDecodificada;

    for (const auto &codigo : codigos) {
        wchar_t letra = mapearACaracter(codigo);
        fraseDecodificada += letra;
    }

    return fraseDecodificada;
}

vector<string> quitarEspacios(string frase){
    string codigo;
    stringstream flujo(frase);

    vector<string> codigos;

    while (getline(flujo, codigo, ' ')) {
        codigos.push_back(codigo);
    }

    return codigos;
}

wchar_t mapearACaracter(string codigo) {
    for (const auto &encriptacion : tabla) {
        if (codigo == encriptacion.codigo) {
            return encriptacion.letra;
        }
    }
}

void testDecodificar(){
        assert(decodificar("{] @ %_ “#") == "hola");
        assert(decodificar("{] @ %_ “# &_& ¿? ** /( @") == "hola nico");
        assert(decodificar("¿¡ ;* &_& ^) ¿? &_& %$ ^) ¿¡ ¿? &_& )= ** “#") == "es un buen dia");
        assert(decodificar("/( |@ |@ &_& ¿¡ ;* &_& “# ;* |@ ¿¡ =! @") == "cpp es aspero");
        assert(decodificar("¿¡ %_ &_& $!” ^) ¿? )= @ &_& ¿¡ ¿? ¡_ ¿¡ =! @") == "el mundo entero");
        assert(decodificar("%$ “# ¿? |! ** ¿¡ %_ )= &_& “ = = )") == "banfield 2009");
        
        

        assert(decodificar("“#") == "a");
        assert(decodificar("%$") == "b");
        assert(decodificar("/(") == "c");
        assert(decodificar(")=") == "d");
        assert(decodificar("¿¡") == "e");
        assert(decodificar("|!") == "f");
        assert(decodificar("}[") == "g");
        assert(decodificar("{]") == "h");
        assert(decodificar("**") == "i");
        assert(decodificar("^`") == "j");
        assert(decodificar("_.?") == "k");
        assert(decodificar("%_") == "l");
        assert(decodificar("$!”") == "m");
        assert(decodificar("¿?") == "n");
        //assert(decodificar("¿?^") == "ñ");
        assert(decodificar("@") == "o");
        assert(decodificar("|@") == "p");
        assert(decodificar("@|") == "q");
        assert(decodificar("=!") == "r");
        assert(decodificar(";*") == "s");
        assert(decodificar("¡_") == "t");
        assert(decodificar("^)") == "u");

        assert(decodificar("=") == "0");
        assert(decodificar("¡") == "1");
        assert(decodificar("“") == "2");
        assert(decodificar("#") == "3");
        assert(decodificar("$") == "4");
        assert(decodificar("%") == "5");
        assert(decodificar("^") == "6");
        assert(decodificar("/") == "7");
        assert(decodificar("(") == "8");
        assert(decodificar(")") == "9");

        assert(decodificar("&_&") == " ");
}

void testCodificar(){
        assert(codificar("hola") == "{] @ %_ “#");
        assert(codificar("hol ni") == "{] @ %_ &_& ¿? **");
        assert(codificar("hola nico") == "{] @ %_ “# &_& ¿? ** /( @");
        assert(codificar("esta nublado") == "¿¡ ;* ¡_ “# &_& ¿? ^) %$ %_ “# )= @");
        assert(codificar("Esta Nublado") == "¿¡ ;* ¡_ “# &_& ¿? ^) %$ %_ “# )= @");

        assert(codificar("A") == "“#");
        assert(codificar("B") == "%$");
        assert(codificar("C") == "/(");
        assert(codificar("D") == ")=");
        assert(codificar("E") == "¿¡");
        assert(codificar("F") == "|!");
        assert(codificar("G") == "}[");
        assert(codificar("H") == "{]");

        assert(codificar("a") == "“#");
        assert(codificar("b") == "%$");
        assert(codificar("c") == "/(");
        assert(codificar("d") == ")=");
        assert(codificar("e") == "¿¡");
        assert(codificar("f") == "|!");
        assert(codificar("g") == "}[");
        assert(codificar("h") == "{]");
        assert(codificar("i") == "**");
        assert(codificar("j") == "^`");
        assert(codificar("k") == "_.?");
        assert(codificar("l") == "%_");
        assert(codificar("m") == "$!”");
        assert(codificar("n") == "¿?");
      //assert(codificar("ñ") == "¿?^");
        assert(codificar("o") == "@");
        assert(codificar("p") == "|@");
        assert(codificar("q") == "@|");
        assert(codificar("r") == "=!");
        assert(codificar("s") == ";*");
        assert(codificar("t") == "¡_");
        assert(codificar("u") == "^)");
        assert(codificar("v") == "(/");
        assert(codificar("w") == "((//");
        assert(codificar("x") == "||");
        assert(codificar("y") == "|(/");
        assert(codificar("z") == "_/_");


        assert(codificar("0") == "=");
        assert(codificar("1") == "¡");
        assert(codificar("2") == "“");
        assert(codificar("3") == "#");
        assert(codificar("4") == "$");
        assert(codificar("5") == "%");
        assert(codificar("6") == "^");
        assert(codificar("7") == "/");
        assert(codificar("8") == "(");
        assert(codificar("9") == ")");

        assert(codificar(" ") == "&_&");
}
 