🍽️ **philosophers**

This repository contains a solution to the philosophers project from the **third circle** of the **42 school curriculum**.
The project simulates the classic Dining Philosophers problem, a fundamental concurrency challenge in computer science.

🚀 **Project Overview**

The philosophers problem models several philosophers sitting around a table with forks between them.
Each philosopher alternates between thinking and eating, but must pick up two forks to eat.
The challenge is to avoid deadlocks, starvation, and ensure proper synchronization.

This project tackles:

Real-world concurrency and synchronization issues

Thread management using POSIX threads (pthread)

Mutexes to prevent race conditions on shared forks

Time management to track philosophers’ states accurately


🧠 **Custom Utilities**

Garbage Collector

Simplifies memory management by tracking all dynamic allocations and freeing them reliably at program termination.

Waiter Thread

A dedicated thread controlling philosophers’ lifecycle, monitoring their states, and ensuring no philosopher starves or deadlocks occur.


🔧 **Key Features**

Fork acquisition with proper mutex locking

Philosopher lifecycle management (think, eat, sleep)

Thread-safe printing for console output

Timed checks for philosopher death conditions

Graceful shutdown and resource cleanup


💬 **Example Usage**

make

./philosophers 5 800 200 200

5 philosophers

800 milliseconds to die

200 milliseconds to eat

200 milliseconds to sleep
