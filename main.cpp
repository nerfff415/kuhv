// АиСД-2, 2023, задание 5
// Безруков Михаил БПИ214
// Среда разработки - Visual Studio Code
// Сделано все, кроме условия Айверсона 2

#include <iostream>
#include "sorts.h"
#include <chrono>
#include "rnd.h"
#include <fstream>
#include <cstdlib>
#include "exceptions.h"

void refillVectors(std::vector<std::vector < int> *

> working,
std::vector <std::vector<int>> standard,
int size
)
{
for (
int i = 0;
i<working.

size();

++i)
{
working.
at(i)
->

clear();

}
for (
int i = 0;
i<size;
++i)
{
working.at(0)->
emplace_back(standard
.at(0).
at(i)
);
working.at(1)->
emplace_back(standard
.at(1).
at(i)
);
working.at(2)->
emplace_back(standard
.at(2).
at(i)
);
working.at(3)->
emplace_back(standard
.at(3).
at(i)
);
}
}

bool isSorted(std::vector<int> *vector) {
    for (int i = 0; i < vector->size() - 1; ++i) {
        if (vector->at(i) > vector->at(i + 1)) {
            return false;
        }
    }
    return true;
}

void doIterations(const std::vector<int> &standard_small, const std::vector<int> &standard_big,
                  const std::vector<int> &standard_almost, const std::vector<int> &standard_reversed,
                  std::ofstream &ofst, std::ofstream &ofst2, int start, int stop, int step) {
    std::vector<int> working_small, working_big, working_almost, working_reversed;
    std::vector < std::vector < int > * > working_vectors = {&working_small, &working_big, &working_almost,
                                                             &working_reversed};
    std::ofstream output("output.txt");
    for (int i = start; i <= stop; i += step) {
        int ops = 0;
        ofst << i;
        ofst2 << i;
        output << "Векторы, отсортированные выбором:" << std::endl;
        // Сортируем разные векторы выбором
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = selectionSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные пузырьком:" << std::endl;
        // Сортируем пузырьком
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = bubbleSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные пузырьком с айверсоном 1:" << std::endl;
        // Сортируем пузырьком с айверсоном.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = bubbleSortAiveson(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные простыми вставками:" << std::endl;
        // Сортируем простыми вставками.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = insertionSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные бинарными вставками:" << std::endl;
        // Сортируем бинарными вставками.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = insertionSortBinary(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные подсчетом:" << std::endl;
        // Сортируем подсчетом.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = countSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные цифровой:" << std::endl;
        // Сортируем цифровой.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = radixSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные слиянием:" << std::endl;
        // Сортируем слиянием.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = mergeSort(working_vectors.at(j), 0, working_vectors.at(j)->size() - 1);
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные быстрой:" << std::endl;
        // Сортируем быстрой разб Хоара.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = quickSort(working_vectors.at(j), 0, working_vectors.at(j)->size() - 1);
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
            ofst2 << ";" << ops;
        }

        output << "Векторы, отсортированные пирамидальной:" << std::endl;
        // Сортируем пирамидальной.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = heapSort(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst2 << ";" << ops;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
        }

        output << "Векторы, отсортированные Шелла Циура:" << std::endl;
        // Сортируем пирамидальной.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = shellSortZiura(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst2 << ";" << ops;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
        }

        output << "Векторы, отсортированные Шелла Шелла:" << std::endl;
        // Сортируем пирамидальной.
        for (int j = 0; j < working_vectors.size(); ++j) {
            ops = 0;
            double times[5];
            for (int k = 0; k < 7; ++k) {
                refillVectors(working_vectors, {standard_small, standard_big, standard_almost, standard_reversed}, i);
                auto start = std::chrono::high_resolution_clock::now();
                ops = shellSortShell(working_vectors.at(j), working_vectors.at(j)->size());
                auto end = std::chrono::high_resolution_clock::now();
                if (!isSorted(working_vectors.at(j))) {
                    throw unsortedException("vector is unsorted");
                }
                if (k > 1) {
                    times[k - 2] =
                            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
                }
            }
            for (int k = 0; k < i; ++k) {
                output << working_vectors.at(j)->at(k) << " ";
            }
            output << std::endl;
            ofst2 << ";" << ops;
            ofst << ";" << (times[0] + times[1] + times[2] + times[3] + times[4]) / 5;
        }
        ofst << std::endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<int> standard_small, standard_big, standard_almost, standard_reversed;

    // Заполняем эталонные массивы.
    for (int i = 0; i < 4100; ++i) {
        standard_small.emplace_back(random(0, 5));
        standard_big.emplace_back(random(0, 4000));
        if (i != 0 && i % 500 == 0) {
            standard_almost.emplace_back(i);
            std::swap(standard_almost.at(i - 1), standard_almost.at(i));
        } else {
            standard_almost.emplace_back(i);
        }
        standard_reversed.emplace_back(std::abs(4100 - i));
    }

    std::ofstream ofst1("../result300.csv");
    ofst1.setf(std::ios::fixed);
    std::ofstream ofst3("../result300op.csv");
    ofst3.setf(std::ios::fixed);
    // Вводим заголовок в файл.
    std::vector <std::string> sort_names = {"Выбором", "Пузырьком", "Пузырьком с Айверсоном 1", "Простыми вставками",
                                            "Бинарными вставками", "Подсчетом", "Цифровая", "Слиянием",
                                            "Быстрой", "Пирамидальной", "Шелла Циура", "Шелла Шелла"};
    std::vector <std::string> array_types = {", случайные значения от 0 до 5", ", случайные значения от 0 до 4000",
                                             ", почти отсортированный", ", в обратном порядке"};
    ofst1 << "Размер массива";
    ofst3 << "Размер массива";
    for (auto &sort_name: sort_names) {
        for (auto &array_type: array_types) {
            ofst3 << ";" << sort_name << array_type;
            ofst1 << ";" << sort_name << array_type;
        }
    }
    ofst3 << std::endl;
    ofst1 << std::endl;

    // Заполняем csv данными
    doIterations(standard_small, standard_big, standard_almost, standard_reversed, ofst1, ofst3, 50, 300, 10);

    std::ofstream ofst2("../result4100.csv");
    ofst2.setf(std::ios::fixed);
    std::ofstream ofst4("../result4100op.csv");
    ofst4.setf(std::ios::fixed);
    ofst4 << "Размер массива";
    ofst2 << "Размер массива";
    for (auto &sort_name: sort_names) {
        for (auto &array_type: array_types) {
            ofst4 << ";" << sort_name << array_type;
            ofst2 << ";" << sort_name << array_type;
        }
    }
    ofst4 << std::endl;
    ofst2 << std::endl;
    doIterations(standard_small, standard_big, standard_almost, standard_reversed, ofst2, ofst4, 100, 4100, 100);
    ofst4.close();
    ofst3.close();
    ofst2.close();
    ofst1.close();
    std::ofstream input("input.txt");
    input << "Числа до 5:" << std::endl;
    for (int i = 0; i < 4100; ++i) {
        input << standard_small.at(i) << " ";
    }
    input << std::endl
          << "Случайные числа до 4000: " << std::endl;
    for (int i = 0; i < 4100; ++i) {
        input << standard_big.at(i) << " ";
    }
    input << std::endl
          << "Почти отсортированный вектор: " << std::endl;
    for (int i = 0; i < 4100; ++i) {
        input << standard_almost.at(i) << " ";
    }
    input << std::endl
          << "В обратном порядке: " << std::endl;
    for (int i = 0; i < 4100; ++i) {
        input << standard_reversed.at(i) << " ";
    }
    input.close();
    return 0;
}
