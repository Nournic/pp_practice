#include <iostream>
#include <vector>
using namespace std;
void zapolnenie(vector<vector<int>>& vec, int group); void output(vector<vector<int>>& vec);
int main()
{
    setlocale(LC_ALL, "RU");
    int n, m, group,count_groups;
    cin >> n >> m >> group >> count_groups;
    vector<vector<int>> zal(n, vector<int>(m,0));
    zal[0][0] = 1;
    zapolnenie(zal, group);
    output(zal);
}
void zapolnenie(vector<vector<int>>& vec, int group) {
    int asd = 100;
    while (asd > 0) {
        asd = 0;
        for (size_t i = 0; i < vec.size(); i++) {
            for (size_t j = 0; j < vec[0].size(); j++) {
                if (((i > 0 && vec[i - 1][j] == 1) || (j > 0 && vec[i][j - 1] == 1) || (j < vec[0].size() - 1 && vec[i][j + 1] == 1) || (i < vec.size() - 1 && vec[i + 1][j] == 1)) && group > 0 && vec[i][j] != 1) {
                    asd += 1;
                    vec[i][j] = 1;
                    group -= 1;
                }
            }
        }
    }
    if (group > 0) cout << "Не удалось рассадить " << group-1 << " человек.";
    else cout << "Все рассажены";
}
void output(vector<vector<int>>& vec) {
    cout << endl;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[0].size(); j++) cout << vec[i][j];
        cout << endl;
    }
}

