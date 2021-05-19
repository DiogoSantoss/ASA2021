FOLDERNAME="gen_inputs"
FOLDEROUTPUTNAME="our_outputs"
FILEBASENAME="graph"

#Variables for gen2procs
N=(500 1000 1500 2000)
C=(50 100 150 200 250 300)

echo "Compiling proj..."
g++ -std=c++11 -O3 -Wall -o proj2 Projeto2.cpp -lm
echo "Success"
echo "Compiling gen2procs..."
g++ -std=c++11 -O3 -Wall -o gen2procs gen2procs.cpp -lm
echo "Success"

echo "Creating test files..."
mkdir -p ${FOLDERNAME}
for v in ${N[@]}; do
    for p in ${C[@]}; do
        echo Creating $v $p
        ./gen2procs $v $p > ${FOLDERNAME}/${FILEBASENAME}$v-$p.in
    done
done
echo "Done"

echo "Testing..."
mkdir -p ${FOLDEROUTPUTNAME}
for FILE in "$FOLDERNAME"/*.in; do          
        echo "$FILE"                                                                            
        echo "Lista"
        time ./proj2 < "$FILE" >${FOLDEROUTPUTNAME}/${OUTPUTDIR}_$(basename $FILE).out
        echo "----------------------"
done
echo "Done"

echo "Removing compiled files..."
rm proj2 && rm gen2procs