 #!/bin/sh

buildDir="./build/";
outputDir="./output/";
resultsDir="./results/";

invocation="./tools/compiler";
databaseupdater="./tools/update-db.sh";

if [ ! -d "$outputDir" ]; then
  mkdir "$outputDir";
fi

if [ ! -d "$resultsDir" ]; then
  mkdir "$resultsDir";
fi

chmod +x $invocation;
chmod +x $databaseupdater;

case $1 in

    "questao5")
        bash -c "$invocation questao5.c sorts/src/insertionSort.c sorts/src/quickSort.c sorts/src/mergeSort.c sorts/src/swap.c";
        echo "Executando o programa questao5...";
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
            echo "Foram ordenados $4 números em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao5.")
        bash -c "$invocation questao5.c sorts/src/insertionSort.c sorts/src/quickSort.c sorts/src/mergeSort.c sorts/src/swap.c";
        echo "Executando o programa questao5...";
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
            echo "Foram ordenados $4 números em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao5.c")
        bash -c "$invocation questao5.c sorts/src/insertionSort.c sorts/src/quickSort.c sorts/src/mergeSort.c sorts/src/swap.c";
        echo "Executando o programa questao5...";
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
            echo "Foram ordenados $4 números em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo "Executando o programa questao8...";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
            echo "Foram inseridos $4 números em uma árvore $2 em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8.")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo "Executando o programa questao8...";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
            echo "Foram inseridos $4 números em uma árvore $2 em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8.c")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo "Executando o programa questao8...";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
            echo "Foram inseridos $4 números em uma árvore $2 em ${result}µs.";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao4")
        bash -c "$invocation questao4.c";
        echo "Executando o programa questao4..."
        echo;
        bash -c "${buildDir}questao4";
    ;;

    "questao4.")
        bash -c "$invocation questao4.c";
        echo "Executando o programa questao4..."
        echo;
        bash -c "${buildDir}questao4";
    ;;

    "questao4.c")
        bash -c "$invocation questao4.c";
        echo "Executando o programa questao4..."
        echo;
        bash -c "${buildDir}questao4";
    ;;

    "generate.c")
        bash -c "$invocation generate.c";
        echo "Executando o programa generate...";
        bash -c "${buildDir}generate $2 $3 $4";
        echo "Foram gerados $2 números e salvos em $3.";
    ;;

    "generate.")
        bash -c "$invocation generate.c";
        echo "Executando o programa generate...";
        bash -c "${buildDir}generate $2 $3 $4";
        echo "Foram gerados $2 números e salvos em $3.";
    ;;

    "generate")
        bash -c "$invocation generate.c";
        echo "Executando o programa generate...";
        bash -c "${buildDir}generate $2 $3 $4";
        echo "Foram gerados $2 números e salvos em $3.";
    ;;

 	*)
 		echo "Opções: questao4 | questao8 | questao5 | generate."
 		exit 1;
 	;;
esac

exit 0;
