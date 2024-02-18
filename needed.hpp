#ifndef __NeeCon_mod
#define __NeeCon_mod

#include <concepts>
#include <cstdint>

/* * * * * * * *
 *  Concepts  *
 * * * * * * * */

/* Encompass the types that supports arthmetric operations. */
template<typename _type> concept arithmetric = requires (_type Arth, int i) {
    Arth + Arth;                                    // addition 
    Arth += Arth;
    Arth - Arth;                                    // substraction 
    Arth -= Arth;
    Arth * Arth;                                    // multiplication 
    Arth *= Arth;
    Arth / Arth;                                    // division 
    Arth /= Arth;
    Arth == Arth;                                   // equal comparation
    Arth = Arth;                                    // asignation
    requires std::constructible_from<_type, int>;   // 1, -1, 0 needs to be convertible to _type
};

/* Fundamental arithmetric types. */
template<typename T> 
concept IntFloat = std::floating_point <T> || std::integral <T>;

/* Two expresions 'a' and 'b' are Multipliable if they have defined the * binary operation. */
template<typename _type>
concept Multipliable = requires(_type a){
    a * a;
};

/* 
    Two expresions 'a' and 'b' are Orderable if they define the ordered operations.
    (>, <, >=, <=, ==)
*/
template<typename _type>
concept Orderable = requires(_type a){
    a > a;
    a < a;
    a >= a;
    a >= a;
    a == a;
};


/* * * * * *
 *  Types  *
 * * * * * */

typedef uint32_t index;

#endif
