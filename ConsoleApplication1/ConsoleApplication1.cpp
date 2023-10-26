#include <iostream>
#include <vector>
using namespace std;
char checkAns() {
    cout << "You want add new group? (Y/N) ";
    char ans;
    while (!(cin >> ans) || cin.peek() != 10 || (toupper(ans) != 'Y' && toupper(ans) != 'N'))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You wand add new group? (Y/N): ";
    }
    return toupper(ans);
}
int razm(int** vec, int group, int line, int collumns, int nomer) {
    int svobod;
    if (line >= group) {
        for (int j = 0; j < collumns; j++) {
            svobod = 0;
            for (int i = 0; i < line; i++) {
                if (vec[i][j] == 0) svobod += 1;
            }
            if (svobod >= group && group>0) {
                for (int i = 0; i < line; i++) {
                    if (vec[i][j] == 0 && group>0) vec[i][j] = nomer;
                    group -= 1;
                }
            }
        }
        if (group > 0) {
            cout << "Группу усадить не удалось в данный кинозал";
            return 0;
        }
        else return 1;
    }
    else { 
        cout << "В группе больше людей чем допустимо для выполнения условия задачи"; 
        return 0;
    }
}
void output(int** vec, int line, int collumn) {
    for (int i = 0; i < collumn; i++) {
        for (int j = 0; j < line; j++)
            cout << vec[j][i];
        cout << endl;
    }    
}
struct zal {
    int line;
    int collumn;
    int** matrix;
    int** price;
};


int main()
{
    zal test;
    test.line = 5;
    test.collumn = 6;
    test.matrix = new int*[test.line];
    test.price = new int* [test.line];
    for (int i = 0; i < test.line; i++) {
        test.matrix[i] = new int[test.collumn];
        test.price[i] = new int[test.collumn];
    }
    for (int i = 0; i < test.line; i++) {
        delete[] test.matrix[i];
        delete[] test.price[i];
    }
    delete[] test.matrix;
    delete[] test.price;

    setlocale(LC_ALL, "RU");
    int line, collumn;
    cin >> line >> collumn;
    int** zal = new int* [line];
    for (int i = 0; i < line; i++) {
        zal[i] = new int[collumn] {0};
    }
    int group,nomer=0;
    nomer = 1;
    do {
        cin >> group;
        while (razm(zal, group, line, collumn, nomer) == 0) {
            cout << endl;
            while (!(cin >> group) || group < 2) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Это не группа, введите снова: ";
            }
        }
        nomer += 1;
        output(zal, line, collumn);
    } while (checkAns() == 'Y');
}

