// Credit: Louis Stuber (IBM Client Center Montpellier)
#include <stdio.h>

#define WAIT_TIME 100000000

double do_things1(int i);
double do_things2(int i);

double do_things_main(int i) {
    double j = i / 2;

    for(int t = 0; t < i; ++t) {
        j = (1 + j) * j / t;
    }

    return j;
}

int main() {
    double a, b, c;
    a = do_things_main(WAIT_TIME * 2);  // 40% of time, a.out
    b = do_things1(WAIT_TIME);          // 20% of time, libdo1.so
    c = do_things2(WAIT_TIME * 2);      // 40% of time, libdo2.so
    puts("OK");
    return (int)(a + b + c);
}
