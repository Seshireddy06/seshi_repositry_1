#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>

class Car {
private:
    int car_id;
    std::string brand;
    std::string model;
    std::string owner;

public:
    // Constructor
    Car(int id, const std::string& b, const std::string& m, const std::string& o)
        : car_id(id), brand(b), model(m), owner(o) {}
    
    // Getters
    int getId() const { return car_id; }
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    std::string getOwner() const { return owner; }
    
    // String representation
    std::string toString() const {
        return "Car(ID: " + std::to_string(car_id) + 
               ", Brand: " + brand + 
               ", Model: " + model + 
               ", Owner: " + owner + ")";
    }
    
    // Overload < operator for set ordering
    bool operator<(const Car& other) const {
        if (car_id != other.car_id) return car_id < other.car_id;
        if (brand != other.brand) return brand < other.brand;
        if (model != other.model) return model < other.model;
        return owner < other.owner;
    }
    
    // Overload == operator for equality comparison
    bool operator==(const Car& other) const {
        return car_id == other.car_id && 
               brand == other.brand && 
               model == other.model && 
               owner == other.owner;
    }
};

// Function to print a set of cars
void printCarSet(const std::set<Car>& cars, const std::string& title) {
    std::cout << title << ":" << std::endl;
    if (cars.empty()) {
        std::cout << "  No cars in this category" << std::endl;
    } else {
        for (const auto& car : cars) {
            std::cout << "  " << car.toString() << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function to find cars by brand
std::set<Car> findCarsByBrand(const std::set<Car>& allCars, const std::string& brand) {
    std::set<Car> result;
    for (const auto& car : allCars) {
        if (car.getBrand() == brand) {
            result.insert(car);
        }
    }
    return result;
}

// Function to find cars by owner
std::set<Car> findCarsByOwner(const std::set<Car>& allCars, const std::string& owner) {
    std::set<Car> result;
    for (const auto& car : allCars) {
        if (car.getOwner() == owner) {
            result.insert(car);
        }
    }
    return result;
}

int main() {
    // Create car instances
    Car car1(1, "Toyota", "Camry", "John Doe");
    Car car2(2, "Honda", "Civic", "Jane Smith");
    Car car3(3, "Ford", "Mustang", "Bob Johnson");
    Car car4(4, "Toyota", "Corolla", "Alice Brown");
    Car car5(5, "BMW", "X5", "Charlie Wilson");
    
    // Create sets of cars
    std::set<Car> luxury_cars = {car5};  // BMW X5
    std::set<Car> family_cars = {car1, car4};  // Toyota Camry and Corolla
    std::set<Car> sport_cars = {car3};  // Ford Mustang
    std::set<Car> all_cars = {car1, car2, car3, car4, car5};
    
    std::cout << "=== Car Management System (C++) ===" << std::endl;
    
    printCarSet(all_cars, "All Cars");
    printCarSet(luxury_cars, "Luxury Cars");
    printCarSet(family_cars, "Family Cars");
    printCarSet(sport_cars, "Sport Cars");
    
    // Set operations
    std::cout << "=== Set Operations ===" << std::endl;
    
    // Union of family and sport cars
    std::set<Car> family_or_sport;
    std::set_union(family_cars.begin(), family_cars.end(),
                   sport_cars.begin(), sport_cars.end(),
                   std::inserter(family_or_sport, family_or_sport.begin()));
    printCarSet(family_or_sport, "Family or Sport Cars");
    
    // Intersection of luxury and family cars (should be empty)
    std::set<Car> luxury_and_family;
    std::set_intersection(luxury_cars.begin(), luxury_cars.end(),
                         family_cars.begin(), family_cars.end(),
                         std::inserter(luxury_and_family, luxury_and_family.begin()));
    printCarSet(luxury_and_family, "Luxury and Family Cars (intersection)");
    
    // Difference: cars that are not luxury
    std::set<Car> non_luxury_cars;
    std::set_difference(all_cars.begin(), all_cars.end(),
                       luxury_cars.begin(), luxury_cars.end(),
                       std::inserter(non_luxury_cars, non_luxury_cars.begin()));
    printCarSet(non_luxury_cars, "Non-Luxury Cars");
    
    // Find cars by brand
    std::set<Car> toyota_cars = findCarsByBrand(all_cars, "Toyota");
    printCarSet(toyota_cars, "Toyota Cars");
    
    // Find cars by owner
    std::set<Car> johns_cars = findCarsByOwner(all_cars, "John Doe");
    printCarSet(johns_cars, "John Doe's Cars");
    
    // Additional set operations
    std::cout << "=== Additional Set Operations ===" << std::endl;
    
    // Check if a car exists in a set
    Car searchCar(1, "Toyota", "Camry", "John Doe");
    if (all_cars.find(searchCar) != all_cars.end()) {
        std::cout << "Car found in all_cars set!" << std::endl;
    }
    
    // Count cars in different categories
    std::cout << "Number of luxury cars: " << luxury_cars.size() << std::endl;
    std::cout << "Number of family cars: " << family_cars.size() << std::endl;
    std::cout << "Number of sport cars: " << sport_cars.size() << std::endl;
    std::cout << "Total number of cars: " << all_cars.size() << std::endl;
    
    return 0;
} 