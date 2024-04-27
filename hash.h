#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
                unsigned long long w[5] = {0}; // Array to store the values of each chunk
        int len = k.length();
        int numChunks = (len + 5) / 6; // Calculate the number of chunks

        // Process each chunk
        for (int i = 0; i < numChunks; i++) {
            int chunkStart = std::max(0, len - 6 * (i + 1));
            int chunkEnd = len - 6 * i;
            unsigned long long chunkValue = 0;
            for (int j = chunkStart; j < chunkEnd; j++) {
                int pos = chunkEnd - j - 1;
                chunkValue += letterDigitToNumber(k[j]) * static_cast<unsigned long long>(std::pow(36, pos));
            }
            w[4 - i] = chunkValue; // Store the result in w, starting from the end
        }

        // Compute the hash using the w values and the rValues
        unsigned long long hash = 0;
        for (int i = 0; i < 5; i++) {
            hash += rValues[i] * w[i];
        }
        return hash;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
                if (letter >= '0' && letter <= '9') {
            return 26 + (letter - '0'); // Numbers 0-9 are 26-35
        } else if (letter >= 'a' && letter <= 'z') {
            return letter - 'a'; // Lowercase letters a-z are 0-25
        } else if (letter >= 'A' && letter <= 'Z') {
            return letter - 'A'; // Uppercase letters A-Z are also 0-25
        }
        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
