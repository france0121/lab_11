#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSolveClicked();
    void onClearClicked();
    void onExitClicked();

private:
    // Функции задания
    bool isPerfect(int n);
    std::vector<int> findPerfectNumbers(const std::vector<int>& arr);
    void outputToListWidget(const std::vector<int>& arr, QListWidget* widget);
    void updateStatus(const QString& message, bool isError = false);

    // UI
    QTextEdit *textEditInput;
    QListWidget *listOriginal;
    QListWidget *listResult;
    QLabel *labelStatus;
    QPushButton *btnSolve, *btnClear, *btnExit;
};

#endif
