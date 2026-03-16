#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <Cmath>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int secret, guess, tries;
    char again;

    cout << "\n";
    cout << "================\n";
    cout << "  УГАДАЙ НОТУ\n";
    cout << "  V.0.1(demo)\n";
    cout << "================\n\n";

    do {
        secret = rand() % 7 + 1;
        tries = 0;

        cout << "Я загадал ноту (1-7)\n";
        cout << "1(До) 2(Ре) 3(Ми) 4(Фа) 5(Соль) 6(Ля) 7(Си)\n";
        cout << "У тебя 5 попыток\n\n";

        while (tries < 5) {
            cout << "> ";
            cin >> guess;

            if (guess < 1 || guess > 7) {
                cout << "Нет такой ноты\n";
                continue;
            }

            tries++;

            if (guess == secret) {
                cout << "\n=== ПОБЕДА ===\n";
                cout << "Нота " << secret << "\n";
                break;
            }

            if (tries == 5) {
                cout << "\nНе угадал. Это была нота №" << secret << "\n";
                break;
            }

            if (guess < secret) {
                cout << "Выше\n";
            } else {
                cout << "Ниже\n";
            }
            cout << "Осталось: " << 5 - tries << "\n\n";
        }

        cout << "\nЕщё? (y/n): ";
        cin >> again;
        cout << "\n";

    } while (again == 'y' || again == 'Y');

    cout << "Пока\n\n";

    return 0;
}
