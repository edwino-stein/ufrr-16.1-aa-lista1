1ª Lista de exercícios de Análise de Algoritmos

Aluno: Edwino Stein
Matricula: 1201324411  

As respostas estão no arquivo Repostas.pdf e Repostas.docx.
As instruções de como compilar e executar as questões 4, 5 e 8 estão no arquivo de respostas.

Para gerar um arquivo de entrada, basta executar o programa generate.c com o comando:

    $ ./run.sh generate.c <quantidade> <arquivo> <ordem>

Onde:

    <quantidade_de_valores>: Número de valores que serão gerados;
    <arquivo>: Caminho do arquivo que será gravado os valores;
    <ordem>: Define o critério de gerção do valores:
        asc: Valores em ordem crescente;
        desc: Valores em ordem decrescente;
        random: Valores aleatórios;

Exemplo:

    $ ./run.sh generate.c 1000 inputs/input-1000-rand.txt random
