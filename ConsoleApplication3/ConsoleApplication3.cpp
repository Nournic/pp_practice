#include <iostream>
#include <string>
#include <cstdlib>
#include "classes.cpp"
#include <ctime>
#pragma warning(disable : 4996)
#include <algorithm>
#include <limits>

using namespace std;

const string hallNames[5] = { "1", "2", "3", "4", "5" };
const string filmNames[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
const unsigned filmscount = 10;

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    //Раздача случайно длительности фильмам из массива с именами фильмов
    Time_t filmDuration[10];
    for (size_t i{}; i != 10; ++i) {
        filmDuration[i].setTime(rand() % 60, rand() % 60, 1, 0, 0, 0);
    }

    //Текущее время
    Time_t CurrentTime;
    time_t ttime = time(0);
    tm* now = localtime(&ttime);
    CurrentTime.setTime(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon, now->tm_year);

    Time_t start_day; //Начало дня, нужно для составления расписания
    Time_t day_end; //Конец дня, нужно для составления расписания

    const size_t hallsValue = 5; //Количество залов
    Hall hallsList[hallsValue]; //Массив с залами, размер задан hallsValue
    for (size_t i{}; i != hallsValue; i++) {
        hallsList[i].SetName(hallNames[i]); // задаём имя залу (пока предсказуемое)
        hallsList[i].SetMatrix(static_cast<size_t>(2 + rand() % 10), static_cast<size_t>(2 + rand() % 10)); // задаём размер зала
        hallsList[i].randomFillSeats(); // рандомно сажаем людей :)
        start_day.setTime(0, 0, 8, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
        day_end.setTime(0, 0, 23, CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());

        //Рандомная раздача фильмов залу на 7 дней
        for (unsigned day{ 1 }; day != 8; day++) {

            for (unsigned film{}; film != 8; film++) {
                unsigned random = rand() % 10;

                //Провека, чтобы предыдущий фильм не совпадал со следующим
                if (film != 0) {
                    while (hallsList[i].getFilms(day)[film - 1].getName() == filmNames[random]) {
                        random = rand() % 10;
                    }
                }
                //Добавление фильма в список фильмов на день
                if (start_day < (day_end - filmDuration[random])) {
                    hallsList[i].addFilm(filmNames[random], start_day, filmDuration[random], day);
                    start_day = start_day + filmDuration[random];
                    //Перерыв
                    start_day.addTime(0, 30, 0, 0, 0, 0);
                }
            }
            day_end.addTime(0, 0, 0, 1, 0, 0);
            start_day.setTime(0, 0, 8, start_day.getDay() + 1, start_day.getMonth(), start_day.getYear());
        }
    };
    char gr = '0';
    /* if (currHallNumber == "DEV") {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Запуск режима тестировщика
        } */

        // Пока работает только с выбранным залом
    bool again = false;
    bool anotherday = false;
    bool complete = false;
    unsigned day{ 1 };
    do {
        again = false;

        do {
            char choosefilmtoday = 'N';
            cout << "Выбрать фильм на сегодня? (Y/N): ";

            while (!(cin >> choosefilmtoday) || cin.peek() != 10 || (toupper(choosefilmtoday) != 'Y' && toupper(choosefilmtoday) != 'N')) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Выбрать фильм на сегодня? (Y/N): ";

            }

            if (choosefilmtoday == 'Y' && anotherday == false) {
                //Вывод фильмов на сегодня, с учётом нынешнего времени
                /*for (size_t i{}; i != 8; ++i) {
                    if (hallsList[currHallNumber].getFilms(1)[i].getName() != "" && hallsList[currHallNumber].getFilms(1)[i].getTimeStart() > CurrentTime) {
                        cout << "Name: " << hallsList[currHallNumber].getFilms(1)[i].getName() << " Start time: "; hallsList[currHallNumber].getFilms(1)[i].getTimeStart().printTimeWithoutSeconds();
                        cout << endl;
                    }
                }*/
                cout << "\nСписок фильмов\n";
                for (size_t i{}; i != 10; ++i) {
                    cout << i + 1 << ") Name: " << filmNames[i];
                    cout << endl;
                }
                cout << "Хотите посмотреть информацию о каком-либо фильме? (Y/N): ";
                char otvet{ 'N' };
                cin >> otvet;
                if (otvet == 'Y') {
                    unsigned number_film;
                    cout << "Введите номер фильма: ";
                    cin >> number_film;
                    bool exit{ false };
                    while (exit == false) {
                        cout << "Name: " << filmNames[number_film - 1] << " Залы: ";
                        for (size_t i{}; i != hallsValue; ++i) {
                            for (size_t j{}; j != 8; ++j) {
                                if (hallsList[i].getFilms(day)[j].getName() == filmNames[number_film - 1]) {
                                    cout << i + 1 << " ";
                                    break;
                                }
                            }
                        }
                        unsigned aoao;
                        cout << endl;
                        cout << "Для просмотра предыдущего фильма введите 0, для просмотра следующего фильма введите 1";
                        cout << endl << "Для выхода из режима просмотра введите 2" << endl;
                        cin >> aoao;
                        if (aoao == 0 && number_film > 1) number_film -= 1;
                        else if (aoao == 1 && number_film < 10) number_film += 1;
                        else if (aoao == 2) exit = true;
                    }
                }

                unsigned choose_number_film{ 0 };

                bool anotherfilm{ false };
                    anotherfilm = false;
                    cout << "Выберите номер желаемого фильма: ";
                    cin >> choose_number_film;
                    cout << "Выберите один из этих залов, в которых можно будет просмотреть фильм сегодня: ";
                    for (size_t i{}; i != hallsValue; ++i) {
                        for (size_t j{}; j != 8; ++j) {
                            if (hallsList[i].getFilms(day)[j].getName() == filmNames[choose_number_film - 1] /* && hallsList[i].getFilms(day)[j].getTimeStart() > CurrentTime*/) {
                                cout << i + 1 << " ";
                                anotherday = true;
                                break;
                            }
                            
                        }
                        if (anotherfilm == true) break;
                    }
                cout << endl;
                unsigned currHallNumber{ 0 };
                cin >> currHallNumber;
                if (currHallNumber > 0) currHallNumber -= 1;

                //вывод залов с заданным фильмом
                unsigned mins, hours;
                char UserChooseTime = 'N';
                Film chooseFilm;
                chooseFilm.setStart(23, 23, 23, 23, 23, 23);
                Film temp;
                temp.setStart(23, 23, 23, 23, 23, 23);
                cout << "You want choose time? (Y/N): ";
                cin >> UserChooseTime;
                if (UserChooseTime == 'Y') {
                    do {
                        for (size_t i{}; i != 8; ++i) {
                            Film temp_film;
                            temp_film = hallsList[currHallNumber].getFilms(1)[i];
                            if (filmNames[choose_number_film + 1] == temp_film.getName() && temp_film.getTimeStart() > CurrentTime) {
                                cout << "Время начала: "; hallsList[currHallNumber].getFilms(1)[i].getTimeStart().printTimeWithoutSeconds();
                                cout << endl;
                            }
                        }
                        cout << "Enter film's time: ";
                        cin >> hours >> mins;
                        for (size_t i{}; i != 8; ++i) {
                            if (hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getHour() == hours && hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getMin() == mins) {
                                Time_t timee;
                                timee.setTime(hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getSec(), hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getMin(), hallsList[currHallNumber].getFilms(1)[i].getTimeStart().getHour(), CurrentTime.getDay(), CurrentTime.getMonth(), CurrentTime.getYear());
                                if (timee > CurrentTime) {
                                    chooseFilm = hallsList[currHallNumber].getFilms(1)[i];
                                }
                            }
                        }
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } while (chooseFilm.getTimeStart() == temp.getTimeStart());
                }

                if (UserChooseTime == 'Y') {
                    hallsList[currHallNumber].PrintMatrix();
                    unsigned count_bilets;
                    cout << "Сколько билетов купить: ";
                    cin >> count_bilets;
                    char choose_choosen{ 'N' };
                    do {
                        unsigned userchoose_variant{};
                        bool choose_hand = false;
                        if (count_bilets > 8) {
                            //output всех вариантов рассадки
                            cout << "Хотите выбрать один из предложенных вариантов рассадки? (Y/N): ";
                            cin >> choose_choosen;
                            if (choose_choosen == 'Y') {
                                //выбор варианта рассадки
                            }
                        }

                        if (choose_choosen == 'N' || count_bilets <= 8) {
                            //Ручной ввод мест
                            //Заполнение согласно ручному вводу
                        }
                        else {
                            //Заполнение согласно выбранному варианту
                        }
                        hallsList[currHallNumber].PrintMatrix();

                        char seats_choosen_right = 'N';
                        cout << "Места выбраны верно?";
                        cin >> seats_choosen_right;

                        if (seats_choosen_right == 'Y') {

                            //Формирование счета к оплате
                            complete = true;
                        }
                        else if (choose_hand == true) {
                            // __
                        }
                    } while (choose_choosen == true);
                }
                else if (choosefilmtoday == 'N') {

                    //Выбор фильма на другой день

                }
                else anotherday = true;
            }
            else {
                //Вывод фильма на ближайшие 7 дней
                //    Выберите день
            }
        } while (anotherday == true && complete == false);

        //Оплата
        //userHall.addProfit(1/* счёт оплаты*/);
        if (/*Конец смена == */true) {
            again = false;
        }
        else {
            again = true;
        }
    } while (again == true);
    unsigned profit{ 0 };
    for (size_t i{}; i != hallsValue; ++i) {
        profit += hallsList[i].getProfit();
    }
    cout << "Кинозал получил прибыли: " << profit;

    //do {
    //    gr = (int)gr + 1;

    //    userHall.PrintMatrix();

    //    cout << "Введите колличество человек в группе " << gr << " -> " << '\n'; cin >> humans;

    //    bool complete = false;

    //    for (size_t i{}; i < userHall.GetLine(); ++i) { // бежим по рядам
    //        unsigned slots{}, firstSeat{}, lastSeat{};
    //        for (size_t j{}; j < userHall.GetSeat(); ++j) { // бежим по местам ряда i
    //            if (userHall.GetSeatStatus(i, j) == '0') { // если место пустое
    //                slots++; // число подряд-свободных мест
    //                if (slots == 1) firstSeat = j; // место для первого человека
    //            }
    //            else {
    //                slots = 0; firstSeat = 0;
    //            }

    //            if (slots == humans) {
    //                lastSeat = j;
    //                if (!complete) userHall.SetSeat(firstSeat, lastSeat, i, gr);
    //                complete = true;
    //            }
    //        }
    //    }

    //    if (!complete) {
    //        cout << "Группу " << gr << " невозможно посадить в один ряд" << '\n';
    //        gr = (int)gr - 1;
    //    }

    //    userHall.PrintMatrix();

    //    cout << "Хотите посадить ещё одну группу?" << '\n';
    //    cin >> repeat;
    //} while (repeat == "Yes");

    return 0;
}