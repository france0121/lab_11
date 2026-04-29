#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Функция вывода вектора
void printVector(const string& name, const vector<int>& vec) {
    cout << name << " (размер: " << vec.size() << "): ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    int N;
    cout << "Введите количество элементов N: ";
    cin >> N;
    
    // 1. Создаём вектор и заполняем случайными числами
    vector<int> original;
    for (int i = 0; i < N; i++) {
        original.push_back(rand() % 201 - 100); // числа от -100 до 100
    }
    printVector("Исходный вектор", original);
    
    // 2. Проверяем: есть ли и чётные, и нечётные числа
    bool hasEven = false;
    bool hasOdd = false;
    
    for (int val : original) {
        if (val % 2 == 0) hasEven = true;
        else hasOdd = true;
    }
    
    // 3. Если нет и тех, и других — выводим сообщение и завершаем
    if (!hasEven || !hasOdd) {
        cout << "\nУсловие не выполнено: в векторе нет одновременно чётных и нечётных чисел." << endl;
        return 0;
    }
    
    // 4. Находим x — значение последнего нечётного числа
    int x = 0;
    for (int i = original.size() - 1; i >= 0; i--) {
        if (original[i] % 2 != 0) {
            x = original[i];
            break;
        }
    }
    
    cout << "\nПоследнее нечётное число (x) = " << x << endl;
    
    // 5. Создаём новый вектор из чётных чисел, уменьшенных на x
    vector<int> newVector;
    for (int val : original) {
        if (val % 2 == 0) {
            newVector.push_back(val - x);
        }
    }
    
    // 6. Выводим результат
    printVector("Новый вектор (чётные - x)", newVector);
    
    return 0;
}
