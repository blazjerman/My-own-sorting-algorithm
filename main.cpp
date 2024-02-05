#include <iostream>
#include <chrono>
#include <random>


const int32_t ARRAY_SIZE = 200000000;
uint32_t array[2][ARRAY_SIZE];



void sortByBit(const int32_t start, const int32_t end, uint32_t bit) {

    uint32_t *arrayRead = array[(bit & 0x55555555) != 0];
    uint32_t *arrayWrite = array[(bit & 0x55555555) == 0];

    int32_t top = start;
    int32_t bot = end - 1;

    for (size_t j = start; j < end; ++j) {

        if ((arrayRead[j] & bit) != 0) {
            arrayWrite[top] = arrayRead[j];
            ++top;
        } else {
            arrayWrite[bot] = arrayRead[j];
            --bot;
        }

    }

    bit >>= 1;
    if (bit == 0) return;

    if(top != start) sortByBit(start, top, bit);
    if(end != top) sortByBit(top, end, bit);

}



int main() {

    uint32_t max_unsigned_int_size = std::numeric_limits<unsigned int>::max();


    //Random numbers
    std::mt19937 rng(static_cast<uint32_t>(1));
    std::uniform_int_distribution<uint32_t> distribution(0, max_unsigned_int_size);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        array[0][i] = distribution(rng);
        array[1][i] = array[0][i];
    }



    auto start = std::chrono::high_resolution_clock::now();


    sortByBit(0,ARRAY_SIZE - 1, 1 << 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;


    std::cout << "Array_0:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[0][j];


    std::cout << "\nArray_1:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[1][j];


    return 0;
}







