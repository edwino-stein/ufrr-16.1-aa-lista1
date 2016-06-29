 #!/bin/sh

dbFile=$1;
key=$2;
value=$3;

data="";
jqBin="./tools/jq/jq";

function hasKey(){
    if [ "$(echo -n "$data" | $jqBin .$1)" == "null" ] ; then
        return 0;
    else
        return 1;
    fi
}

function getValue(){
    echo $(echo -n $data | $jqBin .$1);
}

function setValue(){
    data=$(echo -n "$data" | $jqBin .$1=$2)
}

function incrementValue(){
    data=$(echo -n "$data" | $jqBin .$1=.$1+$2);
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
    touch $dbFile;
    echo "{}" > "$dbFile";
fi

data=$(cat $dbFile);

hasKey $key;
if [ $? == 0 ] ; then
    setValue "$key.total" 0;
    setValue "$key.times" 0;
fi

incrementValue "$key.total" $value;
incrementValue "$key.times" 1;

# Commit
if [ $? -eq 0 ] ; then
    echo -n "$data" > $dbFile;
fi
