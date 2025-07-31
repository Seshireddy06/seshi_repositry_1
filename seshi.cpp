
#include <iostream>
#include <string>   
class Student {
public:
    std::string name;
    int age;
    std::string familyName;

    Student(const std::string& name, int age, const std::string& familyName)
        : name(name), age(age), familyName(familyName) {}
};  
//write main function to test the Student class
int main() {
    Student student("John", 20, "Doe");
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "Age: " << student.age << std::endl;
    std::cout << "Family Name: " << student.familyName << std::endl;
    return 0;
}
