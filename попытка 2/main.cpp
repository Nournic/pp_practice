﻿#include <iostream>
#include <string>
#include <cstdlib>
#include "classes.cpp"
#include <ctime>
#pragma warning(disable : 4996)
#include <algorithm>
#include <limits>
#include <set>

using namespace std;

const string hallNames[5] = { "1", "2", "3", "4", "5" };
const string filmNames[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
const unsigned filmscount = 10;

string typeSelect(char);
void cinemaHall(unsigned, Hall*); // функция задает размеры залов.

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RU");


    size_t hallsValue; //Количество залов
    Time_t CurrentTime;
    Time_t start_day; //Начало дня, нужно для составления расписания
    Time_t day_end; //Конец дня, нужно для составления расписания
    bool again = false; //Повтор, если покупатель захотел ещё раз сходить в кино
    bool anotherday = false; //Если покупатель решил придти в другой день, запускается ветка выбора дня
    bool complete = false;  //Если покупатель закончил с фильмами, то выход из циклов
    unsigned day{ 1 };
    char choosefilmtoday = 'N';
    char otvet{ 'N' };
    unsigned continue_inspection;
    unsigned choose_number_film;
    bool anotherfilm;
    unsigned number_film;
    set<unsigned> listHallsWithCurrentFilm;


    //Раздача случайно длительности фильмам из массива с именами фильмов
    Time_t filmDuration[10];
    for (size_t i{}; i != 10; ++i) {
        filmDuration[i].setTime(rand() % 60, rand() % 60, 1, 0, 0, 0);
    }

    cout << "Вид от кассира" << endl;
    cout << "Введите количество кинозалов -> "; // проверки нет, но подразумевается, что их 3-5.
    cin >> hallsValue;
    Hall* hallsList = new Hall[hallsValue];; //Массив с залами, размер задан hallsValue
    for (size_t i{}; i != hallsValue; i++) {
        cout << "Введите название для кинозала " << i + 1 << " зала -> ";
        string name; cin >> name;
        hallsList[i].SetName(name); // установка имени зала.
        cout << "Выберите тип зала ('g' - обычный, 's' - с диванами, 'v' - VIP, 'c' - детский) -> ";
        char tp; cin >> tp; // установка типа зала.
        hallsList[i].SetType(typeSelect(tp));
        cinemaHall(i + 1, hallsList); // задаем параметры количества мест и рядов для каждого объекта в массиве, собств. матрицы.
    }
    cout << "Структура кинозалов настроена. Введённые данные:" << endl;
    for (size_t i{}; i != hallsValue; i++) {
        hallsList[i].PrintInfo(); // метод вывода информации, чтобы увидеть результат.
    }
    system("pause");
    system("cls");
    

    cout << "Вид от покупателя" << endl;
    //Текущее время
    time_t ttime = time(0);
    tm* now = localtime(&ttime);
    CurrentTime.setTime(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday, now->tm_mon, now->tm_year);
    
    for (size_t i{}; i != hallsValue; i++) {
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

    do {
        again = false;
        do {
            choosefilmtoday = 'N';
            if (anotherday == false) {
                cout << "Выбрать фильм на сегодня? (Y/N): ";

                while (!(cin >> choosefilmtoday) || cin.peek() != 10 || (toupper(choosefilmtoday) != 'Y' && toupper(choosefilmtoday) != 'N')) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Выбрать фильм на сегодня? (Y/N): ";

                }
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
                otvet = 'N';
                cin >> otvet;
                if (otvet == 'Y') {
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
                        cout << endl;
                        cout << "Для просмотра предыдущего фильма введите 0, для просмотра следующего фильма введите 1";
                        cout << endl << "Для выхода из режима просмотра введите 2" << endl;
                        cin >> continue_inspection;
                        if (continue_inspection == 0 && number_film > 1) number_film -= 1;
                        else if (continue_inspection == 1 && number_film < 10) number_film += 1;
                        else if (continue_inspection == 2) exit = true;
                    }
                }

                continue_inspection = -1;
                choose_number_film = 0;
                anotherfilm = false;

                cout << "Выберите номер желаемого фильма: ";
                cin >> choose_number_film;
                
                for (size_t i{}; i != hallsValue; ++i) {
                    for (size_t j{}; j != 8; ++j) {
                        if (hallsList[i].getFilms(day)[j].getName() == filmNames[choose_number_film - 1] && hallsList[i].getFilms(day)[j].getTimeStart() > CurrentTime) {
                            listHallsWithCurrentFilm.insert(i);
                        }
                    }
                }
                   
                
                if (listHallsWithCurrentFilm.empty()) {
                    cout << "К сожалению, данный фильм не показывают сегодня. У вас есть вариант выбрать другой или придти в другой день\n0 - другой фильм\t1 - другой день\n";
                    cin >> continue_inspection;
                    
                }
                if (continue_inspection == 1) {
                    anotherday = true; again = true;
                }
                if (again == false) {
                    cout << "Выберите один из этих залов, в которых можно будет просмотреть фильм сегодня: ";
                    for (int n : listHallsWithCurrentFilm)
                        cout << n+1 << ' ';
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

void cinemaHall(unsigned k, Hall* halls) // функция задает размеры залов.
{
    size_t cols, rows; // количество мест в ряду, рядов.
    cout << "Выберите размеры для " << k << "-го кинозала.\n"; // 2 таких зала.
    cout << "Введите количество рядов в зале -> ";
    cin >> rows;
    cout << "Введите количество мест в каждом ряду -> ";
    cin >> cols;
    halls[k - 1].SetMatrix(rows, cols); // просто заполняет матрицы элементов массива залов за счёт встроенного метода.
}

string typeSelect(char tp) // отдельная функция выбора типа кинозала.
{
    switch (tp) {
    case 'g':
        cout << "Выбран вариант: обычный." << endl;
        return "general";
        break;
    case 's':
        cout << "Выбран вариант: с диванами." << endl;
        return "soft";
        break;
    case 'v':
        cout << "Выбран вариант: VIP." << endl;
        return "VIP";
        break;
    case 'c':
        cout << "Выбран вариант: детский." << endl;
        return "children's";
        break;
    }
}