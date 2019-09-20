//
// Created by copper on 2019/9/20.
//

#ifndef IRZ_DECODER_H
#define IRZ_DECODER_H

#include <vector>
#include <cstdio>

struct ac_status {
    int power; // 0 for off & 1 for on
    int temp; // origin temp
    int mode; // 0 for cool & 1 for warm & 2 for dry
    int swing; // 0 for fixed & 1 for on
    int wind_speed; // 0 for auto, 1 2 3
};

class decoder {
public:
    static void status_to_array(const ac_status &status, int dest[]);

    static void array_to_binary(int origin[], int dest[]);

    static std::vector<int> binary_to_timeseq(int binaries[]);
};


#endif //IRZ_DECODER_H
