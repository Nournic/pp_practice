#include <string>
#include <iostream>
#include "time.cpp"
#include <vector>
using namespace std;

class Seat {
private:
    unsigned price_seat{0};
    bool vip_status{false};
    char status_seat{'0'};
public:

    void setStatus(char status) {
        status_seat = status;
    }

    char getStatus() {
        return status_seat;
    }

    void setVip(bool vip) {
        vip_status = vip;
    }

    bool getVip() {
        return vip_status;
    }

    void setPrice(unsigned price) {
        price_seat = price;
    }

    int getPrice() {
        return price_seat;
    }

};

class Film {
private:
    string name{};
    Time_t start{};
    Time_t end{};
    Time_t duration_film{};

public:
    void setStart(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 1, unsigned months = 1, unsigned years = 1970) {
        start.setTime(secs, mins, hours, days, months, years);
    }
    void setStart(Time_t startt) {
        start = startt;
    }

    void setEnd(unsigned secs, unsigned mins=0, unsigned hours=0, unsigned days=1, unsigned months=1, unsigned years=1970) {
        end.setTime(secs, mins, hours, days, months, years);
    }
    void setDuration(unsigned secs, unsigned mins = 0, unsigned hours = 0, unsigned days = 0, unsigned months = 0, unsigned years = 0) {
        Time_t duration;
        duration.setTime(secs, mins, hours, days, months, years);
        end = start + duration;
    }
    void setDuration(Time_t duration) {
        end = start + duration;
        duration_film = duration;
    }

    Time_t getDuration() {
        return duration_film;
    }
    Time_t getTimeStart() {
        return start;
    }
    Time_t getTimeEnd() {
        return end;
    }

    string getName() {
        return name;
    }

    void setName(string names) {
        name = names;
    }
};

class TimeTable {
private:
    Time_t start_day{}; 
    Time_t end_day{};
    Film film{};
public:

};
class Hall
{
private:
    size_t line{};
    size_t seat{};
    string name_hall = "";
    char** matrix{};
    const size_t size = 7;
    Film** films{};
    unsigned profit{ 0 };
public:
    void SetName(string h_name) { // ��� ��������
        name_hall = h_name;
    }
    void addProfit(unsigned money) {
        profit += money;
    }

    unsigned getProfit() {
        return profit;
    }
    void addFilm(string name, Time_t start, Time_t duration, unsigned day) {
        Film filmss;
        filmss.setName(name);
        filmss.setStart(start);
        filmss.setDuration(duration);
            for (size_t i{}; i != 8; ++i) {
                if (films[day-1][i].getName() == "") { 
                    films[day-1][i] = filmss;
                    return;
                }
        }
    }

    char** getMatrix() {
        return matrix;
    }

    Film* getFilms(unsigned day) {
        return films[day-1];
    }

    void outputFilms(unsigned day) {
        for (size_t i{}; i != 8; ++i) {
            cout << films[day-1][i].getName() << " ";
        }
    }

    void SetMatrix(size_t h_line, size_t h_seat) { // ������� ������� ���� 
        line = h_line;
        seat = h_line;
        matrix = new char* [line] {};
        films = new Film * [7] {};
        for (size_t i{}; i != line; ++i) {
            matrix[i] = new char[seat] {'0'};
        }
        for (size_t i{}; i != 7; ++i) {
            films[i] = new Film[8] {};
        }
    }
    void deleteMatrix() {
        for (size_t i{}; i != line; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        for (size_t i{}; i != 7; ++i) {
            delete[] films[i];
        }
        delete[] films;
    }

    void SetSeat(size_t fs, size_t ls, size_t row, char gr) { // ���������� ����
        for (size_t i = fs; i <= ls; ++i) {
            matrix[row][i] = gr;
        }
    }

    char GetSeatStatus(size_t i, size_t j) { // �������� ������ ����� 
        return matrix[i][j];
    }

    size_t GetLine() { // �������� ����� ����� 
        return line;
    }

    size_t GetSeat() { // �������� ����� ���� � ������ ���� 
        return seat;
    }

    void PrintMatrix() { // ����� ������� ����
        for (size_t i{}; i != line; ++i) {
            for (size_t j{}; j != seat; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << '\n';
        }
        cout << '\n';
    }

    void PrintInfo() { // ����� ���������� � ��������
        cout << "Name: " << name_hall << '\t' <<
            "Line: " << line << '\t' <<
            "Seat: " << seat << '\n';
    }

    void randomFillSeats() { // �������� ������ ����� :)
        char elems[2] = { '0', '*' };
        for (size_t i{}; i != line; ++i) {
            for (size_t j{}; j != seat; ++j) {
                matrix[i][j] = elems[rand() % 2];
            }
        }
    }
};



class Hall_Money
{
private:
    size_t line{};
    size_t seat{};
    unsigned** matrix{};
    unsigned money{ 0 };
public:

    void SetMatrix(size_t h_line, size_t h_seat) { // ������� ������� ���� 
        line = h_line;
        seat = h_line;
        matrix = new unsigned* [line] {};
        for (size_t i{}; i != line; ++i) {
            matrix[i] = new unsigned[seat] {'0'};
        }
    }

    void addProfit(unsigned profit) {
        money += profit;
    }

};

