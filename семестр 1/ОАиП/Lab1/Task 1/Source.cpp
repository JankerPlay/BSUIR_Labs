//#include <iostream>
//int main() {
  //  using namespace std;
    //float a,b,c,d,e,f,g,x,y;
   // cout << "x = ";
 //   cin >> x;
//    a = x * x;
//    b = 23 * a;
//    c = b + 32;
 //   d = c * x;
//    e = 69 * a;
//    f = e + 8;
 //   g = d + f;
 //   y = f - d;
 //   std::cout << "1-e = " << g;
//    std::cout << "\n2-å = " << y;
//    return 0;
//}
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
int main() {
    long int W, H, x1, y1, x2, y2, w, h, a, b, c, d, a1, b1, a3, a4, a5;
    cin >> W >> H >> x2 >> y2 >> x1 >> y1 >> w >> h;
    a3 = x2 - x1;
    a4 = y2 - y1;
    if ((H - a4 <= h and W <= w) or (W - a3 <= w and H <= h)
    {
        a = H - y2;
            b = W - x2;
            c = x2 + w - W;
            d = y2 + h - H;
            if (c >= 0 and d >= 0)
            {
                a5 = c + d;
                    cout << a5;
            }
            else if (c < 0 and d >= 0)
                cout << d;
            else if (c >= 0 and d < 0)
                cout << c;
    }
    else
        cout << "-1";
    return 0;
}