#include <iostream>
#include <cassert>
#include "TimeCode.h"

using namespace std;

void TestDefaultConstructor() {
    cout << "Testing Default Constructor" << endl;
    TimeCode tc;
    assert(tc.ToString() == "0:0:0");
    cout << "PASSED!\n" << endl;
}

void TestConstructorAndGetters() {
    cout << "Testing Constructor and Getters" << endl;
    TimeCode tc(5, 2, 18);
    assert(tc.GetHours() == 5);
    assert(tc.GetMinutes() == 2);
    assert(tc.GetSeconds() == 18);
    cout << "PASSED!\n" << endl;
}

void TestAdditionOperator() {
    cout << "Testing Addition Operator" << endl;
    TimeCode tc1(2, 30, 15);
    TimeCode tc2(1, 45, 10);
    TimeCode result = tc1 + tc2;
    assert(result.ToString() == "4:15:25");
    cout << "PASSED!\n" << endl;
}

void TestDivisionOperator() {
    cout << "Testing Division Operator" << endl;
    TimeCode tc(6, 0, 0);
    TimeCode result = tc / 2.0;
    assert(result.ToString() == "3:0:0");
    cout << "PASSED!\n" << endl;
}

void TestTimeConversion() {
    cout << "Testing Time Conversion" << endl;
    TimeCode tc(3, 15, 45);
    assert(tc.GetTimeCodeAsSeconds() == (3 * 3600 + 15 * 60 + 45));
    cout << "PASSED!\n" << endl;
}

int main() {
    TestDefaultConstructor();
    TestConstructorAndGetters();
    TestAdditionOperator();
    TestDivisionOperator();
    TestTimeConversion();

    cout << "ALL TESTS PASSED!" << endl;
    return 0;
}
