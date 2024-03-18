#include <iostream>
#include <memory>
/*
const
1. compile time constraint that an object can not be modified
2. SHOULD be initialized at the time of declaration
3. const int *p; // same as int const *p;
int main() {
    const int a = 5;
    // a = 6; // Error: assignment of read-only variable 'a'
    const int* b = new int(7);
    // const int* b1 = new int; // this is weird, but it's valid
    const int* const p1 = &a;
    int const *p2 = &a;
    return 0;
}
*/



/*
const_cast
Usage, when we want to remove the constness of a variable. 
Eg, thrid party library function which takes non-const argument, but we have const variable. We also know within the function the variable will not be modified.

Indeed the variable still should not be modified.


Not static_cast compile-time check

int main() {
    // const int a = 5;
    // const_cast<int&>(a) = 6;
    // printf("a: %d\n", a); // print out 5, since this is a undefined behavior
    int b = 7;

    // static_cast<const int&>(b) = 8; // compile time error, read-only variable is not assignable
    
    return 0;
}
*/



/*
constexpr
Force work at compile time


*/


/*
const used in function

Usage I    - const ref as argument
Usage II   - const return value
Usage III  - const member function
    - only call another const member function
    - only access member variable
    - can used to overload function

*/
class Dog {
    int age;
    std::string name;
public:
    // void setAge(const int newAge) { // this not make sense, since newAge is a copy of the argument, it do not make sense to make a copy of to a const variable
    void setAge(const int& newAge) {
        age = newAge;
        // newAge++; // error: increment of read-only reference 'newAge'
    }
    /*
    void setAge(const int newAge) {}
    void setAge(int newAge) {}
    From compiler perspective, these two are the same, since the argument is a copy of the original variable
     error: class member cannot be redeclared
    */


    // const return value
    const std::string& getName() {
        return name;
    }

    void printDogName() const {
        printf("name: %s\n", name.c_str());
        printf("age: %d\n", age);
    } // invoke when dog is const
    // this is a different function from the above one
    void printDogName() {
        printf("ABD\n");
    } // invoke when dog is not const
};
int main() {
    Dog d;
    int a = 9;
    d.setAge(a);
    printf("a: %d\n", a); // print out 10
    return 0;
}