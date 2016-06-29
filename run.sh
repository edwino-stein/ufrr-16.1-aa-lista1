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
 		echo "Opções: generate."
 		exit 1;
 	;;
esac

exit 0;
