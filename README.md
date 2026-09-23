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
- Press **Cmd+Shift+B** on macOS (**Ctrl+Shift+B** on Linux/Windows) to save, compile, and run using the default **CP: Run** task. Output and elapsed wall time appear in `output.txt`.
- For automatic runs on save, use **Terminal → Run Task → CP: Watch (run on save)** once per session. Saving `main.cpp`, `input.txt`, or `expected.txt` reruns the test. Stop it with **Terminal → Terminate Task** before using other run tasks.
- To check an answer, create `expected.txt` with the correct output. The runner displays **Accepted (local test)** or **Wrong answer (local test)**. Comparison ignores whitespace differences; it does not handle floating-point tolerances or problems with multiple valid answers. Delete `expected.txt` when switching to unchecked tests. An empty file expects empty output.
- Without `expected.txt`, successful execution displays **Run completed**. A local pass does not guarantee acceptance on a judge's hidden tests.
- **CP: Debug checks** enables AddressSanitizer and UndefinedBehaviorSanitizer. `dbg(x, y)` writes streamable values to the debug section locally and is disabled on submission.

The default timeout is 2 seconds; compilation is excluded from elapsed time. Raw output is saved separately in `.build/stdout.txt`. Keep `output.txt` unedited so VS Code can refresh it from disk.

## Terminal commands

```sh
bash run.sh
bash run.sh --watch
bash run.sh --debug
bash run.sh --timeout 5
```

Requires Python 3 and a C++17 compiler. The runner prefers `clang++`, falls back to `g++`, or uses the compiler path in `CXX`. The supplied IntelliSense compiler path is for macOS; adjust it on other systems. On Windows, run this workspace inside WSL with Python and G++ installed.

## Template

`main.cpp` includes fast I/O, integer aliases, min-heap alias, `chmin`/`chmax`, modular exponentiation, DSU, a Fenwick tree, and local debug printing. It uses standard headers so Apple Clang works without `bits/stdc++.h`.

Set `MULTIPLE_TESTS = true` when the first input value is a test count. The initial `solve()` is intentionally empty; implement the problem before expecting output. Submit only `main.cpp`.

VS Code references: [tasks](https://code.visualstudio.com/docs/debugtest/tasks), [editor layouts](https://code.visualstudio.com/docs/configure/custom-layout).
