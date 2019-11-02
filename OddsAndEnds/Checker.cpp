#include <bits/stdc++.h>

using namespace std;

mt19937 Rand(time(0));
#define task "TEST"
void MakeInput()
{
    ofstream fi(task".inp");

    fi.close();
}

int Check()
{
    //ifstream fo(task".out");
    //ifstream fa(task".ans");
    return system("fc /W "task".out "task".ans");
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    for (int itest = 1; itest <= T; ++itest)
    {
        //system("cls");
        cout << "itest " << itest << ": ";
        MakeInput();
        //return 0;
        system(task".exe");
        system(task"_Brute.exe");
        if (Check()) { cout << "WA"; return 0; }
        cout << "OK\n";
    }
}
