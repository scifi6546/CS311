// cuber.h
// Glenn G. Chappell
// 2019-11-22
//
// For CS 311 Fall 2019
// Header for class Cuber
// There is no associated source file.
// For Project 8, Exercise B

#ifndef FILE_CUBER_H_INCLUDED
#define FILE_CUBER_H_INCLUDED


// class Cuber
// Class for function objects that return cubes of numbers.
// Usage:
//     Cuber c;
//     cout << c(3);    // Prints "27"
//     cout << c(1.5);  // Prints "3.375"
// Class invariants: None.
class Cuber {
public:
    // operator()
    // Takes a value k and returns its cube.
    // Requirements on types:
    //     Num must have binary operator* and copy ctor.
    // Pre:
    //     The cube of k must be representable as a value of the same
    //      type as k.
    // Throws what & when Num operations throw.
    // Strong Guarantee
    // Exception Neutral
    template<typename Num>
    Num operator()(const Num & k) const
    {
        return k * k * k;
    }

    // We use automatically generated default ctor & Big 5.
    Cuber() = default;
    ~Cuber() = default;
    Cuber(const Cuber &) = default;
    Cuber(Cuber &&) = default;
    Cuber & operator=(const Cuber &) = default;
    Cuber & operator=(Cuber &&) = default;
};  // End class Cuber


#endif //#ifndef FILE_CUBER_H_INCLUDED

