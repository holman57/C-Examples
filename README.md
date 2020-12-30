
## C Examples 
#### The `exec` family of functions in conjunction with forking, file descriptors, threading, and sockets.


hackr.io
C Tutorials and Courses
- https://hackr.io/tutorials/learn-c

The Archive of Interesting Code
- The Archive of Interesting Code is an effort on my part to code up interesting algorithms and data structures. https://www.keithschwarz.com/interesting/

Garbage Collection Algorithms
- http://dmitrysoshnikov.com/courses/essentials-of-garbage-collectors/
  - Writing a Memory Allocator
    - This is the 6th lecture from the Garbage Collection Algorithms class, devoted to the automatic memory management. http://dmitrysoshnikov.com/compilers/writing-a-memory-allocator/

Single-file public-domain/open source libraries with minimal dependencies
- a list of small, easy-to-integrate, portable libraries which are usable from C and/or C++ https://github.com/nothings/single_file_libs

Building Your Own C Interpreter
- https://www.drdobbs.com/cpp/building-your-own-c-interpreter/184408184

C Tutorials and Courses
- Learn C programming online from the best C tutorials submitted and voted by the programming community. https://hackr.io/tutorials/learn-c

Getting started with C programming
- A mac based lightning-fast start for absolute beginners https://not.cafe/2020/10/12/getting-started-with-c-programming.html

Learn C
- As C is a veteran programming languages there are tons of C communities, forums and tutorials. Top 10 Best C Tutorials. https://medium.com/hackr-io/learn-c-best-c-tutorials-for-beginners-949835f3f20a

C++: The Good Parts
- Jordan DeLong overviews the past, current and near future "good parts" of C++'s functional side through the colored lens of his biases. https://www.infoq.com/presentations/c-plus-plus-pros/?itm_source=presentations_about_CPlusPlus

Orthodox C++
- Orthodox C++ (sometimes referred as C+) is minimal subset of C++ that improves C, but avoids all unnecessary things from so called Modern C++. https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b#file-orthodoxc-md

Cosmopolitan libc
- Build-once run-anywhere c without devops https://justine.lol/cosmopolitan/index.html

---

How Does a C Debugger Work? (GDB Ptrace/x86 example)
- Linux ptrace API allows a (debugger) process to access low-level information about another process (the debuggee). https://blog.0x972.info/?d=2014/11/13/10/40/50-how-does-a-debugger-work

Bit Manipulation with C++20
- the class std::source_location http://www.modernescpp.com/index.php/bit-manipulation-with-c-20

libcu++
- the NVIDIA C++ Standard Library, is the C++ Standard Library for your entire system. It provides a heterogeneous implementation of the C++ Standard Library that can be used in and between CPU and GPU code. https://github.com/NVIDIA/libcudacxx

The Little Things
- Speeding up C++ compilation https://codingnest.com/the-little-things-speeding-up-c-compilation/

How expensive is integer-overflow trapping in C++?
- Integers in programming languages have a valid range but arithmetic operations can result in values that exceed such ranges. For example, adding two large integers can result in an integer that cannot be represented in the integer type. We often refer to such error conditions as overflows. https://lemire.me/blog/2020/09/23/how-expensive-is-integer-overflow-trapping-in-c/

SCC
- SCC is a limited C compiler producing tiny-model DOS COM files. It should run on most operating systems and can self-host under DOS2.0+ compatible systems with 128K RAM https://github.com/mras0/scc

w64devkit
- Portable C and C++ Development Kit for x64 Windows https://nullprogram.com/blog/2020/09/25/

Urkel 
- An optimized and cryptographically provable key-value store. Written in C. https://github.com/chjj/liburkel

chibicc: A Small C Compiler
- chibicc is yet another small C compiler that implements most C11 features. Even though it still probably falls into the "toy compilers" category just like other small compilers do, chibicc can compile several real-world programs, including Git, SQLite and libpng, without making modifications to the compiled programs. https://github.com/rui314/chibicc

Frama-C
- An extensible and collaborative platform dedicated to source-code analysis of C software. http://frama-c.com/index.html

RISC-V userspace emulator library
- https://github.com/fwsGonzo/libriscv

---

### Linear Algebra

- Are there any C++ (or C) libs that have NumPy-like arrays with support for slicing, vectorized operations, adding and subtracting contents element-by-element, etc.? https://stackoverflow.com/questions/11169418/numpy-style-arrays-for-c/40448758

XTensor
- Linear Algebra In C++ With XTensor Is Just Like Numpy https://towardsdatascience.com/linear-algebra-in-c-with-xtensor-is-just-like-numpy-1a6b1ee00736

---

### Articles

1. Is the C runtime and library a legitimate part of the Unix API? https://utcc.utoronto.ca/~cks/space/blog/unix/UnixAPIAndCRuntime
1. What does I/O bound really mean? Erik Engbrecht's Blog http://erikengbrecht.blogspot.com/2008/06/what-does-io-bound-really-mean.html?m=1
1. The Jim Roskind C/C++ Grammar https://blog.robertelder.org/jim-roskind-grammar/
1. A Special Kind of Hell - intmax_t in C and C++ https://thephd.github.io/intmax_t-hell-c++-c
1. Overloading by Return Type in C++ https://artificial-mind.net/blog/2020/10/10/return-type-overloading
1. Does C++ still deserve the bad rap it has had for so long? https://nibblestew.blogspot.com/2020/10/does-c-still-deserve-bad-rap-it-has-had.html
1. No, C++ still isn't cutting it. https://da-data.blogspot.com/2020/10/no-c-still-isnt-cutting-it.html
1. What's Wrong with C++ Templates? http://people.cs.uchicago.edu/~jacobm/pubs/templates.html
1. Multi-Level Break in C++ via IIFE https://artificial-mind.net/blog/2020/10/28/multi-level-break-iife
1. Fast programming languages: C, C++, Rust, and Assembly http://tempesta-tech.com/blog/fast-programming-languages-c-c++-rust-assembly
1. Why nullable types? https://medium.com/dartlang/why-nullable-types-7dd93c28c87a

---

### Papers

1. The Evolution of C Programming Practices: A Study of the Unix Operating System 1973-2015 https://ieeexplore.ieee.org/abstract/document/7886953
1. C source-to-source compiler enhancement from within https://hal.inria.fr/hal-02998412
1. Compiling without Continuations https://dl.acm.org/doi/10.1145/3062341.3062380
1. HardBound: Architectural Support for Spatial Safety of the C Programming Language https://dl.acm.org/doi/pdf/10.1145/1353535.1346295
1. Program Analysis and Specialization for the C Programming Language https://www.semanticscholar.org/paper/Program-Analysis-and-Specialization-for-the-C-Andersen-Lee/b7efe971a34a0f2482e0b2520ffb31062dcdde62
1. The Semantics of the C Programming Language http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.29.6755&rep=rep1&type=pdf
