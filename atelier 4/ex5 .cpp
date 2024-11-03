#include <iostream>
using namespace std;

class Test {
public:
    static int count;

    void call() {
        count++;
    }
};

int Test::count = 0;  

int main() {
    Test test1, test2, test3;

    test1.call();
    test2.call();
    test3.call();
    test1.call();
    test2.call();
    test3.call();

    cout << "La fonction 'call' a été appelée " << Test::count << " fois." << endl;

    return 0;
}
