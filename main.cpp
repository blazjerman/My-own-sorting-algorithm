#include <iostream>
#include <chrono>
#include <random>


void sortByBit(uint32_t *array, const int32_t start, const int32_t end, uint32_t mask) {

    int32_t top = start;
    int32_t bot = end - 1;


    while (true) {

        while ((array[top] & mask) != 0){
            ++top;
            if (bot <= top) goto endOfLoop;
        }

        while ((array[bot] & mask) == 0){
            --bot;
            if (bot <= top) goto endOfLoop;
        }

        uint32_t tmp = array[top];
        array[top] = array[bot];
        array[bot] = tmp;

    }


    endOfLoop:


    if (top < end) if((array[top] & mask) != 0) ++top;

    mask >>= 1;
    if (mask == 0) return;

    if(top != start) sortByBit(array, start, top, mask);
    if(end != top) sortByBit(array, top, end, mask);

}




const int32_t ARRAY_SIZE = 5000;
const uint32_t PRINT_N_FIRST = 6;


int main() {



    auto *array = new uint32_t[ARRAY_SIZE];


    uint32_t max_unsigned_int_size = std::numeric_limits<unsigned int>::max();


    //Generate random numbers
    std::mt19937 rng(static_cast<uint32_t>(36736));
    std::uniform_int_distribution<uint32_t> distribution(0, max_unsigned_int_size);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) array[i] = distribution(rng);


    auto start = std::chrono::high_resolution_clock::now();

    sortByBit(array, 0,ARRAY_SIZE, 1 << 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;


    std::cout << "First n numbers:\n";

    for (size_t j = 0; j < PRINT_N_FIRST; ++j) std::cout << " " << array[j];

    return 0;
}







