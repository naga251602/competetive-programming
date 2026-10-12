# Competitive programming workspace

## One-time VS Code setup

1. Open this folder in VS Code. Install the recommended Microsoft **C/C++** extension for completion and diagnostics.
2. Select **View → Editor Layout → Two Rows Right**.
3. Drag `main.cpp` into the left group, `input.txt` into the top-right group, and `output.txt` into the bottom-right group. VS Code remembers this arrangement.

```text
┌───────────────────────┬──────────────────┐
│                       │ input.txt        │
│ main.cpp              ├──────────────────┤
│                       │ output.txt       │
└───────────────────────┴──────────────────┘
```

## Daily workflow

- Write your solution inside `solve()` and paste a test into `input.txt`.
- Press **Cmd+Shift+B** on macOS (**Ctrl+Shift+B** on Linux/Windows) to save, compile, and run using the default **CP: Run** task. Program output, execution time, and available debug messages appear in `output.txt`.
- For automatic runs on save, use **Terminal → Run Task → CP: Watch (run on save)** once per session. Saving `main.cpp`, `input.txt`, or `expected.txt` reruns the test. Stop it with **Terminal → Terminate Task** before using other run tasks.
- To check an answer, create `expected.txt` with the correct output. The runner displays **Accepted (local test)** or **Wrong answer (local test)**. Wrong answers show only the first mismatch below the verdict in `output.txt`, with the expected and actual lines and their line numbers. Missing or extra output is marked `<end of output>`. Comparison ignores whitespace differences; it does not handle floating-point tolerances or problems with multiple valid answers. An empty file expects empty output.
- Put only `NVM` in `expected.txt` to skip comparison. `output.txt` shows program output, total execution time, and available debug messages. Timeouts still show **TLE**, and compilation or runtime errors still show their error details.
- Without `expected.txt`, successful execution displays **Run completed**. A local pass does not guarantee acceptance on a judge's hidden tests.
- **CP: Debug checks** enables AddressSanitizer and UndefinedBehaviorSanitizer. All local run tasks define `LOCAL`, so `dbg(x, y)` writes streamable values with a `[debug]` tag to the `[debug / stderr]` section. Without `LOCAL`, `dbg(...)` is disabled and its arguments are not evaluated. Submit `main.cpp` without defining `LOCAL`.

The default timeout is 2 seconds; compilation is excluded from elapsed time. Raw output is saved separately in `.build/stdout.txt`. Keep `output.txt` unedited so VS Code can refresh it from disk.

## Skip comparison with NVM

Set `expected.txt` to:

```text
NVM
```

Use uppercase `NVM` as the only content; surrounding spaces and newlines are allowed. Save the file and run **CP: Run**, or let **CP: Watch** rerun it. On success, `output.txt` contains the program's standard output, a **Total execution time** footer, and a `[debug / stderr]` section when stderr is present. Execution time excludes compilation. Debug messages are separate from standard output and do not affect answer comparison. Replace `NVM` with the expected answer to resume comparison.

Errors still appear in `output.txt` when using `NVM`:

| Result | What appears in `output.txt` |
| --- | --- |
| Time limit exceeded | `TLE (time limit exceeded: 2 s)` with elapsed time; the limit follows `--timeout`. |
| Compilation failure | `Compilation error` followed by compiler diagnostics. |
| Runtime failure | `Runtime error` with the exit code or launch error and available stderr. |

If `NVM` still appears as an expected answer in a mismatch, restart any **CP: Watch** task that was running before the runner was updated: use **Terminal → Terminate Task**, then **Terminal → Run Task → CP: Watch (run on save)**. An existing watcher keeps the runner code it loaded at startup.

## Terminal commands

```sh
bash run.sh
bash run.sh --watch
bash run.sh --debug
bash run.sh --timeout 5
```

Requires Python 3 and a compiler supporting C++23 mode. The runner compiles with `-std=c++23`, and VS Code IntelliSense is configured for C++23. The runner prefers `clang++`, falls back to `g++`, or uses the compiler path in `CXX`. The supplied IntelliSense compiler path is for macOS; adjust it on other systems. On Windows, run this workspace inside WSL with Python and G++ installed. Individual C++23 features depend on compiler and standard library support; select a compatible language standard when submitting to an online judge.

## Template

`main.cpp` includes fast I/O, integer aliases, min-heap alias, `chmin`/`chmax`, modular exponentiation, DSU, a Fenwick tree, and local debug printing. It uses standard headers so Apple Clang works without `bits/stdc++.h`.

Set `MULTIPLE_TESTS = true` when the first input value is a test count. The initial `solve()` is intentionally empty; implement the problem before expecting output. Submit only `main.cpp`.

VS Code references: [tasks](https://code.visualstudio.com/docs/debugtest/tasks), [editor layouts](https://code.visualstudio.com/docs/configure/custom-layout).
