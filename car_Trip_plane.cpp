#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <queue>
#include <chrono>
#include <random>
#include <string>

std::mutex mtx;

// Shared data
struct CarStatus {
    double speed;     // km/h
    int rpm;          // revolutions per minute
    double mileage;   // km/l
} car;

bool running = true;

// Simulate car sensor readings
void sensorSimulation(std::vector<double> &speedLog) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> speedDist(40, 120); // km/h
    std::uniform_int_distribution<> rpmDist(1000, 5000); // rpm
    std::uniform_real_distribution<> mileageDist(10, 18); // km/l

    while (running) {
        std::lock_guard<std::mutex> lock(mtx);
        car.speed = speedDist(gen);
        car.rpm = rpmDist(gen);
        car.mileage = mileageDist(gen);
        speedLog.push_back(car.speed);

        std::cout << "[Sensor] Speed: " << car.speed 
                  << " km/h, RPM: " << car.rpm 
                  << ", Mileage: " << car.mileage << " km/l\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Trip planner
void tripPlanner(std::queue<std::string> &waypoints, std::map<std::string, double> &distances) {
    while (running && !waypoints.empty()) {
        std::string nextStop;
        {
            std::lock_guard<std::mutex> lock(mtx);
            nextStop = waypoints.front();
            waypoints.pop();
        }

        double dist = distances[nextStop];
        double eta;
        {
            std::lock_guard<std::mutex> lock(mtx);
            eta = dist / (car.speed > 0 ? car.speed : 1); // hours
        }

        std::cout << "[Trip] Next stop: " << nextStop 
                  << ", Distance: " << dist << " km, ETA: " << eta * 60 << " minutes\n";

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main() {
    std::vector<double> speedHistory;          // STL vector to store speed logs
    std::queue<std::string> waypoints;         // STL queue for trip stops
    std::map<std::string, double> distances;   // STL map for stop distances

    // Sample trip plan
    waypoints.push("City A");
    distances["City A"] = 50;
    waypoints.push("City B");
    distances["City B"] = 120;
    waypoints.push("City C");
    distances["City C"] = 200;

    // Launch threads
    std::thread t1(sensorSimulation, std::ref(speedHistory));
    std::thread t2(tripPlanner, std::ref(waypoints), std::ref(distances));

    // Let simulation run for 15 seconds
    std::this_thread::sleep_for(std::chrono::seconds(15));
    running = false;

    t1.join();
    t2.join();

    // Show collected speed history
    std::cout << "\n--- Speed History ---\n";
    for (double s : speedHistory) {
        std::cout << s << " km/h\n";
    }

    return 0;
}
