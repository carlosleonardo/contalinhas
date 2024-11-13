# contalinhas

1. Para iniciar, instale:

-   Visual Studio Code;
-   C++ Extensions para VSCode;
-   conan package manager
-   CMake 3.12
-   Git

2. Usando git, faça a clonagem deste projeto em um diretório qualquer:

-   git clone https://github.com/carlosleonardo/contalinhas.git

3. Execute o comando para detectar o profile:

-   conan profile detect --force

4. Entre no diretório raiz e execute o seguinte comando:

-   conan install . --build=missing
    O conan deve estar no PATH. Ao término da execução, as dependências listadas em conanfile.txt devem estar instaladas

5. CMake deve estar no PATH. Execute o seguinte comando:

-   $ cmake --list-presets
-   $ cmake --preset=conan-default para usar o profile do conan

6. Configure o cmake

-   $ cmake .

7. Dê um build no projeto:

-   $ cmake . --build build
