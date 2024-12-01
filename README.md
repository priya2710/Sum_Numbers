# File Sum Compiler

This project is a multi-threaded C++ application that processes a set of text files containing integers, sums them up, and outputs the total sum.

## How to Run the Compiled Program

### 1. **Compile the Code**

To compile the code, use the following command:

```bash
g++ -std=c++17 -o sum_compiler files_sum.cpp -pthread
```

### 2. **Run the Compiled Program**

Once the code is compiled, you can run the program using the following command:

#### On Linux/macOS:
```bash
./sum_compiler
```

#### On Windows:
```bash
sum_compiler.exe
```

If the execution is successful, the following message will be printed:

```
Compilation successful and Total Sum: <answer>
```

---

## How to Use `system_creation.py` to Generate Sample Files

If you want to generate sample text files for testing, you can use the `system_creation.py` script. This script will create 100 text files with random integers inside the `text_files` directory.

### 1. **Run the Python Script**

To generate the sample files, run the following command:

```bash
python system_creation.py
```

This will populate the `text_files` directory with 100 `.txt` files, each containing random integers that the C++ program can then process.

---

This `README.md` now focuses solely on running the compiled program and generating the sample files with the Python script. Let me know if you need any further modifications!