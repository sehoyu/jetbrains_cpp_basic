#ifndef CPPBASICS_DATAPAIR_HPP
#define CPPBASICS_DATAPAIR_HPP

#include <iostream>
#include <type_traits>

template <typename T1, typename T2>
class DataPair {
private:
    T1 first;
    T2 second;

public:
    DataPair() : first(T1()), second(T2()) {}
    DataPair(T1 first, T2 second) : first(first), second(second) {}

    T1 getFirst() const {
        return first;
    }

    T2 getSecond() const {
        return second;
    }

    void setFirst(T1 value) {
        first = value;
    }

    void setSecond(T2 value) {
        second = value;
    }
};

template <typename T1, typename T2>
void printDataPair(DataPair<T1, T2> data) {
    if constexpr (std::is_same_v<T1, T2>) {
        std::string typeName;
        if constexpr (std::is_same_v<T1, int>) {
            typeName = "int";
        } else if constexpr (std::is_same_v<T1, double>) {
            typeName = "double";
        } else if constexpr (std::is_same_v<T1, std::string>) {
            typeName = "std::string";
        } else {
            typeName = "";
        }
        if (!typeName.empty()) {
            std::cout << typeName << " ";
        }
    }

    std::cout << "DataPair: " << data.getFirst() << ", " << data.getSecond() << std::endl;

}
#endif //CPPBASICS_DATAPAIR_HPP
