# B2 – Errors
`predict_rethrow.cpp` is the supplied prediction experiment. `complete_todo_claim.cpp` completes TODOs. `error_conditions.cpp` tests invalid input, claim/package errors, numeric conversion, oversized allocation and catch-all recovery. The oversized request may throw `length_error` before `bad_alloc`; record the actual result.
