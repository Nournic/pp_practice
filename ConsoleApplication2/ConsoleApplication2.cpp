#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void printSeats(char**, const size_t&, const size_t&);
void fillCinema(char**, const size_t&, const size_t&, const size_t&, const char&);
void randomFillSeats(char**, const size_t&, const size_t&);
char checkAns();
// создание динамических двумерных массивов
// настройка структуры зала
// стоимость: прибыль, время сеанса, фильм, vip места, диванчики:)
// выбрать желаемый ряд

struct zal {
    unsigned line;
    unsigned collumn;
    char** matrix;
    int** price;
};

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    zal seats;
    cout << "Введите количество рядов в зале и кол-во мест в каждом ряду -> ";
    while (!(cin >> seats.line >> seats.collumn) || cin.peek() != 10) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nВы ввели неправильные значения\n";
        cout << "Введите количество рядов в зале и кол-во мест в каждом ряду -> ";
    }

    seats.line = 5;
    seats.collumn = 6;
    seats.matrix = new char* [seats.line];
    seats.price = new int* [seats.line];
    for (int i = 0; i < seats.line; i++) {
        seats.matrix[i] = new char[seats.collumn];
        seats.price[i] = new int[seats.collumn];
    }


    randomFillSeats(seats.matrix, seats.collumn, seats.line);
    printSeats(seats.matrix, seats.collumn, seats.line);

    string repeat = "Yes";
    unsigned humans; // число человек в группе

    char gr = '0';
    do
    {
        gr = (int)gr + 1;
        cout << "Введите колличество человек в группе " << gr << " -> " << '\n';
        while (!(cin >> humans) || cin.peek() != 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите колличество человек в группе " << gr << " -> " << '\n';
        }

        bool complete = false;
        for (size_t i = 0; i < seats.line; ++i) { // бежим по рядам
            unsigned slots = 0, firstSeat = 0, lastSeat = 0;
            for (size_t j = 0; j < seats.collumn; ++j) { // бежим по местам ряда i
                if (seats.matrix[i][j] == '0') { // если место пустое
                    slots++; // число подряд-свободных мест
                    if (slots == 1) firstSeat = j; // место для первого человека
                }
                else {
                    slots = 0; firstSeat = 0;
                }

                if (slots == humans) {
                    lastSeat = j;
                    if (!complete) fillCinema(seats.matrix, firstSeat, lastSeat, i, gr);
                    complete = true;
                }
            }
        }

        if (!complete) {
            cout << "Группу " << gr << " невозможно посадить в один ряд" << '\n';
            gr = (int)gr - 1;
        }

        printSeats(seats.matrix, seats.collumn, seats.line);

        cout << "Хотите посадить ещё одну группу? (Y/N)" << '\n';
    } while (checkAns() == 'Y');
    for (int i = 0; i < seats.line; i++) {
        delete[] seats.matrix[i];
        delete[] seats.price[i];
    }
    delete[] seats.matrix;
    delete[] seats.price;

}
void printSeats(char** seats, const size_t& cols, const size_t& rows) {
    cout << "-----SCREEN-----" << '\n';
    for (size_t i{}; i != rows; ++i) {
        for (size_t j{}; j != rows; ++j) {
            cout << seats[i][j] << " ";
        }
        cout << '\n';
    }
}

// рандомно сажаем людей
void randomFillSeats(char** seats, const size_t& cols, const size_t& rows) {
    char elems[2] = { '0', '*' };
    /*можно через if*/
    for (size_t i{}; i != rows; ++i) {
        for (size_t j{}; j != rows; ++j) {
            seats[i][j] = elems[rand() % 2];
        }
    }
}

void fillCinema(char** seats, const size_t& fs, const size_t& ls, const size_t& row, const char& gr) {
    for (size_t i = fs; i <= ls; ++i) {
        seats[row][i] = gr;
    }
}

char checkAns() {
    char ans;
    while (!(cin >> ans) || cin.peek() != 10 || (toupper(ans) != 'Y' && toupper(ans) != 'N')) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Хотите посадить ещё одну группу? (Y/N)" << '\n';
    }
    return toupper(ans);
}