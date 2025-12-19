source venv/bin/activate python3

echo "compiled C++ code"
./compile.sh
g++ -std=c++17  -o lowerBound -O3 ../lowerbound.cpp 
g++ -std=c++17  -o brut -O3 ../brut.cpp 

echo "Generating test..."
python3 ../gen.py < small.in > test.in

echo "Running solution"
./ant < test.in > test.out
./lowerBound < test.in > lowerBound.out
./brut < test.in > brut.out
python3 ../demo.py < test.in


cat lowerBound.out
cat brut.out
cat test.out
