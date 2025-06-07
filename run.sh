cd "$(dirname "$0")"
mkdir -p build
cd build
cmake ..
make
./cpp_modern_techniques