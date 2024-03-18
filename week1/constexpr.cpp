/*
Constexpr

C++ 11
    - single return statement only
    - constexpr members imply const
    - non-virtual members
    - no switching or branching

    except for ternary operator
    almost turing complete
    all types must be literal types

C++ 14

    - multiple statements allowed
    - constexpr members do not imply const
    - lambdas not yet

C++ 17
    - more stdlib support
    - lambda automatically constexpr if possible

C++ 20
    - constexpr dynamic allocation
    - (dynamic allocation cannot leave constexpr context)
    - constexpr destructors
    - constexpr vector
    - constexpr string
    - constexpr std algorithm
    
*/



/*
leanc++ 5.4 constatnt expressions and compile time optimization
https://www.learncpp.com/cpp-tutorial/constant-expressions-and-compile-time-optimization/

Constant expression:
    An expression that contains only compile-time constants and operators/functions that support compile-time evaluation
    Including
        - literals (e.g. 5, 3.14, 'a')
        - constexpr variables (5.5)
        - const integral variables with a constatn expression initializer (e.g. const int x {5};). This is a historical exception -- in modern C++, you should use constexpr instead of const for this purpose
        - non-type template parameters (11.9)
        - Enumerators (13.2)

Tips:
    const non-integral variables are always run-time constants, not compile-time constants. If you need such a variable to be a compile-time constant, you should use constexpr instead of const.


learnc++ 5.5 constexpr variables

    conpile-time const VS runtime-const
    - const: runtime const
    - constexpr: compile-time const
    - compile-time const more efficient than runtime const in runtime
    - runtime const more easy to debug since compiler may not optimize the code as much as compile-time const

int a { 5 };       // not const at all
const int b { a }; // obviously a runtime const (since initializer is non-const)
const int c { 5 }; // obviously a compile-time const (since initializer is a constant expression)

const int d { obj };        // not obvious whether this is a runtime or compile-time const
const int e { getValue() }; // not obvious whether this is a runtime or compile-time const

constexpr
    constant expression, must be initialized with a constant expression, otherwise compile-time error

constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not a constant expression  

in this exampel why f have compile issue? since five() is not defined as a constexpr function
fix
    constexpr int five() { return 5; }


Best practive
    - any const variable whose initializer is a cosnt expression should be declared as constexpr
    - any const variable whose initializer is not a constant expression should be declared as const



constexpr for function
    - constexpr func, only return a constant expression when inputs are constant expressions
    - even inputs are constant expressions, the function may not return a constant expression, it guarantees to generate a constant expression when it is asked to do so
Eg
constexpr int add(int x, int y) { return x + y; }
int main() {
    constexpr int a { 5 };
    constexpr int b { 6 };
    constexpr int c { add(a, b) }; // ok: add(a, b) is a constant expression
    int d { add(3, 4) };           // ok: add(3, 4) is may not be a constant expression, depending on the compiler decision
    return 0;
}




Tips:
    How to check whether a variable is a constant expression?
    std::static_asset(std::is_constant_expression_v<variable>, "variable is not a constant expression");
*/

/*
More Deeper
constexpr still not gurantee a variable is evaluated at compile-time, the compiler optimization may still evaluate the variable at runtime.
gcc is more aggressive in optimizing the code than llvm
I will not dig into this topic for now, Mar 2024


*/

constexpr int getvalue(int value) {
    return 3*value;
}
int main() {
    constexpr int a = 5;
    constexpr auto value = getvalue(42);
    constexpr static auto value = getvalue(42);
    return 0;
}