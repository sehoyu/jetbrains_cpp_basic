#include <iostream>

#include "../include/book.hpp"

void newAndDeleteBook() {
    // Create and delete Book object using new/delete
    Book* book = new Book("c++ basics");
    delete book;
}

void mallocAndFreeBook() {
    // Do the same using malloc/free
    Book* book = (Book*) malloc(sizeof(Book));
    free(book);
}

int main() {
    newAndDeleteBook();
    mallocAndFreeBook();
    return 0;
}