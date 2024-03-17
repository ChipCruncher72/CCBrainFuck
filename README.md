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

Then, if you want to you can create a shortcut
```sh
export ccbf='path/to/exec'
```
on Windows
```ps1
New-Alias -Name ccbf -Value 'path\to\exec'
```


To run a brainfuck file you just need to include the path as an argument
```sh
ccbf 'path/to/brainfuck'
```

And you're done! Have fun with Brainfuck!

#### IMPORTANT:
Make sure you put the [{fmt} library](https://github.com/fmtlib/fmt) in libs/fmt or else it cannot compile

---

## Extra
The interpreter isn't *quite* finished yet; there is still some stuff in the works such as:
- Better onboarding
- QOL improvements (compiler flags such as -h, -v, --repl, -f, ...)
- Support for the .b extention
- Transpiler
