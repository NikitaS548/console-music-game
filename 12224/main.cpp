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
    //        создание переменных и подклюючение русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int secret, guess, tries;
    char again;
    int score = 0;
    int round = 0;
    int difficulty;

    //         приветствие игрока
    cout << "\n";
    cout << "================\n";
    cout << "  УГАДАЙ НОТУ\n";
    cout << "  V.1.0(сложности)\n";
    cout << "================\n\n";
    cout << "Выбери сложность:\n";
    cout << "1 - Легко (5 попыток, подсказки)\n";
    cout << "2 - Средне (2 попытки)\n";
    cout << "3 - Сложно (1 попытка)\n";
    cin >> difficulty;
    int maxTries = (difficulty == 1) ? 5 : (difficulty == 2) ? 2 : 1;
    int ptsMult = (difficulty == 1) ? 1 : (difficulty == 2) ? 2 : 3;
    cout << "Счёт: " << score << "\n";


    //          основной цикл
    do {
        //      загадывание ноты
        round++;
        secret = rand() % 7 + 1;
        tries = 0;
        playNote(notes[secret-1],750);
        cout << "\nРаунд " << round << ":\n";
        cout << "1(До) 2(Ре) 3(Ми) 4(Фа) 5(Соль) 6(Ля) 7(Си)\n";
        cout << "У тебя "<<maxTries<<" попыток(-тки)\n\n";

        while (tries < maxTries) {
            //     попытка отагадь ноту
            cout << "> ";
            cin >> guess;

            if (guess < 1 or guess > 7) {
                cout << "Нет такой ноты\n";
                continue;
            }

            tries++;

            if (guess == secret) {
                int pts = (tries == 1) ? 100:(tries==2) ? 50:(tries==3) ? 25:10;
                score += pts*ptsMult;
                cout << "\n=== ПОБЕДА ===\n";
                cout << "Нота " << secret << "\n";
                cout << "+" << pts<<" * mult("<<ptsMult<<") очков (с " << tries << "-й попытки)\n";
                break;
            }

            if (tries == maxTries) {
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
            cout << "Осталось: " << maxTries - tries << "\n\n";
        }

        cout << "\nСчёт: " << score << "\n";
        cout << "Ещё? (y/n): ";
        cin >> again;
        cout << "\n";

    } while (again == 'y' or again == 'Y');

    cout << "Игра окончена! Финальный счёт: " << score << "\n\n";
    return 0;
}
