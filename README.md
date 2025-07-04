# 🧠 head.c — Custom `head` Implementation in C

This program replicates core functionality of the UNIX `head` command, allowing you to display the first **K lines** of a file, with optional filtering for **even** or **odd** lines. It supports several command-line flags and is intended for educational or demonstration use in a UNIX environment.

---

## 📌 Author

**Name:** Abdus'Samad Bhadmus  

---

## ✅ Features

- ✅ Prints the first `K` lines of a file (`-n K`)
- ✅ Can print only **even** lines (`-e`) or **odd** lines (`-o`)
- ✅ Shows **help** message (`-h`)
- ✅ Displays **version and author info** (`-V`)
- ✅ Defaults to showing the **first 10 lines** if `-n` is omitted
- ✅ Handles input from `stdin` if no filename is provided
- 🚫 Does **not support** `-n` without a number (`-n` alone)
- ⚠️ Supports files with **maximum 100 lines** (due to `MAXLENGTH` cap)

---

## 🛠️ Compilation

Use `gcc` to compile:

```bash
gcc head.c -o head
```

---

## ▶️ Usage

```
./head [OPTIONS] [FILENAME]
```

### 🔹 Example Commands:

```bash
./head -n 3 input.txt         # Print first 3 lines
./head input.txt              # Print first 10 lines (default)
./head -n 5 -e input.txt      # Print first 5 even-numbered lines
./head -n 4 -o input.txt      # Print first 4 odd-numbered lines
./head -V                     # Show version information
./head -h                     # Show help menu
```

---

## 🔣 Command-Line Options

| Option | Description |
|--------|-------------|
| `-n K` | Print first `K` lines from the file (default = 10) |
| `-e`   | Print only **even-numbered** lines (1-based index) |
| `-o`   | Print only **odd-numbered** lines |
| `-V`   | Display version, author, email, and student number |
| `-h`   | Show help menu with option explanations |

> **Note:** If multiple options are given, the **last one overrides**. For example:  
> `./head -n 4 -e input.txt` → prints 4 even-numbered lines.

---

## 📄 Input File Format

- Any plain text file is valid.
- Maximum: **100 lines**, each line up to **100 characters**.
- If no file is provided, the program will read from **standard input (stdin)**.

---

## ⚠️ Limitations

- Files with more than **100 lines** will be truncated.
- `-n` **must** be followed by a valid positive integer. Invalid formats like `-n`, `-n abc`, or `-n 3a` will cause an error.
- Only **one** file is supported at a time.

---

## 🧪 Covered Test Cases

The following test cases have been implemented:

- `./head -n 3 input.txt`
- `./head -n 3 -e input.txt`
- `./head -n 3 -o input.txt`
- `./head -h`
- `./head -V`
- `./head input.txt`

> ❌ Not implemented: `./head -n` (without a value)

---

## 💡 Design Notes

- Uses `getopt()` from `<unistd.h>` to parse CLI arguments.
- File reading is done with `fgets()` and stored in a 2D character array.
- Modular design:
  - `processfile()` reads lines from file
  - `printfirstX()` handles different print modes (normal, even, odd)
  - `versioninformation()` and `helpmessage()` provide metadata/help

---

## 📦 Dependencies

- `stdio.h`
- `stdlib.h`
- `string.h`
- `unistd.h`

These are all standard C libraries on UNIX systems.

---

## 🧹 Exit Codes

- `0` — Success
- `1` — Any error (invalid arguments, file errors, etc.)

---

## 📃 License

This project is released for educational purposes. Free to use, modify, or extend.