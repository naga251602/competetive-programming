#!/usr/bin/env python3
"""Local C++ runner. expected.txt enables whitespace-token comparison."""
import argparse
import os
from pathlib import Path
import shutil
import subprocess
import time

ROOT = Path(__file__).resolve().parent.parent


def run(timeout, debug):
    build = ROOT / '.build'
    build.mkdir(exist_ok=True)
    compiler = os.environ.get('CXX') or shutil.which('clang++') or shutil.which('g++')
    if not compiler:
        report('Compiler not found. Install a C++ compiler or set CXX.')
        return 1
    flags = ['-std=c++17', '-Wall', '-Wextra', '-Wshadow', '-DLOCAL']
    flags += ['-O0', '-g', '-fsanitize=address,undefined', '-fno-omit-frame-pointer'] if debug else ['-O2']
    result = subprocess.run([compiler, *flags, str(ROOT / 'main.cpp'), '-o', str(build / 'main')],
                            capture_output=True, text=True)
    if result.returncode:
        report('Compilation error\n' + result.stdout + result.stderr)
        return 1
    (ROOT / 'input.txt').touch(exist_ok=True)
    start = time.perf_counter()
    status = 'Run completed (no expected.txt to check)'
    code = 0
    with (ROOT / 'input.txt').open('rb') as inp, (build / 'stdout.txt').open('wb') as out, (build / 'stderr.txt').open('wb') as err:
        try:
            result = subprocess.run([str(build / 'main')], stdin=inp, stdout=out, stderr=err,
                                    cwd=ROOT, timeout=timeout)
            if result.returncode:
                status, code = f'Runtime error (exit {result.returncode})', 1
        except subprocess.TimeoutExpired:
            status, code = f'Time limit exceeded ({timeout:g} s)', 1
    elapsed = (time.perf_counter() - start) * 1000
    actual = (build / 'stdout.txt').read_bytes()
    expected = ROOT / 'expected.txt'
    if code == 0 and expected.exists():
        match = actual.split() == expected.read_bytes().split()
        status, code = ('Accepted (local test)', 0) if match else ('Wrong answer (local test)', 1)
    body = actual.decode('utf-8', errors='replace')
    body += ('' if body.endswith('\n') or not body else '\n') + f'\n--- {status} | Time: {elapsed:.2f} ms ---\n'
    errors = (build / 'stderr.txt').read_text(errors='replace')
    if errors:
        body += '\n[stderr / debug]\n' + errors
    report(body)
    return code


def report(body):
    temp = ROOT / '.build' / 'output.tmp'
    temp.parent.mkdir(exist_ok=True)
    temp.write_text(body)
    temp.replace(ROOT / 'output.txt')
    print(body, flush=True)


def fingerprint():
    return tuple((ROOT / name).read_bytes() if (ROOT / name).exists() else None
                 for name in ('main.cpp', 'input.txt', 'expected.txt'))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--watch', action='store_true')
    parser.add_argument('--debug', action='store_true')
    parser.add_argument('--timeout', type=float, default=2)
    args = parser.parse_args()
    if args.timeout <= 0:
        parser.error('--timeout must be positive')
    if not args.watch:
        return run(args.timeout, args.debug)
    print('Watching main.cpp, input.txt and expected.txt. Stop with Ctrl+C.', flush=True)
    previous = None
    try:
        while True:
            current = fingerprint()
            if current != previous:
                time.sleep(0.15)
                previous = fingerprint()
                run(args.timeout, args.debug)
            time.sleep(0.2)
    except KeyboardInterrupt:
        return 0


if __name__ == '__main__':
    raise SystemExit(main())
