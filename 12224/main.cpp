#include <bits/stdc++.h>
#include <cmath>
#include <windows.h>
#include <random>


using namespace std;

//       Звук
vector<float>notes = {261.63,293.66,329.63,349.23,392.00,440.00,493.88};
void playNote(double frequency, int durationMs) {
    Beep(static_cast<DWORD>(frequency), durationMs);
     // Beep() – встроенная функция Windows, издаёт простой звук через динамик.
    // static_cast<DWORD> преобразует double в целое число (DWORD = 32-битное беззнаковое)
}

int main() {
    //        создание переменных и подклюючение русского языка
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Установка шрифта для поддержки кириллицы
    system("chcp 65001 > nul");

    random_device rd; //источник seed
    mt19937 gen(rd());// генератор чисел
    uniform_int_distribution<> dist(1, 7);// диапозон

    int secret, guess, tries;
    char again;
    int score = 0;
    int round = 0;
    int difficulty=0;
    int correctAnswers = 0;
    int totalRounds = 0;
    int perfectRounds = 0;
    float totalAttempts = 0.0;

    //         приветствие игрока
    cout << "\n";
    cout << "================\n";
    cout << "  УГАДАЙ НОТУ\n";
    cout << "  V.1.2\n";
    cout << "================\n\n";
    cout << "Выбери сложность:\n";
    cout << "1 - Легко (5 попыток, подсказки)\n";
    cout << "2 - Средне (2 попытки)\n";
    cout << "3 - Сложно (1 попытка)\n";
    while (true){
        cin >> difficulty;
        if (difficulty>=1 and difficulty<=3){
            break;
        }
        else cout<<"\nнекоректный ввод!\n";
    }
    int maxTries = (difficulty == 1) ? 5 : (difficulty == 2) ? 2 : 1;
    int ptsMult = (difficulty == 1) ? 1 : (difficulty == 2) ? 2 : 3;
    cout << "Счёт: " << score << "\n";

    //          основной цикл
    do {
        //      загадывание ноты
        round++;
        secret = dist(gen);
        tries = 0;
        playNote(notes[secret-1],750);
        cout << "1(До) 2(Ре) 3(Ми) 4(Фа) 5(Соль) 6(Ля) 7(Си)\n";
        cout << "У тебя " << maxTries << " попыток(-тки)\n\n";

        while (tries < maxTries) {
            //     попытка отгадать ноту
            cout << "> ";
            cin >> guess;

            if (guess < 1 or guess > 7) {
                cout << "Нет такой ноты\n";
                continue;
            }

            tries++;

            if (guess == secret) {
                correctAnswers++;
                if (tries == 1) {
                    perfectRounds++;
                }
                totalAttempts += tries;
                int pts = (tries == 1) ? 100 : (tries == 2) ? 50 : (tries == 3) ? 25 : 10;
                score += pts * ptsMult;
                cout << "\n=== ПОБЕДА ===\n";
                cout << "Нота " << secret << "\n";
                cout << "+" << pts << " * mult(" << ptsMult << ") очков (с " << tries << "-й попытки)\n";
                break;
            }

            if (tries == maxTries) {
                cout << "\nНе угадал. Это была нота №" << secret << "\n";
                break;
            }

            if (guess != secret) {
                cout << "\n-- музыкальная подсказка ---\n";
                double freqSecret = notes[secret-1];
                double freqGuess = notes[guess-1];
                double semitones = 12.0 * log2(freqSecret / freqGuess);
                cout << "Ты ошибся на " << floor(semitones * 10) / 10 << " полутонов.\n";
                if (semitones > 0)
                    cout << "Загаданная нота ВЫШЕ на " << fabs(semitones) << " полутонов\n";
                else if (semitones < 0)
                    cout << "Загаданная нота НИЖЕ на " << fabs(semitones) << " полутонов\n";
                if (fabs(semitones) <= 2.0) {
                    int bonus = 20 * ptsMult;
                    score += bonus;
                        cout << "Бонус за близость! +" << bonus << " очков\n";
                    }
                    cout << "Осталось попыток: " << maxTries - tries << "\n\n";
                }
            cout << "Осталось: " << maxTries - tries << "\n\n";
        }

        cout << "\nСчёт: " << score << "\n";
        cout << "Ещё? (y/n): ";
        cin >> again;
        cout << "\n";
        system("cls");

    srand(time(0));
    } while (again == 'y' or again == 'Y');

    // ФИНАЛЬНАЯ СТАТИСТИКА
    cout << "\n═══════════════════════════════════\n";
    cout << "           ИГРА ОКОНЧЕНА           \n";
    cout << "          СТАТИСТИКА ИГРЫ          \n";
    cout << "═══════════════════════════════════\n";
    cout << "Всего раундов:        " << round << "\n";
    cout << "Правильных ответов:   " << correctAnswers << "\n";
    cout << "Точность:            " << (round > 0 ? (correctAnswers * 100 / round) : 0) << "%\n";
    cout << "Идеальных раундов:    " << perfectRounds << " (с 1-й попытки)\n";
    cout << "Финальный счёт:       " << score << "\n";
    cout << "═══════════════════════════════════\n";

    return 0;
}
