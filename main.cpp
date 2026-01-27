#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include <filesystem>
#include <chrono>
#include <algorithm>

#ifdef WIN32
#include <windows.h>
#endif

using namespace std;
namespace fs = std::filesystem;

long int nLinhasTotais;
long nTotalLOC;
const string filtro = "filtro.ini";

long int nTotalArquivos;
long int nTotalDiretorios;

list<string> listaExtensoes;
list<string> listaPastasIgnoradas;

// Verifica se a pasta deve ser ignorada
bool deveIgnorarPasta(const fs::path &caminhoPasta)
{
    string nomePasta = caminhoPasta.filename().string();
    return std::any_of(listaPastasIgnoradas.begin(), listaPastasIgnoradas.end(),
                       [&nomePasta](const string &pastaIgnorada) {
                           return nomePasta == pastaIgnorada;
                       });
}

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
    string secaoAtual;

    while (!inp.eof())
    {
        // Recupera uma extensão por linha
        getline(inp, linha);

        // Remove espaços em branco no início e fim da linha
        linha.erase(0, linha.find_first_not_of(" \t\r\n"));
        linha.erase(linha.find_last_not_of(" \t\r\n") + 1);

        // Ignora linhas vazias
        if (linha.empty())
            continue;

        // Verifica se é uma seção
        if (linha.front() == '[' && linha.back() == ']')
        {
            secaoAtual = linha.substr(1, linha.length() - 2);
            continue;
        }

        // Adiciona item à lista apropriada baseado na seção atual
        if (secaoAtual == "extensoes")
        {
            listaExtensoes.push_back(linha);
        }
        else if (secaoAtual == "pastas_ignoradas")
        {
            listaPastasIgnoradas.push_back(linha);
        }
    }

    // Verifica se pelo menos a seção de extensões foi encontrada
    if (listaExtensoes.empty())
    {
        cout << "Nenhuma extensão encontrada na seção [extensoes]" << endl;
        return false;
    }

    return true;
}

// Vê se o arquivo possui a extensão permitida
bool possuiExtensaoFiltrada(const fs::path &c)
{
    const auto extensao = c.extension();
    return std::any_of(listaExtensoes.begin(), listaExtensoes.end(),
                [&extensao](const string &ext) {
                    return extensao == ("." + ext);
                });
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
    long int nLinhaVazia = 0;

    if (!inp)
    {
        cout << "Não foi possível abrir " << caminho << endl;
        return;
    }

    string linha;
    while (!inp.eof())
    {
        getline(inp, linha);
        // Remove espaços em branco no início e fim da linha
        linha.erase(0, linha.find_first_not_of(" \t\r\n"));
        linha.erase(linha.find_last_not_of(" \t\r\n") + 1);
        // Ignora linhas vazias
        if (linha.empty())
            nLinhaVazia++;
        nLinhas++;
    }
    cout << "Linhas do arquivo: " << nLinhas << endl;
    nTotalArquivos++;
    nLinhasTotais += nLinhas;
    nTotalLOC += (nLinhas - nLinhaVazia);
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

            for (const auto &p : iter)
            {
                if (fs::is_regular_file(p))
                {
                    contalinhas(p);
                }
                else if (fs::is_directory(p) && !deveIgnorarPasta(p))
                {
                    cout << "Diretório encontrado: " << p.path() << endl;
                    nTotalDiretorios++;
                    // Adiciona o diretório à pilha para busca posterior
                    pastas.push(p);
                }
                else if (fs::is_directory(p) && deveIgnorarPasta(p))
                {
                    cout << "Ignorando diretório: " << p.path() << endl;
                }
                else
                {
                    //pastas.push(p);
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
            nTotalLOC = 0;

            const auto inicio = chrono::system_clock::now();
            buscarDiretorioIterativo(argv[1]);
            const auto fim = chrono::system_clock::now();

            const auto lapsoTempo = chrono::duration_cast<chrono::seconds>(fim - inicio).count();

            cout << endl;
            cout << "Tempo gasto: " << lapsoTempo << " segundos. " << endl;
            cout << "Total de Arquivos: " << nTotalArquivos << "." << endl;
            cout << "Total de Diretórios: " << nTotalDiretorios << "." << endl;
        }
        cout << "Total Linhas: " << nLinhasTotais << endl;
        cout << "Total LOC: " << nTotalLOC << endl;
    }

    return 0;
}
