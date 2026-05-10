#include <concepts>
#include <stdint.h>

template<typename T>
concept con = requires (T t) {
    t + t;
    t - t;
    t * t;
    t / t;
    t = t;
    t == t;
    requires std::constructible_from<T, int>;
};

class Hello {
public:
    Hello ();
    Hello (int);
    Hello& operator* (const Hello&) { return *this; }; 
    Hello& operator+ (const Hello&) { return *this; }; 
    Hello& operator/ (const Hello&) { return *this; }; 
    Hello& operator- (const Hello&) { return *this; }; 
    bool operator= (const Hello&) const {return true; }; 
    bool operator== (const Hello&) const {return true; }; 
};

template<con T>
class Bye {
    T a;
public:
    Bye (int r) { this->a = r; };
    ~Bye () = default; 
};

int main () {
    Bye a{Bye<Hello>(1)};
    Bye b{Bye<int>(1)};
    Bye c{Bye<int64_t>(1)};
    Bye d{Bye<double>(1)};
    Bye e{Bye<float>(1)};
    return 0;
}
