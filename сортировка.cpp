#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // для rand() и srand()
#include <ctime>    // для time()
#include <iomanip>  // для setw и setprecision
#include <chrono>   // для измерения времени
#include <climits>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Прототипы функций сортировки
void bubbleSort(vector<double>& arr);
void insertionSort(vector<double>& arr);
void quickSort(vector<double>& arr, int low, int high);
void selectionSort(vector<double>& arr);
void mergeSort(vector<double>& arr, int left, int right);
void heapSort(vector<double>& arr);

// Вспомогательные функции
void printArray(const vector<double>& arr);
int getIntInput(const string& prompt, int min, int max);
double getDoubleInput(const string& prompt);
void initializeArray(vector<double>& arr);

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    vector<double> arr;
    bool arrayInitialized = false; // Для проверки того, создан ли массив

    while (true) {
        cout << "\nВыберите алгоритм сортировки:\n"
             << "1. Пузырьковая сортировка\n"
             << "2. Сортировка вставками\n"
             << "3. Быстрая сортировка\n"
             << "4. Сортировка выбором\n"
             << "5. Сортировка слиянием\n"
             << "6. Пирамидальная сортировка\n"
             << "7. Применить все алгоритмы сортировки\n"
             << "0. Выход\n";

        int choice = getIntInput("Ваш выбор: ", 0, 7);
        if (choice == 0) break;

        if (!arrayInitialized) { // Если массив не был инициализирован
            initializeArray(arr); // Инициализируем массив
            arrayInitialized = true; // Ставим значение true тк массив теперь инициализирован
        }

        cout << "Исходный массив:\n";
        printArray(arr);

        if (choice == 7) {
            vector<string> algorithmNames = {
                    "Пузырьковая сортировка",
                    "Сортировка вставками",
                    "Быстрая сортировка",
                    "Сортировка выбором",
                    "Сортировка слиянием",
                    "Пирамидальная сортировка"
            };

            vector<double> times(6); // Для хранения времени выполнения каждого алгоритма
            vector<double> originalArr = arr; //Копия исходного массива
            vector<double> sortedArr; // Для хранения отсортированного массива

            for (int i = 0; i < 6; ++i) {
                vector<double> arrCopy = originalArr; // Создаем копию исходного массива для каждого метода
                auto start = chrono::high_resolution_clock::now(); // Фиксируем время начала сортировки

                switch (i + 1) {
                    case 1: bubbleSort(arrCopy); break;
                    case 2: insertionSort(arrCopy); break;
                    case 3: quickSort(arrCopy, 0, arrCopy.size() - 1); break;
                    case 4: selectionSort(arrCopy); break;
                    case 5: mergeSort(arrCopy, 0, arrCopy.size() - 1); break;
                    case 6: heapSort(arrCopy); break;
                }

                auto end = chrono::high_resolution_clock::now(); // Фиксираем время конца сортировки
                chrono::duration<double, milli> elapsed = end - start; // Вычисляем время выполнения алгоритма в миллисекундах
                times[i] = elapsed.count(); // Сохраняем время выполнения алгоритма

                if (i == 0) sortedArr = arrCopy; // Сохраняем результат первой сортировки для дальнейшего вывода
            }

            cout << "Отсортированный массив:\n";
            printArray(sortedArr);

            cout << "\nРезультаты сортировки:\n";
            for (int i = 0; i < 6; ++i) { // Для каждого алгоритма выводим время его выполнения
                cout << algorithmNames[i] << ": " << fixed << setprecision(5)
                     << times[i] << " мс\n";
            }

        }
        else {
            vector<double> arrCopy = arr; // Создаем копию исходного массива
            auto start = chrono::high_resolution_clock::now(); // Фиксируем время начала работы алгоритма

            switch (choice) { // Выбираем алгоритм на основе введенной цифры
                case 1: bubbleSort(arrCopy); break;
                case 2: insertionSort(arrCopy); break;
                case 3: quickSort(arrCopy, 0, arrCopy.size() - 1); break;
                case 4: selectionSort(arrCopy); break;
                case 5: mergeSort(arrCopy, 0, arrCopy.size() - 1); break;
                case 6: heapSort(arrCopy); break;
            }

            auto end = chrono::high_resolution_clock::now(); // Фиксируем время окончания работы алгоритма
            chrono::duration<double, milli> elapsed = end - start;// Вычисляем время работы алгоритма в миллисекундах

            cout << "Отсортированный массив:\n";
            printArray(arrCopy);

            cout << "Алгоритм сортировки выполнился за " << fixed << setprecision(3)
                 << elapsed.count() << " миллисекунд.\n";
        }

        cout << "Что вы хотите сделать дальше?\n"
             << "1. Сохранить существующий массив\n"
             << "2. Ввести новый массив\n"
             << "3. Завершить программу\n";

        int next_action = getIntInput("Ваш выбор: ", 1, 3);
        if (next_action == 2) arrayInitialized = false; // Пользователя заново попросят создать массив
        else if (next_action == 3) break;
    }

    return 0;
}

// Функция для проверки ввода целых чисел
int getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input); // Считываем строку ввода пользователя
        try {
            value = stoi(input); // Пытаемся преобразовать строку input в целое число
            if (value >= min && value <= max) break; // Если преобразование успешно и число в заданном диапазоне, выходим из цикла
            else cout << "Введите число от " << min << " до " << max << ".\n";
        } catch (...) {
            cout << "Введены неверные данные. Попробуйте еще раз.\n";
        }
    }
    return value;
}

// Функция для проверки ввода дробных чисел
double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        try {
            value = stod(input); // Пытаемся преобразовать строку в double
            break;
        } catch (...) {
            cout << "Введены неверные данные. Попробуйте еще раз.\n";
        }
    }
    return value;
}

// Инициализация массива
void initializeArray(vector<double>& arr) {
    int size = getIntInput("Введите размер массива: ", 1, INT_MAX);

    cout << "Выберите способ заполнения массива:\n"
         << "1. Заполнить случайными числами\n"
         << "2. Ввести числа вручную\n";

    int fill_choice = getIntInput("Ваш выбор: ", 1, 2);

    arr.resize(size); // Задаем массиву размер, указанный пользователем

    if (fill_choice == 1) {
        srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
        for (int i = 0; i < size; i++) {
            arr[i] = ((double)rand() / RAND_MAX) * 20000 - 10000; // от -10000 до 10000
        }
    }
    else {
        cout << "Введите " << size << " чисел:\n";
        for (int i = 0; i < size; i++) {
            arr[i] = getDoubleInput("Элемент " + to_string(i) + ": ");
        }
    }
}

// Вывод массива
void printArray(const vector<double>& arr) {
    cout << "+-------+----------------------+\n";
    cout << "| Index |        Value         |\n";
    cout << "+-------+----------------------+\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << "| " << setw(5) << i << " | " << setw(20) << arr[i] << " |\n";
    }
    cout << "+-------+----------------------+\n";
}

// Пузырьковая сортировка
void bubbleSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // Меняем местами элементы
            }
        }
    }
}

// Сортировка вставками
void insertionSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        double key = arr[i]; // Запоминаем текущий элемент
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { // Пока элементы слева больше текущего
            arr[j + 1] = arr[j]; // Сдвигаем элемент вправо
            j--;
        }
        arr[j + 1] = key; // Вставляем текущий элемент на правильное место
    }
}

// Быстрая сортировка
int partition(vector<double>& arr, int low, int high) {
    double pivot = arr[high]; // Опорный элемент
    int i = low - 1; // Индекс меньшего элемента
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) { // Если текущий элемент меньше опорного
            i++;
            swap(arr[i], arr[j]); // Меняем местами
        }
    }
    swap(arr[i + 1], arr[high]); // Ставим опорный элемент на правильное место
    return i + 1;
}

void quickSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Индекс разделения
        quickSort(arr, low, pi - 1); // Сортируем левую часть
        quickSort(arr, pi + 1, high); // Сортируем правую часть
    }
}

// Сортировка выбором
void selectionSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i; // Индекс минимального элемента
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j; // Находим минимальный элемент
        }
        swap(arr[min_idx], arr[i]); // Меняем местами с текущим
    }
}

// Сортировка слиянием
void merge(vector<double>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Размер левой части
    int n2 = right - mid;    // Размер правой части

    vector<double> L(n1), R(n2); // Временные массивы

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i]; // Копируем данные в левый массив
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j]; // Копируем данные в правый массив

    int i = 0, j = 0, k = left; // Индексы для перебора

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // Берем элемент из левого массива
            i++;
        } else {
            arr[k] = R[j]; // Берем элемент из правого массива
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы, если есть
    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }
}

void mergeSort(vector<double>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Находим середину
        mergeSort(arr, left, mid);           // Сортируем первую половину
        mergeSort(arr, mid + 1, right);      // Сортируем вторую половину
        merge(arr, left, mid, right);        // Сливаем отсортированные половины
    }
}

// Пирамидальная сортировка
void heapify(vector<double>& arr, int n, int i) {
    int largest = i;    // Инициализируем наибольший как корень
    int l = 2 * i + 1;  // Левый = 2*i + 1
    int r = 2 * i + 2;  // Правый = 2*i + 2

    if (l < n && arr[l] > arr[largest])
        largest = l; // Левый потомок больше корня
    if (r < n && arr[r] > arr[largest])
        largest = r; // Правый потомок больше корня

    if (largest != i) { // Если наибольший не корень
        swap(arr[i], arr[largest]); // Меняем местами
        heapify(arr, n, largest);   // Рекурсивно преобразуем в пирамиду затронутое поддерево
    }
}

void heapSort(vector<double>& arr) {
    int n = arr.size();

    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]); // Перемещаем текущий корень в конец
        heapify(arr, i, 0);   // Вызываем heapify на уменьшенной куче
    }
}
