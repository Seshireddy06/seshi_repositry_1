#include<iostream>
#include<list>
#include<vector>
#include<memory>
#include<thread>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
using namespace std;

class User {
    public:
    int id;
    std::string name;
    int age;
    float weight, height;
    User(int id,string name,int age,float weight,float height):id(id),name(name),age(age),weight(weight),height(height){
    }
    
    void display() const{
        cout<<endl<<"id: "<<id<<endl<<"name: "<<name<<endl<<"Age: "<<age<<endl<<"weight: "<<weight<<" ,"<<height<<endl;
    }
    
};
class Activity {
public:
    virtual float calculateCalories() const = 0;
    string getType() const { return type; }
    int getDuration() const { return duration; }
    string getTimestamp() const { return timestamp; }
 
protected:
    string type;
    int duration;
    string timestamp;
};
class Walking : public Activity { 
    public:
    Walking(int duration,float weight){
       
        this->duration=duration;
        this->weight=weight;
    }
    float calculateCalories() const override {
        
        return weight * duration * 3.5;
    }
    private:
    float weight;
};
class Running : public Activity { 
 public:
    Running(int duration,float weight){
        this->duration=duration;
        this->weight=weight;
    }
    float calculateCalories() const override {
        return weight * duration * 8.3;
    }
    private:
    float weight;
};
class Cycling : public Activity { 
    public:
    Cycling(int duration,float weight){
        this->duration=duration;
        this->weight=weight;
    }
    float calculateCalories() const override {
        int km;
        cout<<"enter kilometers : ";
        cin>>km;
        if(km<=8){
            return weight * duration * 6.8;
        }
        else{
            return weight * duration * 10;
        }
    }
    private:
    float weight;
};
class calorieTracker{
    public:
    vector<User> users;
    void addUser(const User& user){
      users.push_back(user);
      cout<<"New user added: ";
  } 
  void show(){
      for(const auto& i: users){
          i.display();
      }
  }
};
int main(){
    int id,age;
    string name;
    float weight,height;
    calorieTracker c;
    cout<<"Enter user id: ";
    
    cin>>id;
    cout<<"\nEnter user name: ";
    cin>>name;
    cout<<"\nEnter user age: ";
    cin>>age;
    cout<<"\nEnter user wight";
    cin>>weight;
    cout<<"\nEnter user height: ";
    cin>>height;
    User u(id,name,age,weight,height);
    c.addUser(u);
    c.show();
    Walking w(19,weight);
    cout<<"Calories burned by the  "<<name<<" : "<<w.calculateCalories();
    return 0;
}