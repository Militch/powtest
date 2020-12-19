#include <iostream>
#include <string>
#include <chrono>
#include <climits>
#include <stdexcept>
#include "util/sha256.h"
#ifdef ISWIN
#include "win32/wingetopt.h"
#endif

static struct option const long_options[] = {
    {"difficulty", required_argument, NULL, 'd'}
};

void usage(){
    fprintf(stdout,
            "Usage: powtest [options...] <message>\n"
            "\n"
            "Options:\n"
            "  -d <number> POW difficulty of number\n"
            "  -v    Print package version\n"
            "  -h    Show version number and quit\n");
}

std::string prepareData(int len){
    std::string t;
    for (int i=0; i<len; i++) {
        t += "0";
    }
    return t;
}
int main(int argc, char **argv) {
    int opt;
    int difficulty_num;
    while ((opt = getopt(argc, argv, "d:vh")) != EOF) {
        switch (opt) {
            case 'd':
                try {
                    difficulty_num = std::stoi(std::string(optarg));
                }catch (std::invalid_argument iaex) {
                    usage();
                    return 0;
                }
                break;
            case 'h':
            default:
                usage();
                return 0;
        }
    }
    int argind = optind;
    std:: string message;
    if (argind < argc) {
        message = std::string(argv[argind]);
    }
    if (message.empty()){
        usage();
        return 0;
    }
    long nonce = 0;
    std::chrono::milliseconds beginMs = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::cout << "test begin time: " <<  beginMs.count() << std::endl;
    while (nonce < LONG_MAX) {
        std::string hash = sha256(message + std::to_string(nonce));
        std::string target = prepareData(difficulty_num);
        std::string c = hash.substr(0,target.length());
        // std::cout << "hash: " << hash << ", target: " << target << ", nonce: " << nonce << std::endl;
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
