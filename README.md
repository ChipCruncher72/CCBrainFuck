# CCBrainFuck
The better interpreter
---

## What is it?
CCBrainFuck (or CCBF for short) is a interpreter for the [Brainfuck Programming Language](https://en.wikipedia.org/wiki/Brainfuck)

---

## Installation
Required:
- CMake
- A C++ compiler (preferably clang)
- git (optional)

Clone the repository using `git clone` or download the zip file if you don't have git
```sh
git clone https://github.com/ChipCruncher72/CCBrainFuck
cd CCBrainFuck
```

Make a build directory and cd into it
```sh
mkdir build
cd build
```

Run CMake and build!
```sh
cmake ..
make
```

Then, if you want to you can create a shortcut to it if you need to
```sh
export ccbf='path/to/exec'
```

And you're done! Have fun with Brainfuck!
