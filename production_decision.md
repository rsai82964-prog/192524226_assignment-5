# B4.3 Production Decision
The polymorphic design is suitable as a maintainable core for 15 hospitals and 200,000 bills/day: each bill is processed through a common interface in O(1) dispatch time, so processing n bills is O(n). New bill and payer types can be added as derived classes without modifying the existing processing loop. Exceptions suit exceptional failures; routine validation can use return-style results if invalid input is frequent.

This assignment prototype is not a complete production hospital system. Production would also require persistent transactions, audit logs, authentication, authorization, concurrency control, idempotency, monitoring, backups and recovery.

Alternative configuration/plugin rules: rates can be loaded from data files. A hash lookup is expected O(1), a sorted rule lookup O(log r), plus rule interpretation; rule storage is O(r). This enables rate changes without recompilation but requires schema validation, versioning, security and audit controls. A hybrid is sensible: stable C++ polymorphic interfaces with configurable package rates.
