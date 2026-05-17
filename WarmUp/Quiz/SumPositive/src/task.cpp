// int sumPositive(int array[], int size) {
//     // if (size > 0) {
//     //     int sum = 0;
//     //     int count = 0;
//     //     for (int i = 0; i < size; i++) {
//     //         if (array[i] < 0) {
//     //             count += 1;
//     //         } else {
//     //             sum += array[i];
//     //         }
//     //     }
//     //
//     //     if (count < size) {
//     //         return sum;
//     //     }
//     // }
//     //
//     // return 0;
//     if (size > 0) {
//         int sum = 0;
//         for (int i = 0; i < size; i++) {
//             if (array[i] > 0) {
//                 sum += array[i];
//             }
//         }
//         return sum;
//     }
//
//     return 0;
// }

// int sumPositive(int array[], int size) {
//     if (size > 0) {
//         int sum = 0;
//         for (int i = 0; i < size; i++) {
//             if (array[i] > 0) {
//                 sum += array[i];
//             }
//         }
//         return sum;
//     }
//     return 0;
// }

int sumPositive(int array[], int size) {
    if (size <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > 0) {
            sum += array[i];
        }
    }

    return sum;
}