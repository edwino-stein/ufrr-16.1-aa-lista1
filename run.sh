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
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao5.")
        bash -c "$invocation questao5.c sorts/src/insertionSort.c sorts/src/quickSort.c sorts/src/mergeSort.c sorts/src/swap.c";
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao5.c")
        bash -c "$invocation questao5.c sorts/src/insertionSort.c sorts/src/quickSort.c sorts/src/mergeSort.c sorts/src/swap.c";
        echo;
        result=$(bash -c "${buildDir}questao5 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao5.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8.")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

    "questao8.c")
        bash -c "$invocation questao8.c structs/src/binaryTree.c structs/src/avlTree.c structs/src/RBTree.c";
        echo;
        result=$(bash -c "${buildDir}questao8 $2 $3 $4");
        if [ $? -eq 0 ]; then
            bash -c "$databaseupdater ${resultsDir}db_questao8.json $2_$4 $result";
        else
            echo "Erro na execução:";
            echo "$result";
        fi
    ;;

     "generate.c")
         bash -c "$invocation generate.c";
         bash -c "${buildDir}generate $2 $3";
     ;;

     "generate.")
         bash -c "$invocation generate.c";
         bash -c "${buildDir}generate $2 $3";
     ;;

    "generate")
        bash -c "$invocation generate.c";
        bash -c "${buildDir}generate $2 $3";
    ;;

 	*)
 		echo "Opções: questao5 | generate."
 		exit 1;
 	;;
esac

exit 0;
