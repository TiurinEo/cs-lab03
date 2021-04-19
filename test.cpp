#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_3otric() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_3equal() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}
void
test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 1);
    assert(max == 1);
}
int
main() {
    test_positive();
    test_3otric();
    test_3equal();
    test_empty();
}
