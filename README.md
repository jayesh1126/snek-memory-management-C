# Snek Memory Management (C Runtime Exercise)

This project explores **manual memory management in C** by building a simple object system called **Snek Objects**.

It started as a tagged union-based runtime, and has now evolved through multiple memory management strategies:

1. **Reference Counting Garbage Collector**
2. **Mark-and-Sweep Garbage Collector (final stage)**

This project demonstrates how different garbage collection strategies behave in a custom runtime environment.

---

## Overview

Snek Objects form a lightweight dynamic type system in C. Each object stores a type tag and a union of possible values, allowing it to represent multiple data types in a single structure.

Supported types include:
- Integers
- Floats
- Strings
- 3D Vectors
- Arrays

---

## Evolution of Memory Management

### 1. Reference Counting Garbage Collector

The first GC implementation used **reference counting**, where each object tracks how many references point to it.

**Key properties:**
- Immediate deallocation when refcount reaches zero
- Simple and deterministic memory cleanup
- Easy to reason about locally

**Limitations:**
- Cannot handle cyclic references
- Requires careful updates on every reference mutation
- Overhead on every assignment/update

---

### 2. Mark-and-Sweep Garbage Collector (Final Implementation)

The second GC implementation replaces reference counting with a **tracing garbage collector**.

It operates in three phases:

#### Mark
Scan all VM stack frames and mark root objects as reachable.

#### Trace
Traverse the object graph using a worklist (gray stack), recursively marking all reachable objects.

#### Sweep
Iterate over all tracked heap objects and free those that were not marked during traversal.

---

## Features

- Tagged union-based object system
- Heap-allocated objects using `malloc` / `calloc`
- Two GC strategies implemented:
  - Reference counting GC (initial version)
  - Mark-and-sweep GC (final version)
- VM-style object tracking system
- Stack-frame based root set management
- Graph traversal of object references
- Support for nested structures (Vectors + Arrays)
- Safe array indexing with bounds checking
- Basic arithmetic operations between objects (`snek_add`)

---

## What I Learned

- Manual memory management in C
- Trade-offs between reference counting and tracing GC
- How cycles break reference counting systems
- Root-set based garbage collection design
- Graph traversal algorithms in memory systems
- Object ownership and lifecycle design in runtimes
- How real language runtimes structure memory (VM + heap + GC phases)

---

## Build & Run

```bash
gcc *.c -o app
./app
