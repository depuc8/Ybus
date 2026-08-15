# Ybus Matrix Generator

A C++ program for constructing the bus admittance (Ybus) matrix from transmission line data.

## Project Structure

```text
.
├── Makefile
├── README.md
├── include/
│   └── Ybus.h
├── src/
│   └── Ybus.cpp
└── example/
    └── example_line_data.txt
```

The `example/` directory contains `example_line_data.txt`, which demonstrates the required input format.

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

## Running

Run the executable from the project root.

```bash
./Ybus
```

When prompted, enter the path to the input file. For example:

```text
example/example_line_data.txt
```

## Input File Format

The input file must follow the same format as `example/example_line_data.txt` in the `example/` directory.

Each line must contain six whitespace-separated values in the following order:

```text
FromBus ToBus R X B Tap
```

Where:

| Column | Description |
|--------|-------------|
| FromBus | Sending bus number |
| ToBus | Receiving bus number |
| R | Line resistance |
| X | Line reactance |
| B | Line charging susceptance |
| Tap | Transformer tap ratio (use `0` for a tap ratio of `1`) |

Example:

```text
1 2 0.02 0.06 0.03 0
2 3 0.08 0.24 0.025 1
3 4 0.06 0.18 0.02 0
```

The amount of spacing between the numbers does not matter. Values may be separated by one or more spaces or tabs, as long as each line contains exactly six values in the correct order.

The program expects this format. Using a different input structure may result in parsing errors or incorrect output.

## Output Options

After constructing the Ybus matrix, the program provides three output options:

1. **Print Ybus Matrix** — Displays the matrix in the terminal.
2. **Write Ybus Matrix to File** — Writes the matrix to an output file.
3. **Print and Write to File** — Displays the matrix in the terminal and writes it to an output file.

The output file is automatically created using the input filename.

Examples:

| Input File | Output File |
|------------|-------------|
| `data.txt` | `ybus_data.txt` |
| `linedata.txt` | `ybus_linedata.txt` |
| `example_line_data.txt` | `ybus_example_line_data.txt` |

The output file is created in the same directory as the input file.

## Notes
If you encounter any issues, unexpected behavior, or have suggestions for improvements, please report them through the repository's **Issues** section.
