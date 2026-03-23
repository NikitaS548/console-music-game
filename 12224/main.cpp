#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;



//       Звук
vector<float>notes = {261.63,293.66,329.63,349.23,392.00,440.00,493.88};
void playNote(double frequency, int durationMs) {
    Beep(static_cast<DWORD>(frequency), durationMs);
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int secret, guess, tries;
    char again;
    int score = 0;
    int round = 0;

    cout << "\n";
    cout << "================\n";
    cout << "  УГАДАЙ НОТУ\n";
    cout << "  V.0.3(звук)\n";
    cout << "================\n\n";
    cout << "Счёт: " << score << "\n";

    do {
        round++;
        secret = rand() % 7 + 1;
        tries = 0;
        playNote(notes[secret-1],750    );
        cout << "\nРаунд " << round << ":\n";
        cout << "1(До) 2(Ре) 3(Ми) 4(Фа) 5(Соль) 6(Ля) 7(Си)\n";
        cout << "У тебя 2 попытки\n\n";

        while (tries < 2) {
            cout << "> ";
            cin >> guess;

            if (guess < 1 || guess > 7) {
                cout << "Нет такой ноты\n";
                continue;
            }

            tries++;

            if (guess == secret) {
                int pts = (tries == 1) ? 100:50;
                score += pts;
                cout << "\n=== ПОБЕДА ===\n";
                cout << "Нота " << secret << "\n";
                cout << "+" << pts << " очков (с " << tries << "-й попытки)\n";
                break;
            }

            if (tries == 2) {
                cout << "\nНе угадал. Это была нота №" << secret << "\n";
                break;
            }



            cout << "\n-- подсказка ---\n";
            double accuracy = 100.0 - (fabs(guess - secret) / 6.0 * 100.0);
            if (accuracy < 0) accuracy = 0;

            cout << "Твоя догадка верна на " << accuracy << "%\n";


            if (guess < secret) {
                cout << "Выше\n";
            } else {
                cout << "Ниже\n";
            }
            cout << "Осталось: " << 2 - tries << "\n\n";
        }

        cout << "\nСчёт: " << score << "\n";
        cout << "Ещё? (y/n): ";
        cin >> again;
        cout << "\n";

    } while (again == 'y' || again == 'Y');

    cout << "Игра окончена! Финальный счёт: " << score << "\n\n";
    return 0;
}
