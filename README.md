# Ybus Matrix Generator

A C++ program and API for constructing the bus admittance (Ybus) matrix from transmission line data.

## Project Structure

```text
.
├── Makefile
├── README.md
├── include/
│   └── Ybus.h
├── src/
│   ├── Ybus.cpp
│   └── main.cpp
└── example/
    └── example_line_data.txt
```

The `example/` directory contains `example_line_data.txt`, which demonstrates the required input format.

## Clone the Repository

Clone the repository before building the project:

```bash
git clone git@github.com:depuc8/Ybus.git
```

## Building

Compile the program using the provided Makefile.

```bash
make
```

This creates the executable:

```text
Ybus
```

To remove the executable and object files:

```bash
make clean
```

## Running the Test Driver

The project includes a built-in test driver in `src/main.cpp`. Run the executable from the project root:

```bash
./Ybus
```

When prompted, enter the path to the input file. For example:

```text
example/example_line_data.txt
```

The test driver will automatically execute and demonstrate the different API configurations (printing, writing to file, and quietly returning the matrix data) using the file provided.

## API Usage

The core functionality is exposed as a clean C++ API. Instead of interacting with a console menu, you can directly integrate the `Ybus` generator into your own power flow solvers or C++ projects.

Include the header and call the function with the file path and your desired output behavior:

```cpp
#include "include/Ybus.h"

// The function signature:
// ComplexMatrix Ybus(const std::string& input_file, int choice);

// Example usage:
std::string file_path = "example/example_line_data.txt";

// choice = 0: Returns the Ybus matrix quietly (best for pure computation)
auto my_ybus = Ybus(file_path, 0); 

// choice = 1: Returns the Ybus matrix AND prints it to the terminal
auto my_ybus = Ybus(file_path, 1); 

// choice = 2: Returns the Ybus matrix AND writes it to an output file
auto my_ybus = Ybus(file_path, 2); 

// choice = 3: Returns the Ybus matrix, prints it, AND writes it to a file
auto my_ybus = Ybus(file_path, 3); 
```

*Please refer to `src/main.cpp` for a complete working example of how to implement and test the API.*

### Output File Generation

If you use `choice = 2` or `choice = 3`, the program will automatically generate an output text file containing the formatted matrix in the same directory as your input file.

| Input File | Output File |
|------------|-------------|
| `data.txt` | `ybus_data.txt` |
| `linedata.txt` | `ybus_linedata.txt` |
| `example_line_data.txt` | `ybus_example_line_data.txt` |

## Input File Format

The input file must follow the same format as `example/example_line_data.txt` in the `example/` directory.

Each line must contain six whitespace-separated values in the following order:

```text
FromBus ToBus R X B Tap
```

Where:

| Column | Description |
|--------|-------------|
| FromBus | Sending bus number (0 for Reference/Ground) |
| ToBus | Receiving bus number (0 for Reference/Ground) |
| R | Line resistance |
| X | Line reactance |
| B | Line charging susceptance |
| Tap | Transformer tap ratio (use `0` for a tap ratio of `1`) |

Example:

```text
1 2 0.02 0.06 0.03 0
2 3 0.08 0.24 0.025 1
3 4 0.06 0.18 0.02 0
2 0 0.00 0.15 0.00 0
```

The amount of spacing between the numbers does not matter. Values may be separated by one or more spaces or tabs, as long as each line contains exactly six values in the correct order. The program includes safety checks and will abort if the data format is corrupted (e.g., characters instead of numbers).

## Notes
If you encounter any issues, unexpected behavior, or have suggestions for improvements, please report them through the repository's **Issues** section.
