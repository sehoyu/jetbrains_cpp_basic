bool pointToSameValue(int* a, int* b) {
    // if (a && b) {
    //     return *a == *b;
    // } else if (!a && !b) {
    //     return true;
    // } else {
    //     return false;
    // }

    if (a == b) {
        return true;
    }

    if (!a || !b) {
        return false;
    }

    return *a == *b;
}
