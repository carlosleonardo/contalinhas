#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include <filesystem>
#include <chrono>

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;
namespace fs = std::filesystem;

long int nLinhasTotais;
const string filtro = "filtro.ini";

long int nTotalArquivos;
long int nTotalDiretorios;

list<string> listaExtensoes;

bool leFiltros()
{
    ifstream inp(filtro);

    if (!inp)
    {
        cout << "Não pude abrir arquivo " << filtro << endl;
        cout << "Se não existir, crie-o no diretório atual e depois insira [extensoes] seguido "
                "por extensões de arquivo para filtrar, uma por linha."
             << endl;
        return false;
    }

    string linha;
    getline(inp, linha);

    if (linha.find("extensoes") == string::npos)
    {
        cout << "Chave extensoes não encontrada" << endl;
        return false;
    }
    while (!inp.eof())
    {
        // Recupera uma extensão por linha
        getline(inp, linha);
        listaExtensoes.push_back(linha);
    }
    return true;
}

// Vê se o arquivo possui a extensão permitida
bool possuiExtensaoFiltrada(const fs::path &c)
{
    const auto extensao = c.extension();
    for (const auto &ext : listaExtensoes)
    {
        if (extensao == ("." + ext))
        {
            return true;
        }
    }

    return false;
}

void contalinhas(const fs::path &caminho)
{
    if (!possuiExtensaoFiltrada(caminho))
    {
        return;
    }

    cout << "Contando linhas de " << caminho << endl;
    ifstream inp(caminho.c_str(), ios::in);
    long int nLinhas = 0;

    if (!inp)
    {
        cout << "Não foi possível abrir " << caminho << endl;
        return;
    }

    string linha;
    while (!inp.eof())
    {
        getline(inp, linha);
        nLinhas++;
    }
    cout << "Linhas do arquivo: " << nLinhas << endl;
    nTotalArquivos++;
    nLinhasTotais += nLinhas;
}

void buscarDiretorioIterativo(const fs::path &caminhoBase)
{
    cout << "Buscando diretório " << caminhoBase << endl;
    stack<fs::path> pastas;

    pastas.push(caminhoBase);

    while (!pastas.empty())
    {
        fs::path caminhoAtual = pastas.top();
        pastas.pop();

        try
        {
            fs::directory_iterator iter(caminhoAtual);
            nTotalDiretorios++;

            for (const auto &p : iter)
            {
                if (fs::is_regular_file(p))
                {
                    contalinhas(p);
                }
                else if (fs::is_directory(p))
                {
                    pastas.push(p);
                }
            }
        }
        catch (std::exception &e)
        {
            cerr << e.what() << endl;
        }
    }
}

void buscarDiretorio(const fs::path &caminho)
{
    cout << "Buscando diretório " << caminho << endl;
    fs::directory_iterator iter(caminho);

    for (const auto &p : iter)
    {
        if (fs::is_regular_file(p))
        {
            contalinhas(p);
        }
        else if (fs::is_directory(p))
        {
            buscarDiretorio(p);
        }
    }
}

int main(int argc, char **argv)
{
#ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    if (argc == 1)
    {
        cout << "Forma de uso: " << argv[0] << " <diretório-base>" << "\n";
        return -1;
    }

    if (leFiltros())
    {
        if (fs::exists(argv[1]))
        {
            nLinhasTotais = 0;
            nTotalArquivos = 0;
            nTotalDiretorios = 0;

            const auto inicio = chrono::system_clock::now();
            buscarDiretorioIterativo(argv[1]);
            const auto fim = chrono::system_clock::now();

            const auto lapsoTempo = chrono::duration_cast<chrono::seconds>(fim - inicio).count();

            cout << endl;
            cout << "Tempo gasto: " << lapsoTempo << " segundos. " << endl;
            cout << "Total de Arquivos: " << nTotalArquivos << "." << endl;
            cout << "Total de Diretórios: " << nTotalDiretorios << "." << endl;
        }
        cout << "Total LOC: " << nLinhasTotais << endl;
    }

    return 0;
}