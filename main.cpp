#include <iostream>
#include <chrono>
#include <random>


const int ARRAY_SIZE = 10000000;
unsigned int array_1[ARRAY_SIZE], array_0[ARRAY_SIZE];



void sortByBit(const int start, const int end, unsigned int bit) {

    unsigned int *arrayRead;
    unsigned int *arrayWrite;

    if ((bit & 1) != 0) {
        arrayRead = array_0;
        arrayWrite = array_1;
    } else {
        arrayRead = array_1;
        arrayWrite = array_0;
    }

    int top = start;
    int bot = end - 1;

    for (int j = start; j < end; ++j) {

        if ((arrayRead[j] & (1 << bit)) != 0) {
            arrayWrite[top] = arrayRead[j];
            ++top;
        } else {
            arrayWrite[bot] = arrayRead[j];
            --bot;
        }

    }

    --bit;
    if (bit == 0) return;

    if(top - start > 0) sortByBit(start, top, bit);
    if(end - top > 0) sortByBit(top, end, bit);

}



int main() {



    // Use the current time as a seed for the random number generator
    std::mt19937 rng(static_cast<unsigned int>(1));
    std::uniform_int_distribution<unsigned int> distribution(1, 10000000);

    // Fill the array with random elements
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array_0[i] = distribution(rng);
        //std::cout << " " << array_0[i];
    }
    std::cout << "\n";


    auto start = std::chrono::high_resolution_clock::now();

    sortByBit(0,ARRAY_SIZE - 1, 31);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Execution Time: " << duration.count() << " seconds" << std::endl;



    for (int j = 0; j < 6; ++j) {
        std::cout << " " << array_0[j];
    }

    std::cout << "\n";

    for (int j = 0; j < 6; ++j) {
        std::cout << " " << array_1[j];
    }


    return 0;
}







