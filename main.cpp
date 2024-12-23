#include <iostream>
#include <cstdlib> // Untuk fungsi rand() dan srand()
#include <ctime>   // Untuk fungsi time()
#include <chrono>  // Untuk pengukuran waktu

using namespace std;
using namespace std::chrono; // Untuk menggunakan chrono

//Anggota Kelompok:
//Syahrul Surya Ramadhan
//Justin Jeremia

struct Book {
    string title;
    string author;
    int year;
};

void generateRandomBooks(Book books[], int n) {
    for (int i = 0; i < n; i++) {
        books[i].title = "Judul " + to_string(i + 1);
        books[i].author = "Penulis " + to_string(i + 1);
        books[i].year = 1990 + rand() % 35; // Tahun antara 1990 dan 2024
    }
}

void insertionSort(Book books[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = books[i];
        int j = i - 1;
        while (j >= 0 && books[j].year > key.year) {
            books[j + 1] = books[j];
            j--;
        }
        books[j + 1] = key;
    }
}

void merge_sort_recursive(Book books[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_recursive(books, left, mid);
    merge_sort_recursive(books, mid + 1, right);

    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (books[i].year <= books[j].year) {
            i++;
        } else {
            Book temp = books[j];
            for (int k = j; k > i; k--) {
                books[k] = books[k - 1];
            }
            books[i] = temp;

            i++;
            mid++;
            j++;
        }
    }
}

void displayBooks(Book books[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Judul: " << books[i].title << ", Penulis: " << books[i].author << ", Tahun: " << books[i].year << endl;
    }
}

int main() {
    const int numBooks = 300; // Jumlah buku
    Book books[numBooks];

    srand(time(0)); // Seed untuk angka acak
    generateRandomBooks(books, numBooks);

    cout << "Data Buku Sebelum Pengurutan:" << endl;
    displayBooks(books, numBooks);

    // Mengukur waktu eksekusi Insertion Sort
    auto start = high_resolution_clock::now();
    insertionSort(books, numBooks);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "\nData Buku Setelah Pengurutan dengan Insertion Sort (berdasarkan Tahun):" << endl;
    displayBooks(books, numBooks);
    cout << "Waktu eksekusi Insertion Sort: " << duration.count() << " detik" << endl;

    // Mengukur waktu eksekusi Merge Sort
    start = high_resolution_clock::now();
    merge_sort_recursive(books, 0, numBooks - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<seconds>(stop - start);

    cout << "\nData Buku Setelah Pengurutan dengan Merge Sort (berdasarkan Tahun):" << endl;
    displayBooks(books, numBooks);
    cout << "Waktu eksekusi Merge Sort: " << duration.count() << " detik" << endl;

    return 0;
}
