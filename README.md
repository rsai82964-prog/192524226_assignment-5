# DSA01 – Assignment 5 (CO5)

## Reliable Software with Runtime Polymorphism and Exceptions

### Student Details
- **Name:** P Rahul Sai
- **Register Number:** 192524226
- **Department:** Artificial Intelligence and Data Science
- **Subject:** Object Oriented Programming with C++

### Compiler Details
- **Compiler:** GNU G++ 14.2.0
- **Language:** C++
- **C++ Standard:** C++17

### Assignment Objectives
1. Understand runtime polymorphism and virtual functions.
2. Design reusable class hierarchies using inheritance.
3. Implement abstract classes and pure virtual functions.
4. Understand exception handling and custom exceptions.
5. Apply resource management and RAII principles.
6. Compare runtime performance using different approaches.
7. Design extensible and reliable billing software.

### Repository Structure

```text
DSA01-RegisterNumber-Assignment5/
│
├── PartA/
│   └── PartA_Design_Answers.md
│
├── Task01/
│   ├── complete_todo_b1.cpp
│   ├── polymorphic_billing.cpp
│   ├── predict_virtual_destructor.cpp
│   └── README.md
│
├── Task02/
│   ├── complete_todo_claim.cpp
│   ├── predict_rethrow.cpp
│   ├── error_conditions.cpp
│   ├── rethrow_by_value.cpp
│   └── README.md
│
├── Task03/
│   ├── benchmark.cpp
│   ├── exception_benchmark.cpp
│   └── README.md
│
├── Task04/
│   ├── extension_and_safety.cpp
│   ├── production_decision.md
│   └── README.md
│
├── outputs/
│   ├── Program output files
│   ├── Benchmark results
│   ├── Prediction records
│   └── Compiler information
│
└── README.md
```

### Compilation and Execution

Open the terminal in the respective task folder.

**Compile a C++ program:**

```bash
g++ -std=c++17 -Wall -Wextra -pedantic filename.cpp -o program
```

**Run the program:**

```bash
./program
```

**Compile benchmark programs:**

```bash
g++ -std=c++17 -O2 -Wall -Wextra benchmark.cpp -o benchmark
```

**Compile with AddressSanitizer:**

```bash
g++ -std=c++17 -g -fsanitize=address -fno-omit-frame-pointer filename.cpp -o program
```

### Expected Outcomes
- Implement polymorphic billing classes.
- Demonstrate virtual function execution and destructor behaviour.
- Handle billing errors using exception handling.
- Compare return-code and exception-based error handling.
- Measure performance using virtual functions, switch statements and `std::variant`.
- Extend the billing system with new bill and payer types.

### Conclusion

This assignment demonstrates how runtime polymorphism, inheritance and exception handling can be used to develop reusable, extensible and reliable C++ applications. It also provides practical experience in performance comparison, error handling and safe resource management.

### GitHub Repository
**Repository Link:** [Paste your GitHub repository URL here]
