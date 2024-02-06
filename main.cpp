#include <iostream>
#include <chrono>
#include <random>


void sortByBit(uint32_t *array, const int32_t start, const int32_t end, uint32_t bit) {

    int32_t top = start;
    int32_t bot = end - 1;


    while (true) {

        while ((array[top] & bit) != 0){
            ++top;
            if (bot <= top) goto endOfLoop;
        }

        while ((array[bot] & bit) == 0){
            --bot;
            if (bot <= top) goto endOfLoop;
        }

        uint32_t tmp = array[top];
        array[top] = array[bot];
        array[bot] = tmp;

    }


    endOfLoop:


    if (top < end) if((array[top] & bit) != 0) ++top;

    bit >>= 1;
    if (bit == 0) return;

    if(top != start) sortByBit(array, start, top, bit);
    if(end != top) sortByBit(array, top, end, bit);

}



int main() {


    const int32_t ARRAY_SIZE = 2000000000;
    //const int32_t ARRAY_SIZE = 6;
    auto *array = new uint32_t[ARRAY_SIZE];


    uint32_t max_unsigned_int_size = std::numeric_limits<unsigned int>::max();


    //Random numbers
    std::mt19937 rng(static_cast<uint32_t>(29381));
    std::uniform_int_distribution<uint32_t> distribution(0, max_unsigned_int_size);
    //std::uniform_int_distribution<uint32_t> distribution(0, 300);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) array[i] = distribution(rng);


    std::cout << "Array_0:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[j];
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();


    sortByBit(array, 0,ARRAY_SIZE, 1 << 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;


    std::cout << "Array_0:\n";
    for (size_t j = 0; j < 6; ++j) std::cout << " " << array[j];

    return 0;
}







