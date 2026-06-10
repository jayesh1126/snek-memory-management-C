# Snek Memory Management (C Runtime Exercise)

A small C project implementing a basic dynamic object system similar to a simplified runtime for a dynamically typed language.

## Overview

This project explores manual memory management in C by building a simple "object system" called **Snek Objects**. Each object carries a type tag and a union of possible values, allowing it to represent multiple data types in a single structure.

Supported types include:
- Integers
- Floats
- Strings
- 3D Vectors
- Arrays

## Features

- Tagged union-based object system
- Heap-allocated objects using `malloc` / `calloc`
- String duplication with proper null-termination handling
- Vector3 support with recursive operations
- Dynamic arrays with indexed access
- Safe array bounds checking
- Basic arithmetic operations between objects (`snek_add`)
- Length calculation for different types (`snek_length`)

## What I Learned

- Manual memory allocation and ownership in C
- Handling strings safely with `malloc`, `strcpy`, and `strlen`
- Designing tagged unions for polymorphism
- Implementing recursive operations on composite types
- Building simple runtime-like behaviour in a low-level language

## Build

Compile with GCC:

```bash
gcc main.c snekobject.c -o app
