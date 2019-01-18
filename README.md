# contalinhas

1) Para iniciar, instale:
- Visual Studio Code;
- C++ Extensions para VSCode;
- conan package manager
- CMake 3.12
- Git

2) Usando git, fa�a a clonagem deste projeto em um diret�rio qualquer:
- git clone https://github.com/carlosleonardo/contalinhas.git

3) Crie os diret�rios Debug e Release na pasta raiz do projeto
4) Entre no diret�rio Debug e execute o seguinte comando:
- conan install .. -s debug_type=Debug
O conan deve estar no PATH. Ao t�rmino da execu�?o, as depend?ncias listadas em conanfile.txt devem estar insta
ladas
5) CMake deve estar no PATH. Execute o seguinte comando:
- $ cmake ..
6) Construa o projeto:
- $ cmake --build .

