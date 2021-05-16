FOLDERNAME="inputs"
FOLDEROUTPUTNAME="our_outputs"
OUTPUTDIR="output"

mkdir -p ${FOLDERNAME}

g++ -std=c++11 -O3 -Wall -o proj Projeto2C.cpp -lm

mkdir -p ${FOLDEROUTPUTNAME}

#o=0
for FILE in "$FOLDERNAME"/*.in; do          
        echo "$FILE"                                                                            
        #./proj < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        #echo "${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out"
        time ./proj < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        #echo "outputs/output"$o
        #o=$(($o+1))
        echo "----------------------"
done

rm proj
#rm -r ${FOLDEROUTPUTNAME}
#rm -r ${FOLDERNAME}
