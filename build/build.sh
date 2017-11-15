RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'

echo -e "${RED} BUILDING CMAKE FILES"
cmake ../CMakeLists.txt
echo -e "${YELLOW} MAKING FILES"
make -C ..
echo -e "${GREEN} RUNNING PROGRAM..."
../pt
echo -e "${YELLOW}"
