# B3 – Performance
Compile with `g++ -std=c++17 -O2 -Wall -Wextra`. The first program compares virtual dispatch, tagged switch and std::variant/std::visit for 1,000, 1,000,000 and 10,000,000 records. The second compares return-code and exception validation at 0%, 1% and 50% invalid rates. Timings vary by machine; repeat and compare medians.
