# contalinhas

1. Para iniciar, instale:

-   Visual Studio Code ou CLion IDE;
-   CMake Tools para VSCode;
-   C++ Extensions para VSCode;
-   CMake 3.12 no mínimo;
-   Git

  2. Instruções para clonar e compilar o projeto no VSCode:

      2.1. Acione Ctrl + Shift + P e digite "Git: Clone" para clonar o repositório:

     -   https://github.com/carlosleonardo/contalinhas.git

      2.2. Abra a pasta clonada no VSCode e abra o terminal integrado (Ctrl + `). Verifiqq se você está na pasta correta:

     -   $ cd contalinhas

     2.3. Configure o cmake para gerar os arquivos de build:

     -   $ cmake -S . -B build

     2.4. Dê um build no projeto:

     -   $ cmake --build build

  3. Instruções para o CLion:

     3.1. Abra o CLion e selecione "File - New Project From Version Control".

     3.2. Cole a URL do repositório:
     https://github.com/carlosleonardo/contalinhas.git
    
     3.3. Ao aparecer a janela de configuração do projeto, selecione o diretório onde o projeto será salvo e clique em "Clone".
   
     3.4. O CLion irá abrir o projeto e configurar o CMake automaticamente. Confirme a configuração apresentada
