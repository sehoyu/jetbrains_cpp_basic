#ifndef CPPBASICS_DATAPAIR_HPP
#define CPPBASICS_DATAPAIR_HPP

template <typename T1, typename T2>
class DataPair {
public:
    DataPair(): first(T1()), second(T2())
    {}

    DataPair(T1 firstArg, T2 secondArg): first(firstArg), second(secondArg)
    {}

    T1 getFirst() {
        return first;
    }

    T2 getSecond() {
        return second;
    }

    void setFirst(T1 firstArg) {
        first = firstArg;
    }
    void setSecond(T2 secondArg) {
        second = secondArg;
    }

private:
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
DataPair<T1, T2> makePair(T1 firstArg, T2 secondArg) {
    return DataPair<T1, T2>(firstArg, secondArg);
}

#endif //CPPBASICS_DATAPAIR_HPP
