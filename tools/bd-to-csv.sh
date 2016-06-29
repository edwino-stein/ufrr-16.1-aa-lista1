 #!/bin/sh

dbFile=$1;
cols=();
rows=();
rowData=();
jqBin="./tools/jq/jq";

function hasCol(){
    local e;

    for e in `seq 0 $((${#cols[@]} - 1))`
    do
        if [ "${cols[$e]}" == $1 ]; then
            echo $e;
            return 0;
        fi
    done;
    return 1;
}

function hasRow(){
    local e;

    if [ -z "$rows" ]; then
        return 1;
    fi

    for e in `seq 0 $((${#rows[@]} - 1))`
    do
        if [ "${rows[$e]}" == $1 ]; then
            echo $e;
            return 0;
        fi
    done;
    return 1;
}

os=$(uname -s);
case $os in
	"Linux") os="linux" ;;
	"Darwin") os="osx" ;;
esac

arch=$(uname -m);
case $arch in
	"i386") arch="x86" ;;
	"i486") arch="x86" ;;
	"i586") arch="x86" ;;
	"i686") arch="x86" ;;
	"x86") arch="x86" ;;
	"86") arch="x86" ;;
	"x86_64") arch="x64" ;;
	"x64") arch="x64" ;;
	"64") arch="x64" ;;
esac

jqBin="$jqBin-$os-$arch";
if [ ! -f "$jqBin" ] ; then
    echo "*********************************** ERRO ***********************************";
    echo "Não existe uma versão para seu sistema do programa jq.";
    echo "O programa pode ser baixado em https://stedolan.github.io/jq/download/";
    echo "Baixe e mova o binario para o diretorio jq/ com o seguinte padrão de nome:";
    echo;
    echo "jq-{os}-{arch}";
    echo;
    echo "Exemplo: jq/jq-linux-x86";
    echo "****************************************************************************";
    exit 1;
fi

chmod +x $jqBin;

if [ ! -f "$dbFile" ] ; then
    echo "*********************************** ERRO ***********************************";
    echo "Arquivo de banco de dados inválido";
    echo "****************************************************************************";
    exit 1;
fi

data=$(cat $dbFile);

for i in `seq 1 $#`
do
    if [ $i -ne 1 ]; then
        eval "arg=\$$i";
        cols+=($arg);
    fi
done;

keys=($(echo -n "$data" | $jqBin -c keys_unsorted | tr "," " " | tr "[" " " | tr "]" " " | tr "\"" " "));
values=($(echo "$data" | $jqBin -c "map(.)"));

for i in `seq 0 $((${#keys[@]} - 1))`
do
    inSize=$(echo ${keys[$i]} | grep -Eo "_[0-9]+" | grep -Eo "[0-9]+");
    rowName=$(echo ${keys[$i]} | cut -d_ -f1);

    rowIndex=$(hasRow "$rowName");
    if [ $? -eq 1 ]; then
        rows+=("$rowName");
        rowData+=("[]");
        rolIndex=$((${#rows[@]} - 1));
    fi

    colIndex=$(hasCol "$inSize");
    if [ $? -eq 0 ]; then
        v=$(echo "$values" | $jqBin ".[$i]");
        rowData[$rolIndex]=$(echo "${rowData[$rolIndex]}" | $jqBin ".[$colIndex]=$v");
    fi

done;

csvFile=$(echo $dbFile | cut -f1 -d'.');
csvFile="$csvFile.csv";
if [ ! -f "$csvFile" ] ; then
    touch $csvFile;
fi
echo -n "" > $csvFile;


r="";
for i in `seq 0 $((${#cols[@]} - 1))`
do

    if [ $i == $((${#cols[@]} - 1)) ]; then
        r="$r${cols[$i]}";
    else
        r="$r${cols[$i]}, ";
    fi

done;
echo $r >> $csvFile;

for i in `seq 0 $((${#rows[@]} - 1))`
do

    r="${rows[$i]}, ";
    rd=$(echo "${rowData[$i]}");
    for j in `seq 1 $((${#cols[@]} - 1))`
    do

        c=$(echo "$rd" | $jqBin -c ".[$j]");
        if [ "$c" == "null" ]; then
            cv="0";
        else
            total=$(echo "$c" | $jqBin ".total");
            count=$(echo "$c" | $jqBin ".count");
            cv=$(bc <<< "scale=3; $total/$count");
        fi

        if [ $j == $((${#cols[@]} - 1)) ]; then
            r="$r$cv";
        else
            r="$r$cv, ";
        fi

    done;
    echo $r >> $csvFile;
done;
