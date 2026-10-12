#!/usr/bin/env python3
"""Local C++ runner. expected.txt enables whitespace-token comparison."""
import argparse
from itertools import zip_longest
import os
from pathlib import Path
import shutil
import subprocess
import time

ROOT = Path(__file__).resolve().parent.parent


def first_difference(expected, actual):
    def tokens(data):
        for number, line in enumerate(data.splitlines(), 1):
            for token in line.split():
                yield token, number, line.decode('utf-8', errors='replace')

    for wanted, got in zip_longest(tokens(expected), tokens(actual)):
        if wanted is not None and got is not None and wanted[0] == got[0]:
            continue
        number = got[1] if got is not None else wanted[1]
        detail = f'\n[First mismatch at line {number}]\n'
        detail += (f'Expected (line {wanted[1]}): {wanted[2]}\n'
                   if wanted is not None else 'Expected: <end of output>\n')
        detail += (f'Actual   (line {got[1]}): {got[2]}\n'
                   if got is not None else 'Actual: <end of output>\n')
        return detail
    return ''


def run(timeout, debug):
    build = ROOT / '.build'
    build.mkdir(exist_ok=True)
    compiler = os.environ.get('CXX') or shutil.which('clang++') or shutil.which('g++')
    if not compiler:
        report('Compiler not found. Install a C++ compiler or set CXX.')
        return 1
    flags = ['-std=c++23', '-Wall', '-Wextra', '-Wshadow', '-DLOCAL']
    flags += ['-O0', '-g', '-fsanitize=address,undefined', '-fno-omit-frame-pointer'] if debug else ['-O2']
    try:
        result = subprocess.run([compiler, *flags, str(ROOT / 'main.cpp'), '-o', str(build / 'main')],
                                capture_output=True, text=True)
    except OSError as error:
        report(f'Compiler error: {error}\n')
        return 1
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
            status, code = f'TLE (time limit exceeded: {timeout:g} s)', 1
        except OSError as error:
            status, code = f'Runtime error: {error}', 1
    elapsed = (time.perf_counter() - start) * 1000
    actual = (build / 'stdout.txt').read_bytes()
    expected = ROOT / 'expected.txt'
    expected_bytes = expected.read_bytes() if expected.exists() else None
    unchecked = expected_bytes is not None and expected_bytes.strip() == b'NVM'
    difference = ''
    if code == 0 and expected_bytes is not None and not unchecked:
        match = actual.split() == expected_bytes.split()
        status, code = ('Accepted (local test)', 0) if match else ('Wrong answer (local test)', 1)
        if not match:
            difference = first_difference(expected_bytes, actual)
    body = '' if difference else actual.decode('utf-8', errors='replace')
    if body and not body.endswith('\n'):
        body += '\n'
    if body:
        body += '\n'
    body += (f'--- Total execution time: {elapsed:.2f} ms ---\n'
             if code == 0 and unchecked
             else f'--- {status} | Time: {elapsed:.2f} ms ---\n')
    body += difference
    errors = (build / 'stderr.txt').read_text(errors='replace')
    if errors:
        body += '\n[debug / stderr]\n' + errors
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
