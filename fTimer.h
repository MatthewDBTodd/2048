#include <ctime>
#include <string>
#include <map>
#include <iostream>

struct fTimer {
    std::string fName;
    std::clock_t fStartTime;
    static std::map<std::string, std::pair<double, long>> fTimes;

    fTimer(const char* name) : fName{name}, fStartTime{clock()} {} 
    ~fTimer() {
        long total {clock() - fStartTime};
        long persec {CLOCKS_PER_SEC};
        double tinsec {static_cast<double>(total) / persec};
        fTimes[fName].first += tinsec;
        fTimes[fName].second += 1;
    }

    static void report() {
        std::cout << "\n==============================================\n";
        int totalTime {0};
        for (const auto& entry : fTimes) {
            std::cout << "\n----";
            double avg {entry.second.first / entry.second.second};
            std::cout << entry.first << ": " << "\nTimes called: " << 
            entry.second.second << 
            "\nTotal time: " << entry.second.first <<
            "\nAverage time: " << avg << '\n'; 
            std::cout << "----";
            totalTime += entry.second.first;
        }
        std::cout << "\n\nTotal time: " << totalTime << '\n';
        std::cout << "==============================================\n";
    }
};