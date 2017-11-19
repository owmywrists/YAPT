RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'


output="../YAPT"
if [ -f ../YAPT ]
then
	rm ../YAPT
fi

echo -e "${RED}BUILDING CMAKE FILES"
cmake ../CMakeLists.txt

echo -e "${YELLOW}MAKING FILES"
make -C ..

if [ -f "$output" ]
then
	echo -e "${GREEN}RUNNING PROGRAM..."
	../YAPT
else
	echo -e "${YELLOW}Compiling failed"
fi

