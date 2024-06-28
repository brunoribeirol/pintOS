<p align="center">
  <img
    src="https://img.shields.io/badge/Status-Finished%20-green?style=flat-square"
    alt="Status"
  />
</p>

<p align="center">
  <img
    src="https://img.shields.io/github/repo-size/brunoribeirol/pintOS?style=flat"
    alt="Repository Size"
  />
  <img
    src="https://img.shields.io/github/languages/count/brunoribeirol/pintOS?style=flat&logo=python"
    alt="Language Count"
  />
  <img
    src="https://img.shields.io/github/commit-activity/t/brunoribeirol/pintOS?style=flat&logo=github"
    alt="Commit Activity"
  />
  <a href="LICENSE.md"
    ><img
      src="https://img.shields.io/github/license/brunoribeirol/pintOS"
      alt="License"
  /></a>
</p>

# PintOS - Project 1 (Alarm Clock)

## 👀 Overview

This project extends the functionality of the thread system in PintOS, with a focus on synchronization and implementing a non-busy wait version of `timer_sleep()`

## 📝 Implementation Details

The goal of this project is to reimplement the `timer_sleep()` function in `devices/timer.c` to avoid busy waiting. This function suspends the calling thread until a specified number of timer ticks have elapsed.

### Function to Implement

- `void timer_sleep (int64_t ticks);`
  - Suspends the calling thread until at least `ticks` timer ticks have elapsed.
  - Threads do not need to wake up exactly after `ticks` ticks unless the system is idle.

## 📂 Modified Files:

- **`timer.c`**
  - Implemented `timer_sleep()`
  - Added `wake_up_thread(ticks);` in `timer_interrupt()`
- **`thread.h`**
  - Added `int64_t wake_up;` to the `struct thread`
  - Declared `typedef struct thread Thread;`
  - Added `void thread_sleep(int64_t ticks);`
  - Added `void wake_up_thread(int64_t ticks);`
- **`thread.c`**
  - Initialized `static struct list blocked_list;`
  - Initialized `list_init(&blocked_list);` in `void thread_init(void)`
  - Implemented `void thread_sleep(int64_t ticks);`
  - Implemented `void wake_up_thread(int64_t ticks);`
 
### 🛠️ Code Modifications:

- **`/*Start*/`**: Indicates the start of modifications
- **`/*End*/`**: Indicates the end of modifications
- Original code is commented using `//`

## 🛠️ Build Instructions

1. Navigate to the directory:
```bash
cd pintos/src/threads
```
2. Execute the command:
```bash
make   
```
 
## ⚙️ Running PintOS

Ensure PintOS is compiled before ruuning:
1. Navigate to the directory:
```bash
cd build
```
2. Execute the command:
```bash
pintos
```
3. Execute the command:
```bash
pintos -v -k -T 60 --qemu -- -q run alarm-single
```

## 🧪 Test Cases

Using the command `make check` checks all the tests of PintOS, but your program should only pass these tests:
- `alarm-single`
- `alarm-multiple`
- `alarm-simultaneous`
- `alarm-zero`
- `alarm-negative`
