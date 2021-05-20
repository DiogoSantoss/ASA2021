#Variables
INPUTFOLDER="inputs"
OUTPUTFOLDER="outputs"

#Variables for gen2procs
N=(500 1000 1500 2000)
C=(50 100 150 200 250 300)

compileFiles () 
{
    echo "Compiling proj..."
    if ! g++ -std=c++11 -O3 -Wall -o proj2 Projeto2.cpp -lm; then
        echo "Compilation error!"
        exit 1
    fi
    echo "Success"

    echo "Compiling gen2procs..."
    if ! g++ -std=c++11 -O3 -Wall -o gen2procs gen2procs.cpp -lm; then
        echo "Compilation error!"
        rm proj2
    exit 1
    fi
    echo "Success"
}

compileFiles

echo "Test Input:" 
mkdir -p ${INPUTFOLDER}
echo "Creating ${INPUTFOLDER}"
for v in ${N[@]}; do
    for p in ${C[@]}; do
        INPUTFILE=${INPUTFOLDER}/$v-$p.in
        echo Creating $INPUTFILE
        ./gen2procs $v $p > $INPUTFILE
    done
done
echo "Done"

echo "Testing:"
mkdir -p ${OUTPUTFOLDER}
rm log && touch log
for FILE in "$INPUTFOLDER"/*.in; do     
        FILEOUTPUT=${OUTPUTFOLDER}/$(basename $FILE).out      
        echo $FILE                                                       
        time ./proj2 < $FILE >$FILEOUTPUT
        echo $(basename $FILE) >> log
        cat $FILEOUTPUT >> log
done
echo "Done"

echo "Removing compiled and input/output files..."
rm proj2 && rm gen2procs && rm -r $INPUTFOLDER && rm -r $OUTPUTFOLDER
echo "Done"