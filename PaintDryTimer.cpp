#include <iostream>
#include <vector>
#include <ctime>        // for time(0)
#include <cstdlib>      // for rand(), srand()
#include <cmath>        // for M_PI (PI constant) if available
#include <iomanip>      // for std::setw, std::setfill
#include "TimeCode.h"   // TimeCode class interface

// Structure to hold information about a paint drying batch
struct Batch {
    int id;                       // unique batch ID
    time_t startTime;             // timestamp when batch was added
    TimeCode* totalTime;          // pointer to TimeCode for total drying time (allocated on heap)
};

// Helper function to compute drying time in seconds given radius
unsigned long long computeDryingSeconds(double radius) {
    const double PI = 3.141592653589793;
    double secondsDouble = 4 * PI * radius * radius;
    if (secondsDouble < 0) secondsDouble = 0;  // ensure non-negative
    return static_cast<unsigned long long>(secondsDouble);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));  // seed random number generator for batch IDs
    std::vector<Batch> batches;
    char choice;

    while (true) {
        std::cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        std::cin >> choice;
        if (!std::cin) break;  // Input stream error (EOF)

        choice = std::toupper(choice);

        if (choice == 'A') {
            std::cout << "        radius: ";
            double radius;
            std::cin >> radius;
            if (!std::cin || radius <= 0) {
                std::cerr << "Invalid radius. Please enter a positive number.\n";
                continue;
            }

            // Compute drying time
            unsigned long long totalSec = computeDryingSeconds(radius);
            int hrs = totalSec / 3600;
            int mins = (totalSec % 3600) / 60;
            int secs = totalSec % 60;
            TimeCode* tc = new TimeCode(hrs, mins, secs);

            int batchID = std::rand();
            Batch newBatch = { batchID, std::time(0), tc };
            batches.push_back(newBatch);

            // Display properly formatted drying time
            std::cout << "        Batch-" << batchID 
                      << " (takes " 
                      << std::setw(2) << std::setfill('0') << tc->GetHours() << ":"
                      << std::setw(2) << std::setfill('0') << tc->GetMinutes() << ":"
                      << std::setw(2) << std::setfill('0') << tc->GetSeconds() 
                      << " to dry) time remaining: "
                      << std::setw(2) << std::setfill('0') << tc->GetHours() << ":"
                      << std::setw(2) << std::setfill('0') << tc->GetMinutes() << ":"
                      << std::setw(2) << std::setfill('0') << tc->GetSeconds()
                      << std::endl;
        }
        else if (choice == 'V') {
            if (batches.empty()) {
                std::cout << "        (No drying batches currently tracked.)" << std::endl;
                continue;
            }

            time_t now = std::time(0);
            for (auto it = batches.begin(); it != batches.end();) {
                time_t elapsed = now - it->startTime;
                unsigned long long totalSec = it->totalTime->GetTimeCodeAsSeconds();
                
                if (elapsed >= static_cast<time_t>(totalSec)) {
                    delete it->totalTime;
                    it = batches.erase(it);
                } else {
                    ++it;
                }
            }

            for (const Batch& batch : batches) {
                time_t elapsed = now - batch.startTime;
                unsigned long long totalSec = batch.totalTime->GetTimeCodeAsSeconds();
                long long remainSec = static_cast<long long>(totalSec) - static_cast<long long>(elapsed);
                if (remainSec < 0) remainSec = 0;

                int remH = remainSec / 3600;
                int remM = (remainSec % 3600) / 60;
                int remS = remainSec % 60;
                TimeCode remainTime(remH, remM, remS);

                std::cout << "        Batch-" << batch.id
                          << " (takes " 
                          << std::setw(2) << std::setfill('0') << batch.totalTime->GetHours() << ":"
                          << std::setw(2) << std::setfill('0') << batch.totalTime->GetMinutes() << ":"
                          << std::setw(2) << std::setfill('0') << batch.totalTime->GetSeconds()
                          << " to dry) time remaining: "
                          << std::setw(2) << std::setfill('0') << remainTime.GetHours() << ":"
                          << std::setw(2) << std::setfill('0') << remainTime.GetMinutes() << ":"
                          << std::setw(2) << std::setfill('0') << remainTime.GetSeconds()
                          << std::endl;
            }
        }
        else if (choice == 'Q') {
            break;
        }
        else {
            std::cout << "        Invalid option. Please enter A, V, or Q." << std::endl;
        }
    }

    for (Batch& batch : batches) {
        delete batch.totalTime;
        batch.totalTime = nullptr;
    }
    return 0;
}
