#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

long double x[5], y[5], a[5], b[4], c[3], d;
long double forward_dy_dx, backward_dy_dx, central_dy_dx, stirling_dy_dx, pochodna, dydx[4];
int i,j;
long double x0, h;

long double Pochodna(double x0)
{
    pochodna = 5*x0*x0*x0*x0  - 60 *x0*x0*x0 + 255 *x0*x0 - 450 * x0 + 274;
  
    for (j = 0; j < 3; j++)
    {
        if (j == 0)
        {
            cout << "Blad bezwzgledny dla roznicy w przod =  " << fabs(pochodna - dydx[j]) << endl;
            cout << "Blad wzgledny dla roznicy w przod =  " << ((fabs(pochodna - dydx[j])) / dydx[j]) << endl;
            cout << endl;
        }
        if (j == 1)
        {
            cout << "Blad bezwzgledny dla roznicy w tyl =  " << fabs(pochodna - dydx[j]) << endl;
            cout << "Blad wzgledny dla roznicy w tyl =  " << ((fabs(pochodna - dydx[j])) / dydx[j])  << endl;
            cout << endl;
        }
        if (j == 2)
        {
            cout << "Blad bezwzgledny dla wzoru Stirlinga=  " << fabs(pochodna - dydx[j]) << endl;
            cout << "Blad wzgledny dla wzoru Stirlinga  =  " << ((fabs(pochodna - dydx[j])) / dydx[j])  << endl;
            cout << endl;
        }

        
    }

    return pochodna;
}
long double Forward(double x0, double h)
{

    for (i = 0; i < 5; i++) //Wyliczanie x
    {
        if (i == 0)
            x[i] = x0;
        else
        {
            x[i] = x0 + h;
            x0 = x[i];
        }
    }

    for (i = 0; i < 5; i++)
    {// Wyliczanie f(x)
        y[i] = x[i]*x[i]*x[i]*x[i]*x[i] - 15 * x[i]*x[i]*x[i]*x[i] + 85*x[i]*x[i]*x[i] - 225 *x[i]*x[i] + 274 * x[i] - 120;
        
    }
    cout << "f(" << x[0] << ") = " << y[0] << endl;
    cout << endl;


    for (i = 0; i < 4; i++) // Î”y
        a[i] = (y[i + 1] - y[i]);

    for (i = 0; i < 3; i++) // Î”^2 y
        b[i] = (a[i + 1] - a[i]);


    for (i = 0; i < 2; i++) // Î”^3 y
        c[i] = (b[i + 1] - b[i]);

     d = (c[1] - c[0]); // Î”^4 y

    forward_dy_dx = (1 / h) * (a[0] - (1.0 / 2.0) * b[0] + (1.0 / 3.0) * c[0] - (1.0 / 4.0) * d);
    dydx[0] = forward_dy_dx;
    return forward_dy_dx;
}

long double Backward(double x0, double h)
{
    for (i = 0; i < 5; i++) //Wyliczanie x
    {
        if (i == 0)
        {
            x[i] = x0 - 4 * h;
            x0 = x[i];
        }
        else
        {
            x[i] = x0 + h;
            x0 = x[i];
        }

    }
    for (i = 0; i < 5; i++) // Wyliczanie f(x)
    {
        y[i] =  x[i]*x[i]*x[i]*x[i]*x[i] - 15 * x[i]*x[i]*x[i]*x[i] + 85*x[i]*x[i]*x[i] - 225 *x[i]*x[i] + 274 * x[i] - 120;;

    }
    for (i = 0; i < 4; i++) // Î”y
        a[i] = (y[i + 1] - y[i]);


    for (i = 0; i < 3; i++) // Î”^2 y
        b[i] = (a[i + 1] - a[i]);


    for (i = 0; i < 2; i++) // Î”^3 y
        c[i] = (b[i + 1] - b[i]);

    d = (c[1] - c[0]); // Î”^4 y

   
    backward_dy_dx = (1.0 / h) * (a[3] + (1.0 / 2.0) * b[2] + (1.0 / 3.0) * c[1] + (1.0 / 4.0) * d);
    dydx[1] = backward_dy_dx;
    return backward_dy_dx;
    

}
long double Central(double x0, double h)
{
    for (i = 0; i < 5; i++) // wyliczanie x
    {
        if (i == 0)
        {
            x[i] = x0 - 2 * h;
            x0 = x[i];
        }
        else
        {
            x[i] = x0 + h;
            x0 = x[i];
        }
    }

    for (i = 0; i < 5; i++) // Wyliczanie f(x)
        y[i] =  x[i]*x[i]*x[i]*x[i]*x[i] - 15 * x[i]*x[i]*x[i]*x[i] + 85*x[i]*x[i]*x[i] - 225 *x[i]*x[i] + 274 * x[i] - 120;;


    for (i = 0; i < 4; i++) // Î”y
        a[i] = (y[i + 1] - y[i]);


    for (i = 0; i < 3; i++) // Î”^2 y
        b[i] = (a[i + 1] - a[i]);


    for (i = 0; i < 2; i++) // Î”^3 y
        c[i] = (b[i + 1] - b[i]);


    d = (c[1] - c[0]); // Î”^4 y

    central_dy_dx = (1.0 / h) * (((a[1] + a[2]) / 2.0) - (1.0 / 6.0) * ((c[0] + c[1]) / 2.0));
    stirling_dy_dx = ((1.0 / h) * ((a[2] + a[1]) / 2) - (1.0 / 6.0) * (c[1] - c[0]) / 2);
    dydx[2] = stirling_dy_dx;
    return central_dy_dx;
    return stirling_dy_dx;
}

int main()
{
   
    cout << "Podaj swoj x0" << endl;
    cin >> x0;

    cout << "Podaj swoj krok h" << endl;
    cin >> h;

    Forward(x0, h);
    cout << "Wynik dla roznic w przod = " << forward_dy_dx << endl;
    cout << endl;

    Backward(x0, h);
    cout << "Wynik dla roznic w tyl = " << backward_dy_dx << endl;
    cout << endl;

    Central(x0, h);
    cout << "Wynik dla wzoru Stirlinga = " << stirling_dy_dx << endl;
    cout << endl;
    cout << "Wynik dla roznic centralnych = " << central_dy_dx << endl;
    cout << endl;

    Pochodna(x0);
    cout << "Wynik dla pochodnej wyznaczonej analitycznie = " << pochodna << endl;

    return 0;
}
