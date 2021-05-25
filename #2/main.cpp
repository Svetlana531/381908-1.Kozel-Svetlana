#include <iostream>
#include "UMatrix.h"

#define PATH "C:\\out.txt"

int main()
{
    TMatrix<int> a(5), b(5), c(5);
    int i, j;

    setlocale(LC_ALL, "Russian");
    cout << "Тестирование программ поддержки представления треугольных матриц"
        << endl;
    for (i = 0; i < 5; i++)
        for (j = i; j < 5; j++)
        {
            a[i][j] = i * 10 + j;
            b[i][j] = (i * 10 + j) * 100;
        }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;

    c = a * b;
    cout << "Matrix c = a * b" << endl << c << endl;

    c = a * 5;
    cout << "Matrix c = a * 5" << endl << c << endl;

    c = a + 5;
    cout << "Matrix c = a + 5" << endl << c << endl;

    c = a - 5;
    cout << "Matrix c = a - 5" << endl << c << endl;


    LowerMatrix<int> test(5);
    for (i = 0; i < 5; i++)
        for (j = 0; j <= i; j++)
        {
            test[i][j] = i * 2 + j + 1;
        }
    cout << test << endl;

    int size = 25;
    TVector<int> val(size);                 // Znacheniya
    TVector<int> col(size);                 // Index colums
    TVector<int> row(6);                    // Index row
    TVector<int> tmp(size);                 // For prosmotr isxodnyx data
    int tmp_i = 0;
    int k = 0;
    srand(time(NULL));
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            int num = 0 + rand() % 3;       // randomim 0..2
            tmp[tmp_i] = num;
            tmp_i++;
            if (num > 0)                    // pishem only null
            {
                val[k] = num;
                col[k] = j;
                k++;
            }
            row[i + 1] = k;
        }
    }
    RazrMatrix<int> razr(6, k);
    cout << "Inpud data: " << tmp << "\n";      // check input data
    razr.input(val, col, row);                  // input matrix

    cout << "\nRazryazgennie matrix: \n";
    cout << razr << endl;

    cout << "Klassic vid matrix: \n";
    razr.print();
 
    cout << "Razryazgennie matrix r = a + a: " << endl;
    RazrMatrix<int> r(6, k);
    r = razr + razr;
    r.print();

    cout << "Razryazgennie matrix r = a * a: " << endl;
    r = razr * razr;
    r.print();

    cout << "Razryazgennie matrix r = a * 5: " << endl;
    r = razr * 5;
    r.print();


    TapeMatrix<int> tape(3, 6); 
    for (i = 0; i < 6; i++)
    {
        // randomim 0..5 
        tape[i][i] = 0 + rand() % 5;
        if(i - 1 > 0) 
        {
            tape[i][i - 1] = 0 + rand() % 5;
        }
        if(i + 1 < 6) 
        {
            tape[i][i + 1] = 0 + rand() % 5;
        }
    }
    cout << "Tape Matrix: \n";
    cout << tape;

    TapeMatrix<int> t(3, 6);

    cout << "Tape matrix t = tape + tape: " << endl;
    t = tape + tape;
    cout << t;

    cout << "Tape matrix t = tape + 5: " << endl;
    t = tape + 5;
    cout << t;

    a.WriteFile(PATH);
    TMatrix<int> m(5);
    m.ReadFile(PATH, m);

    cout << "After read file m = " << endl << m << endl;

    system("pause");
    return 0;
}