FOLDERNAME="inputs"
FOLDEROUTPUTNAME="our_outputs"
OUTPUTDIR="output"

mkdir -p ${FOLDERNAME}

g++ -std=c++11 -O3 -Wall -o proj1 tentativa1700.cpp -lm
g++ -std=c++11 -O3 -Wall -o proj2 Projeto2-1625.cpp -lm

mkdir -p ${FOLDEROUTPUTNAME}

#o=0
for FILE in "$FOLDERNAME"/*.in; do          
        echo "$FILE"                                                                            
        #./proj < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        #echo "${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out"
        echo "Lista"
        time ./proj1 < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        echo "Matriz"
        time ./proj2 < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        #echo "outputs/output"$o
        #o=$(($o+1))
        echo "----------------------"
done

rm proj1 && rm proj2
#rm -r ${FOLDEROUTPUTNAME}
#rm -r ${FOLDERNAME}
