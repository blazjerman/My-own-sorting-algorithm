#include <iostream>
#include <chrono>
#include <random>


void sortByBit(uint32_t *arrayRead, uint32_t *arrayWrite, const int32_t start, const int32_t end, uint32_t bit) {

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

    if(top != start) sortByBit(arrayWrite, arrayRead, start, top, bit);
    if(end != top) sortByBit(arrayWrite, arrayRead,top, end, bit);

}



int main() {


    const int32_t ARRAY_SIZE = 2000000000;
    auto **array = new uint32_t*[2];

    for (size_t i = 0; i < 2; ++i) array[i] = new uint32_t[ARRAY_SIZE];  // Allocate memory for each row

    uint32_t max_unsigned_int_size = std::numeric_limits<unsigned int>::max();




    //Random numbers
    std::mt19937 rng(static_cast<uint32_t>(1));
    std::uniform_int_distribution<uint32_t> distribution(0, max_unsigned_int_size);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        array[0][i] = distribution(rng);
        array[1][i] = array[0][i];
    }



    auto start = std::chrono::high_resolution_clock::now();


    sortByBit(array[0], array[1], 0,ARRAY_SIZE - 1, 1 << 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;


    std::cout << "Array_0:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[0][j];


    std::cout << "\nArray_1:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[1][j];


    return 0;
}







