#include <iostream>
#include <chrono>
#include <random>


//Time complexity is O(n * b)
//b stands for value "bit" size, for uint32 it is 32

void sortByBit(uint32_t *array, const uint32_t start, const uint32_t end, uint32_t mask) {

    uint32_t top = start;
    uint32_t bot = end - 1;


    while (true) {

        while ((array[top] & mask) == 0) {
            if (bot <= top) goto endOfLoop;
            ++top;
        }

        while ((array[bot] & mask) != 0) {
            if (bot <= top) goto endOfLoop;
            --bot;
        }

        uint32_t tmp = array[top];
        array[top] = array[bot];
        array[bot] = tmp;

    }

    endOfLoop:

    if (top < end) if((array[top] & mask) == 0) ++top;

    mask >>= 1;
    if (mask == 0) return;

    if(top != start) sortByBit(array, start, top, mask);
    if(end != top) sortByBit(array, top, end, mask);

}




const uint32_t ARRAY_SIZE = 6;
const uint32_t PRINT_N_FIRST = 6;


int main() {


    auto *array = new uint32_t[ARRAY_SIZE];

    uint32_t max_unsigned_int_size = std::numeric_limits<unsigned int>::max();

    //Generate random numbers
    std::mt19937 rng(static_cast<uint32_t>(1));
    std::uniform_int_distribution<uint32_t> distribution(0, 100);
    for (size_t i = 0; i < ARRAY_SIZE; ++i) array[i] = distribution(rng);

    auto start = std::chrono::high_resolution_clock::now();

    sortByBit(array, 0,ARRAY_SIZE, 1 << 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << "\nFirst n numbers:" << std::endl;

    for (size_t i = 0; i < PRINT_N_FIRST; ++i) std::cout << " " << array[i];

    return 0;
}







