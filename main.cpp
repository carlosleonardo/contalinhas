#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

long int nLinhasTotais;
const string filtro = "filtro.ini";

list<string> listaExtensoes;

bool leFiltros()
{
    ifstream inp(filtro);
    
    if (!inp) {
        cout << "Não pude abrir arquivo " << filtro << endl;
        cout << "Se não existir, crie-o no diretório do programa e depois insira [extensoes] seguido pelas extensões de"
            "arquivo para filtra, uma por linha" << endl;
        return false;
    }

    string linha;
    getline(inp, linha);
        
    if (linha.find("extensoes")==string::npos) {
        cout << "Chave extensoes não encontrada" << endl;
        return false;
    }
    while(!inp.eof())
    {
        // Recupera uma extensão por linha
        getline(inp, linha);
        listaExtensoes.push_back(linha);
    }
    return true;
}

// Vê se o arquivo possui a extensão permitida
bool possuiExtensaoFiltrada(const fs::path& c)
{
    auto extensao = c.extension();
    for(auto& ext : listaExtensoes)
    {
        if ( extensao == ("." + ext)) {
            return true;
        }
    }

    return false;
}

void contalinhas(const fs::path& caminho)
{
    if ( !possuiExtensaoFiltrada(caminho) ) {
        return;
    }

    cout << "Contando linhas de " << caminho << endl;
    ifstream inp(caminho.c_str(), ios::in);
    long int nLinhas = 0;

    if (!inp) {
        cout << "Não foi possível abrir " << caminho << endl;
        return;
    }
    
    string linha;
    while(!inp.eof()) {
        getline(inp, linha);
        nLinhas++;
    }
    cout << "Linhas do arquivo: " << nLinhas << endl;
    nLinhasTotais += nLinhas;
}


void buscarDiretorio(const fs::path& caminho)
{
    cout << "Buscando diretório " << caminho << endl;
    fs::directory_iterator iter(caminho);
    for(auto& p : iter)
    {
        if (fs::is_regular_file(p)) {
            
            contalinhas(p);
        } else if (fs::is_directory(p))
        {
            buscarDiretorio(p);
        }
    }

}

int main(int argc, char** argv)
{
    
    if (argc==1) {
        cout << "Informe diretório inicial do código fonte\n";
        return -1;
    }
    
    if (leFiltros()) {
        if (fs::exists(argv[1])) {
            nLinhasTotais = 0;
            buscarDiretorio(argv[1]);
        }
        cout << "Total LOC: " << nLinhasTotais << endl;
    }
    
    return 0;
}