echo "compiled C++ code"
./compile.sh
g++ -std=c++17 -o lowerBound -O3 ../lowerbound.cpp 

echo "Generating test..."
python3 ../gen.py < big.in > test.in

echo "Running solution"
time ./ant < test.in > test.out
./lowerBound < test.in > lowerBound.out

cat lowerBound.out
head -n 1 test.out
