clear;
cmake CMAkeLists.txt -B build/
make  -C build/ -s
cmake -P build/cmake_install.cmake
echo Program strat...
bin/start 
