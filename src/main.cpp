#include <iostream>
#include <string>
#include <chrono>
#include <climits>
#include "util/sha256.h"

#define DIFFICULTY 5
std::string prepareData(){
    std::string t;
    for (int i=0; i<DIFFICULTY; i++) {
        t += "0";
    }
    return t;
}

int main(int, char**) {
    long nonce = 0;
    std::chrono::milliseconds beginMs = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::string msg = "hello, world";
    std::cout << "test begin time: " <<  beginMs.count() << std::endl;
    while (nonce < LONG_MAX) {
        std::string hash = sha256(msg + std::to_string(nonce));
        std::string target = prepareData();
        std::string c = hash.substr(0,target.length());
        std::cout << "hash: " << hash << ", target: " << target << ", nonce: " << nonce << std::endl;
        if (target == c) {
            std::chrono::milliseconds endMs = std::chrono::duration_cast< std::chrono::milliseconds >(
                std::chrono::system_clock::now().time_since_epoch()
            );
            long tms = endMs.count() - beginMs.count();
            float ts = tms/1000;
            std::cout << "test end time: " << endMs.count() << ", spend: " << tms << "(ms), " << ts << "(s)" << std::endl;
            return 0;
        }
        nonce += 1;
    }
    std::cout << "test exit too long" << std::endl;
}
