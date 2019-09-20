#include <cstring>
#include <cstdint>
#include <iostream>
#include "ir-slinger/irslinger.h"
#include "decoder.h"

int irz_emit(int data[], int length);
void print_help();
void print_para_error();
void print_runtime_error(int);

int main(int argc,char** argv) {

    int power = 0, temp = 26, mode = 0, swing = 0, wind_speed = 0;

    if(argc > 1) {
        if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
            print_help();
            return 0;
        }

        if(argc == 6) {
            try {
                sscanf(argv[1], "%d", &power);
                sscanf(argv[2], "%d", &temp);
                sscanf(argv[3], "%d", &mode);
                sscanf(argv[4], "%d", &swing);
                sscanf(argv[5], "%d", &wind_speed);
            } catch (int e) {
                print_para_error();
            }
        } else {
            print_para_error();
        }
    }

    try {

        ac_status test = {
                .power =  power,
                .temp = temp,
                .mode = mode,
                .swing = swing,
                .wind_speed = wind_speed
        };
        int origin[14], binary[14 * 8];
        memset(origin, 0, sizeof(origin));
        memset(binary, 0, sizeof(binary));
        decoder::status_to_array(test, origin);
        decoder::array_to_binary(origin, binary);

        std::vector<int> time_seq = decoder::binary_to_timeseq(binary);
        size_t sz = time_seq.size();
        int time_array[256];
        for (int i = 0; i < sz; i++) {
            time_array[i] = time_seq[i];
        }
        irz_emit(time_array, sz);
    } catch (int e) {
        print_runtime_error(e);
        return -1;
    }
    return 0;
}


int irz_emit(int data[], int length) {
    uint32_t outPin = 17;            // The Broadcom pin number the signal will be sent on
    int frequency = 38000;          // The frequency of the IR signal in Hz
    double dutyCycle = 0.5;         // The duty cycle of the IR signal. 0.5 means for every cycle,
    // the LED will turn on for half the cycle time, and off the other half

    int result = irSlingRaw(
            outPin,
            frequency,
            dutyCycle,
            data,
            length);
    return result;
}

void print_help() {
    std::cout << "Usage:" << std::endl
              << "irz POWER TEMP MODE SWING WINDSPEED" << std::endl
              << "POWER     : 0(off) / 1(on)" << std::endl
              << "TEMP      : 16~31(Temperature you want to set)" << std::endl
              << "MODE      : 0(cool) / 1(warm) / 2(dry)" << std::endl
              << "SWING     : 0(off) / 1(up and down)" << std::endl
              << "WINDSPEED : 0(auto) / 1(slow) / 2(medium) / 3(fast)" << std::endl;
    std::cout << "Copyright (c) 2019 Yuta" << std::endl;
    std::cout << "Opensource under MIT License" << std::endl;
    return;
}

void print_para_error() {
    std::cerr << "Wrong Parameter\n"
              << std::endl;
    print_help();
    return ;
}

void print_runtime_error(int exception) {
    std::cerr << "Runtime Error : " << exception << std::endl;
}
