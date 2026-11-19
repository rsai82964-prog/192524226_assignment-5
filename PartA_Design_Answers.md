# PART A – DESIGN (25 marks)

## A1 – Polymorphic Bill Hierarchy
Common operations: `total()`, `type()`, `print()`. Common data: patient ID/name, bill number and date. Abstract `Bill` declares pure virtual `double total() const = 0`, pure virtual `std::string type() const = 0`, and a virtual destructor. Derived classes: `OutPatientBill`, `InPatientBill`, `DayCareBill`, `EmergencyBill`; each overrides `total()` and `type()`.

```text
                  <<abstract>> Bill
   patientId, patientName, billNo
   total() = 0; type() = 0; print(); virtual ~Bill()
              /        |        |        \
          OPBill     IPBill   DayCare   Emergency
```

SIMATS pseudocode:
```text
ALGORITHM CalculateDailyTotal(bills, n)
BEGIN
    dailyTotal ← 0
    FOR i ← 0 TO n - 1 DO
        dailyTotal ← dailyTotal + bills[i].total()
    END FOR
    DISPLAY dailyTotal
END
```
Alternative tagged structure: one `Bill` record stores a type field and all charge fields; a switch calculates the amount. Both take O(n) for n bills. The tagged record may reserve fields unused by a particular type. Adding a type requires changing the switch and record; a derived class usually leaves the processing loop unchanged.

## A2 – Runtime Binding
Early binding resolves non-virtual calls at compile time using static type. Late binding resolves virtual calls at runtime using dynamic type. `Bill* b = new OPBill; b->total()` invokes `OPBill::total()`.

Conceptual vtables (the C++ standard does not mandate a physical vtable layout):
```text
Bill: total -> pure virtual; type -> pure virtual; destructor
OPBill: total -> OPBill::total; type -> OPBill::type; destructor chain
IPBill: total -> IPBill::total; type -> IPBill::type; destructor chain
```
A virtual destructor is required when deleting a derived object through a base pointer. Without it, behaviour is undefined.

Prediction for supplied program: `500 ~OPBill ~Bill`. `show()` itself is non-virtual, but calls virtual `total()`, so derived total is selected. Virtual destruction invokes derived then base destructors. Removing `virtual` from the base destructor makes deletion through `Bill*` undefined; any observed output is not guaranteed. AddressSanitizer may diagnose a new/delete type mismatch.

Alternative `dynamic_cast`: checking up to k derived types can require up to k casts per bill; virtual dispatch uses one virtual call. For fixed k, processing n bills remains O(n), but casts add branching and make extension less maintainable.

## A3 – Abstract Payer
`Payer` declares pure virtual `amountCovered(const Bill&) const` and a virtual destructor. `SelfPay` returns 0 covered by payer (patient pays full amount). `Insurance` stores cover limit and co-payment percent; illustrative amount is `min(limit, total × (1 - copay/100))`. `GovernmentScheme` stores fixed package rates and rejects unknown package codes. A new `CorporateTieUp : Payer` can be added without changing existing classes.

Alternative `std::function<double(const Bill&)>`: O(1) invocation asymptotically, like virtual dispatch; captured policy data stores limits/rates. Callable policies are concise for one operation; classes are clearer for complex state and multiple operations.

## A4 – Exception Strategy
Errors: negative charges, claim above cover, unknown package, missing patient record, invalid numeric text, out-of-range amount, allocation failure.

```text
std::exception
  └─ std::runtime_error
      └─ BillingError
          ├─ ClaimError
          ├─ PackageError
          └─ PatientError
std::bad_alloc, std::invalid_argument, std::out_of_range are standard exception types.
```
Validation, patient lookup, bill/payer calculation may throw. Destructors and cleanup must not throw; throwing during stack unwinding can call `std::terminate`. `noexcept` is suitable for cleanup operations that truly cannot throw.

Alternative return codes: return a `Status` enum and optionally an error message. Single validation normal/error handling is O(1), but every caller must check and propagate status. Error strings/results consume extra storage; return codes can suit frequent expected validation failures.

## A5 – Recovery and Rethrowing
Validation throws; service layer catches to log context and uses `throw;` to rethrow the same exception; application boundary catches typed billing errors; top-level boundary reports unknown failures. Stack unwinding destroys automatic objects in reverse construction order. RAII objects (`vector`, `string`, streams, `unique_ptr`) release resources automatically.

Prediction for Guard program: `~f caught 42 ~main`. `g` is destroyed during unwinding; catch prints; `m` is destroyed as main exits. `not printed` is skipped.

Manual `delete` in every catch path has similar asymptotic cleanup time but more code and more opportunities to miss cleanup when an error path is added. RAII is safer.
