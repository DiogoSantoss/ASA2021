#Variables
INPUTFOLDER="inputs"
OUTPUTFOLDER="outputs"

#Variables for gen2procs
#N=(500 1000 1500 2000)
N=(500 600 700 800 900 1000 1100 1200 1300 1400 1500)
C=(50)

g++ -std=c++11 -O3 -Wall -o gen2procs gen2procs.cpp -lm

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