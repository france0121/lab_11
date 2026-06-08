#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <algorithm>

using namespace std;

// ===================== ФУНКЦИИ ЗАДАНИЯ =====================

// Проверка, является ли число совершенным
// Совершенное число = сумме своих делителей (кроме самого себя)
// Примеры: 6 = 1+2+3, 28 = 1+2+4+7+14
bool MainWindow::isPerfect(int n) {
    if (n <= 1) return false;
    
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum == n;
}

// Поиск всех совершенных чисел в векторе
vector<int> MainWindow::findPerfectNumbers(const vector<int>& arr) {
    vector<int> result;
    for (int val : arr) {
        if (isPerfect(val)) {
            result.push_back(val);
        }
    }
    return result;
}

// Вывод вектора в QListWidget
void MainWindow::outputToListWidget(const vector<int>& arr, QListWidget* widget) {
    widget->clear();
    if (arr.empty()) {
        widget->addItem("(пусто)");
        return;
    }
    for (size_t i = 0; i < arr.size(); ++i) {
        widget->addItem(QString("[%1] = %2").arg(i).arg(arr[i]));
    }
}

// Обновление статусной строки
void MainWindow::updateStatus(const QString& message, bool isError) {
    labelStatus->setText(message);
    if (isError) {
        labelStatus->setStyleSheet("QLabel { background-color: #f8d7da; color: #721c24; padding: 10px; border-radius: 5px; }");
    } else {
        labelStatus->setStyleSheet("QLabel { background-color: #d4edda; color: #155724; padding: 10px; border-radius: 5px; }");
    }
}

// ===================== КОНСТРУКТОР =====================

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("ЛР 11 — Вариант 29 (Совершенные числа)");
    resize(900, 650);

    // ========== ГРУППА ВВОДА ==========
    textEditInput = new QTextEdit;
    textEditInput->setPlaceholderText("Введите целые числа, каждое на новой строке:\n6\n12\n28\n15\n496\n8");

    QGroupBox *inputGroup = new QGroupBox("Входные данные");
    QVBoxLayout *inputLayout = new QVBoxLayout;
    inputLayout->addWidget(new QLabel("Введите целые числа (каждое на новой строке):"));
    inputLayout->addWidget(textEditInput);
    inputGroup->setLayout(inputLayout);

    // ========== ГРУППА ВЫВОДА ==========
    listOriginal = new QListWidget;
    listResult = new QListWidget;

    QGroupBox *outputGroup = new QGroupBox("Результаты");
    QHBoxLayout *outputLayout = new QHBoxLayout;

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(new QLabel("Исходная структура:"));
    leftLayout->addWidget(listOriginal);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(new QLabel("Совершенные числа:"));
    rightLayout->addWidget(listResult);

    outputLayout->addLayout(leftLayout);
    outputLayout->addLayout(rightLayout);
    outputGroup->setLayout(outputLayout);

    // ========== КНОПКИ ==========
    btnSolve = new QPushButton("Решение");
    btnClear = new QPushButton("Очистить");
    btnExit = new QPushButton("Выход");

    // Стили для кнопок
    btnSolve->setStyleSheet("QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 8px; font-weight: bold; } QPushButton:hover { background-color: #0056b3; }");
    btnClear->setStyleSheet("QPushButton { background-color: #6c757d; color: white; border-radius: 5px; padding: 8px; font-weight: bold; } QPushButton:hover { background-color: #545b62; }");
    btnExit->setStyleSheet("QPushButton { background-color: #dc3545; color: white; border-radius: 5px; padding: 8px; font-weight: bold; } QPushButton:hover { background-color: #c82333; }");

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(btnSolve);
    btnLayout->addWidget(btnClear);
    btnLayout->addWidget(btnExit);
    btnLayout->addStretch();

    // ========== СТАТУСНАЯ СТРОКА ==========
    labelStatus = new QLabel("Введите числа и нажмите 'Решение'");
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setMinimumHeight(40);
    labelStatus->setStyleSheet("QLabel { padding: 10px; border-radius: 5px; background-color: #ecf0f1; color: #34495e; }");

    // ========== ОСНОВНОЙ МАКЕТ ==========
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputGroup);
    mainLayout->addWidget(outputGroup);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(labelStatus);

    QWidget *central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // ========== ПОДКЛЮЧЕНИЕ СИГНАЛОВ ==========
    connect(btnSolve, &QPushButton::clicked, this, &MainWindow::onSolveClicked);
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

// ===================== ОБРАБОТЧИКИ КНОПОК =====================

void MainWindow::onSolveClicked() {
    listOriginal->clear();
    listResult->clear();

    // Чтение чисел из текстового поля
    vector<int> nums;
    QString text = textEditInput->toPlainText();
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);

    for (const QString& line : lines) {
        bool ok;
        int val = line.trimmed().toInt(&ok);
        if (ok) {
            nums.push_back(val);
        }
    }

    if (nums.empty()) {
        updateStatus("Ошибка: введите хотя бы одно число!", true);
        QMessageBox::warning(this, "Ошибка", "Введите хотя бы одно число!");
        return;
    }

    // Вывод исходного массива
    for (size_t i = 0; i < nums.size(); i++) {
        listOriginal->addItem(QString("[%1] = %2").arg(i).arg(nums[i]));
    }

    // Поиск совершенных чисел
    vector<int> perfectNumbers = findPerfectNumbers(nums);

    if (perfectNumbers.empty()) {
        listResult->addItem("(нет совершенных чисел)");
        updateStatus(QString("Обработано %1 чисел. Совершенные числа не найдены.").arg(nums.size()), true);
        return;
    }

    // Вывод результата
    for (size_t i = 0; i < perfectNumbers.size(); i++) {
        listResult->addItem(QString("[%1] = %2").arg(i).arg(perfectNumbers[i]));
    }

    updateStatus(QString("Выполнено. Обработано %1 чисел. Найдено совершенных чисел: %2").arg(nums.size()).arg(perfectNumbers.size()));
}

void MainWindow::onClearClicked() {
    textEditInput->clear();
    listOriginal->clear();
    listResult->clear();
    updateStatus("Введите числа и нажмите 'Решение'", false);
    textEditInput->setFocus();
}

void MainWindow::onExitClicked() {
    close();
}

MainWindow::~MainWindow() {}
