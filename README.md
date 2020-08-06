# O Escaravelho de Ouro

Esse software foi desenvolvido como parte de avaliação para a disciplina de Criptografia para Segurança de Dados, a fim de obter o grau de Bacharel em Sistemas de Informação pela Universidade Federal de Santa Maria - UFSM. 
Inspirado na história [The Golden Bug](https://en.wikipedia.org/wiki/The_Gold-Bug) de Edgar Allan Poe, o intuíto era de desenvolver uma programa que fizesse análise criptográfica (verificação de plaintext com análise de frequencia de caracteres e busca de palavras conhecidas) e criptografia (encriptação e decriptação) usando o algoritmo de [substituição monoalfabética](https://pt.wikipedia.org/wiki/Cifra_de_substitui%C3%A7%C3%A3o_monoalfab%C3%A9tica)

## Funções e Modo de uso
#### Funções 
As seguintes funções estão disponíveis no programa: 
   * Cifragem de mensagem;
   * Decifragem de mensagem;
   * Verificação de plaintext, procurando por palavras conhecidas;
   * Análise de frequência, dando a frequência de caracteres em textos.
   
   
#### Modo de uso
O programa é rodado em um painel de linha de comando.

Todos os arquivos de entrada devem ter a extensão .txt, assim como todos os arquivos gerados serão do tipo .txt.
Em todos os casos, apenas o nome do arquivo (sem extensão) deve ser especificado. Diretórios podem ser indicados
 usando `/`.

###### Cifragem e decifragem
Para a cifragem e decifragem, é necessário ter uma tabela de substituição definida, que deve ser um arquivo .txt com 
o seguinte formato:
   
   * Na primeira linha, os caracteres usados na língua não cifrada, separados por um pipe `|`;
   * Na segunda linha, os caracteres usados para a encrptação/substituição também separados por um pipe `|`;
   * Exemplo: [exemplo_tabela_substituiçao.txt](https://github.com/ddvargas/escaravelhoDeOuro/blob/master/exemplo_tabela_substitui%C3%A7ao.txt)
   
No texto, cada caractere original da primeira linha da tabela será trocado pelo seu respectivo da linha abaixo. 
Será gerado um novo arquivo .txt com a saída resultado da encriptação.
   

###### Verificação de plaintext
A verificação de plaintext recebe uma tabela de substituição igual ao da cifragem e decifragem ([exemplo_tabela_substituiçao.txt](https://github.com/ddvargas/escaravelhoDeOuro/blob/master/exemplo_tabela_substitui%C3%A7ao.txt))
e realiza a decifragem produzindo um arquivo de saída (com nome a ser definido por você). Após, você deve especificar um 
arquivo que contenha o conjunto de palavras que gostaria de procurar no plaintext recém decifrado. 
Cada palavra nesse arquivo deve estar disposto em uma linha. 

O programa irá procurar as palavras e apresentar na tela quais delas foram encontradas.

###### Tabela de frequência
A verificação de tabela de frequência recebe uma tabela de frequência em que em cada linha:
   * Um caractere por linha;
   * Depois do caractere, o número de vezes que apareceu;
   * Depois o valor da frequência daquele caractere com separação decimal usando uma vírgula;
   * Todos separados por um pipe `|`;

Um exemplo da tabela pode ser visualizado em [exemplo_tabela_frequencia.txt](https://github.com/ddvargas/escaravelhoDeOuro/blob/master/exemplo_tabela_frequencia.txt)

Caso a tabela exista, os valores anteriores dos caracteres e número de vezes que apareceu são mantidos 
e acrescidos. Caso o arquivo não exista, ele é criado nesse mesmo formato. O resultado pode ser visualizado no arquivo 
criado.



## Compilação
O programa pode ser compilado usando o CMake, para isso baixar o arquivo CMakeLists.txt e o arquivo main.c.
Ao compilar será gerado em executável chamado "escaravelho".

Caso não queira usar o CMake, pode usar apenas o GCC, para isso baixar apenas o arquivo main.c, executar especificando 
um nome de saída.
Se o nome não for especificado, é gerado um executável "a.out".
