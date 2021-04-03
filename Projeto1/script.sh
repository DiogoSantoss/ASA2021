FILEBASENAME="dag"
FOLDERNAME="test"
INPUTDIR="bigdags"
FOLDEROUTPUTNAME="outputs"
OUTPUTDIR="output"
VERTICES=(100 200 500 1000 2000 5000)
PROBABILIDADE=(0.1 0.5 0.9)

g++ -std=c++11 -O3 -Wall -o randomDAG randomDAG.cpp -lm

mkdir -p ${FOLDERNAME}

for v in ${VERTICES[@]}; do
    for p in ${PROBABILIDADE[@]}; do
        echo Creating $v $p
        ./randomDAG $v $p > ${FOLDERNAME}/${FILEBASENAME}$v-$p.txt
    done
done

g++ -std=c++11 -O3 -Wall -o proj Projeto1.cpp -lm

mkdir -p ${FOLDEROUTPUTNAME}

for FILE in "$FOLDERNAME"/*.txt; do          
        echo "$FILE"                                                                            
        ./proj < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).txt
        echo "----------------------"
done

rm randomDAG && rm proj