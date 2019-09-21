//
// Created by copper on 2019/9/20.
//

#include <cstring>
#include "decoder.h"


void decoder::status_to_array(const ac_status &status, int dest[]) {
    //ac_status to array
    memset(dest, 0, 14 * sizeof(int));

    // 固定头部
    dest[0] = 0b10100110;
    // 温度和风向
    dest[1] = ((status.temp - 16) << 4) + (status.swing == 0 ? 0b0 : 0b1100);
    // 风速: 0自动，后面代表风速级别
    switch (status.wind_speed) {
        case 1:
            dest[5] = 0b01100000;
            break;
        case 2:
            dest[5] = 0b01000000;
            break;
        case 3:
            dest[5] = 0b00100000;
            break;
        default:
            dest[5] = 0b10100000;
            break;
    }
    // 模式：制冷0加热1除湿2
    switch (status.mode) {
        case 1:
            dest[7] = 0b00100000;
            dest[4] |= 0b10000000;
            break; //制热默认开启辅热
        case 2:
            dest[7] = 0b01000000;
            break;
        default:
            dest[7] = 0b00100000;
            break;
    }
    //开关：关0开1
    switch (status.power) {
        case 1:
            dest[4] |= 0b01000000;
            dest[12] = 0b10000101;
            break;
        default:
            dest[4] |= 0b00000000;
            dest[12] = 0b10000101;
            break;
    }

    //校验和
    for (int i = 0; i < 13; i++) {
        dest[13] += dest[i];
    }
    dest[13] &= 0b11111111;
    return;
}

void decoder::array_to_binary(int origin[], int dest[]) {
    int len = 14, counter = 0;
    for (int i = 0; i < len; i++) {
        int num = origin[i], start = (i + 1) * 8 - 1;
        while (++counter <= 8) {
            dest[start--] = num % 2;
            num /= 2;
        }
        counter = 0;
    }
    return;
}

std::vector<int> decoder::binary_to_timeseq(int binaries[]) {
    int onePulse = 562;              // The duration of a pulse in microseconds when sending a logical 1
    int zeroPulse = 562;             // The duration of a pulse in microseconds when sending a logical 0
    int oneGap = 1688;               // The duration of the gap in microseconds when sending a logical 1
    int zeroGap = 562;               // The duration of the gap in microseconds when sending a logical 0

    std::vector<int> time_seq;
    time_seq.reserve(2 * 128);
    time_seq.push_back(3178);
    time_seq.push_back(2972);
    time_seq.push_back(3097);
    time_seq.push_back(4418);
    for (int i = 0; i < 14 * 8; ++i) {
        switch (binaries[i]) {
            case 0:
                time_seq.push_back(zeroPulse);
                time_seq.push_back(zeroGap);
                break;
            case 1:
                time_seq.push_back(onePulse);
                time_seq.push_back(oneGap);
                break;
        }
    }
    time_seq.push_back(zeroPulse);


    return time_seq;
}
