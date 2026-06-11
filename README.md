# Snek Memory Management (C Runtime Exercise)

This project explores **manual memory management in C** by building a simple object system called **Snek Objects**.

It started as a tagged union-based runtime, and has now been extended with a **reference counting garbage collector**. The next step will be implementing **mark-and-sweep GC**.

## Overview

Snek Objects form a lightweight dynamic type system in C. Each object stores a type tag and a union of possible values, allowing it to represent multiple data types in a single structure.

Supported types include:
- Integers
- Floats
- Strings
- 3D Vectors
- Arrays

## Features

- Tagged union-based object system
- Heap-allocated objects using `malloc` / `calloc`
- Reference counting garbage collection (automatic cleanup on refcount = 0)
- Container-aware ownership (Vectors and Arrays manage internal references safely)
- String duplication with proper null-termination handling
- Vector3 support with recursive operations
- Dynamic arrays with indexed access
- Safe array bounds checking
- Basic arithmetic operations between objects (`snek_add`)
- Length calculation for different types (`snek_length`)

## What I Learned

- Manual memory management in C
- How reference counting GC works internally
- Ownership models in composite data structures
- Recursive cleanup in container types
- Designing a simple runtime-like object system

## Build

```bash
gcc main.c snekobject.c -o app
./app
