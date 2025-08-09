MVP Requirements
Convert between a small, fixed set of units:

Length: m ↔ cm ↔ mm ↔ km, in ↔ ft ↔ yd ↔ mi

Mass: g ↔ kg, oz ↔ lb

Accept input via CLI flags or prompts.

Validate units; show a friendly error for unknown units.

Output a single numeric result with unit.

Non-Goals (MVP)
No custom units, no config files, no GUI.

CLI Spec
Command form:
convert <value> <from_unit> <to_unit>
Example: convert 2.5 km m -> 2500 m

If run without args, enter interactive mode (prompt for value/from/to).

Data Model / Design
Map each unit to a canonical base (e.g., meters for length, grams for mass).
Convert: value_in_base = value * factor[from]; out = value_in_base / factor[to].

Use unordered_map<string, double> for factors.

Errors / Edge Cases
Invalid unit → “Unsupported unit: …”

Converting across categories (e.g., kg → m) → “Incompatible units.”

Non-numeric value → “Invalid number.”

Acceptance Criteria
Known conversions return correct values within floating-point tolerance.

Bad inputs produce clear errors, program exits with non-zero status.