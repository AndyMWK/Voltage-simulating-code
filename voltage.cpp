#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>


using namespace std;

//make this into an actual uncertainty-calculating program
/*frist specify the amount of variables measured. 
type it in to the equation function
store all the entries (need steps) of each variable
if multiple variables, equation must take into account corresponding values of each of the variables. 
*/
const double Vknot = 3.9;
const double e = 2.7182818;
const double timeConstant = 0.00019;

const double startX = 0.0;
const double interval = 0.000005;
const double limitX = 0.00005;

const double h = 0.00000001;

const double dx = 0.0000000004;//interval*0.005;

const int maxRandPrec = 1000;

double generateRand(double value, double uncert) {
    double min = value - uncert;
    //double max = value + uncert;
    int random = rand()%maxRandPrec;
    
    double rd = random*1.0;
    rd = rd/(maxRandPrec*1.0);
    
    double result = min + (rd * (2*uncert));

    return result;
}

struct val {
        double y;
        double x;
        double dy;
};

double f(double x) {
    
    double a = pow(e, (-x/timeConstant));
    double ans = Vknot * a;

    return ans;
}

double calcDerivative(double x) {

    /*uses the definition of a derivative
    a = argument of f(x+h)
    b = argument of f(x-h)
    c = argument of (f(x+h) - f(x-h))
    d = 2*h;
    e = (f(x+h) - f(x-h))/2*h*/


    double a = x+h;
    double b = x-h;
    double c = f(a) - f(b);
    double d = 2*h;
    double e = c/d;
    double res = e;
    return res; 

}

double uncert(double dx, double x) {
    double deriv = calcDerivative(x);
    double deriv_sq = pow(deriv, 2);

    double dx_sq = pow(dx, 2);

    double combo = deriv_sq*dx_sq;
    double res = pow(combo, 0.5);

    return res; 
}

int main() {

    vector <val> list;
    //vector <double> x_1;
    double x = startX;
    /*double x1 = x;
    while (x1 <= limit) {
        x_1.push_back(x1);
        x1 = x1 + interval;
    }*/
    srand(time(nullptr));
    
    while(x<= limitX) {
        

        val n;

        double yF = f(x);
        double dy = uncert(dx, x);
        double y = generateRand(yF, dy);

        n.y = y;
        n.dy = dy;
        n.x = x;

        list.push_back(n);
        x = x+interval;
    }

    cout << "Below are the values obtained:\n";
    for(val n: list) {
        cout << n.y << endl;
    }
    cout << "Below will be the time values:\n";
    for(val n: list) {
        cout << n.x << endl;
    }
    cout << "Below are the uncertainty values:\n";
    for(val n: list) {
        cout << n.dy << endl;
    }
    
}


