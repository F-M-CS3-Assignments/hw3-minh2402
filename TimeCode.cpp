// AUTHOR: DUC MINH PHAM
// DATE: FEB 18, 2025

#include "TimeCode.h"
#include <iostream>
#include <assert.h>

using namespace std;

// Test Cases
void TestConstructor() {
    TimeCode tc(1, 30, 45);
    assert(tc.ToString() == "1:30:45");
    cout << "Constructor test passed!" << endl;
}

void TestArithmeticOperators() {
    TimeCode tc1(1, 0, 0);
    TimeCode tc2(0, 30, 0);
    TimeCode sum = tc1 + tc2;
    assert(sum.ToString() == "1:30:0");
    
    TimeCode diff = tc1 - tc2;
    assert(diff.ToString() == "0:30:0");
    
    cout << "Arithmetic operators test passed!" << endl;
}

void TestEdgeCases() {
    cout << "Testing Edge Cases" << endl;

    // Test large inputs
    TimeCode largeTC(10000, 59, 59);
    assert(largeTC.ToString() == "10000:59:59");

    // Test zero inputs
    TimeCode zeroTC;
    assert(zeroTC.ToString() == "0:0:0");

    // Test subtraction edge case
    try {
        TimeCode t1(1, 0, 0);
        TimeCode t2(2, 0, 0);
        TimeCode t3 = t1 - t2;
        assert(false);  // Should not reach here
    } catch (const invalid_argument& e) {
        cout << "Proper exception caught for negative subtraction" << endl;
    }
    
    cout << "PASSED Edge Cases!" << endl;
}

int main() {
    TestConstructor();
    TestArithmeticOperators();
    TestEdgeCases();
    cout << "ALL TESTS PASSED!" << endl;
    return 0;
}
