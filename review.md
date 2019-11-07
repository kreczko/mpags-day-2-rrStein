# Comments
 - `edited-mpags-cipher.cpp` &rarr; `mpags-cipher.cpp`: the beaty of Git (or other version control systems) is that you do not need to do that and still have a backup available.
 - `CaesarKey` &rarr; `caesarKey`: variables should start with lower-case letter
 - formatting matters for bigger projects: `clang-format -i <files>` can do it automatically (or your IDE/editor)
 - one output variable is enough: can even simplify if-elseif
 - better names for inputFile and outputFile: add "Name" to distribguish them from the actual file constructs
 - `main()` function could be further broken down in smaller functions (e.g. encryption, output, etc) for readability
 - `transformChar`: `std::map` is relatively expensive to look up. A better solution would be to use an `std::array`, map the input onto an integer and use it as an index.
 - `transformChar`: uniform initialization for `std::map` allows to make it `const`
 - `transformChar`: innefficient memory use: a new map is created for every time `transformChar` is called. Instead you can use the `static` keyword to make sure the variable is only initialized once (it's a trick also used for SingleTons).


# Bugs
## Random results
```bash
./mpags-cipher -i ../test.txt -o ../output.txt -m encrypt
```
gives random results:

```bash
Writing transformed text into file: 
../output.txt
Write successful
phxlk@hyperion:~/Workspace/teaching/mpags-day-2-rrStein/build$ ./mpags-cipher -i ../test.txt -o ../output.txt -m encrypt
The input text is: 
EASYTRANSFORMATIONONETWOTHREE
The encrypted string is: 
EASYTRANSFORMATIONONETWOTHREE

Writing transformed text into file: 
../output.txt
Write successful
phxlk@hyperion:~/Workspace/teaching/mpags-day-2-rrStein/build$ ./mpags-cipher -i ../test.txt -o ../output.txt -m encrypt
The input text is: 
EASYTRANSFORMATIONONETWOTHREE
The encrypted string is: 
IEWCXVERWJSVQEXMSRSRIXASXLVII

Writing transformed text into file: 
../output.txt
Write successful
phxlk@hyperion:~/Workspace/teaching/mpags-day-2-rrStein/build$ ./mpags-cipher -i ../test.txt -o ../output.txt -m encrypt
The input text is: 
EASYTRANSFORMATIONONETWOTHREE
The encrypted string is: 
IEWCXVERWJSVQEXMSRSRIXASXLVII

Writing transformed text into file: 
../output.txt
Write successful
```

The reason is `int CaesarKey;` where no initial value is set and `processCommandLine`
will only set it if the `-key` optin is given (`else if (args[i] == "-key")`).
BTW: should be `--key`.

## Using side-effects in std::map::operator[]
In `transformChar`, `inputText += my_map[in_char];` no check is done for numbers.
Therefore `[]` is also called for characters for which it has no defined value, e.g. `E`.
Luckily, the return value is empty for these cases - but this is playing with fire.
The `std::map::at()` function is a safer way to do this and, in fact, preferred when you use the `const` keyword.

Safer:
```c++
// Map input numbers to their corresponding words
  const std::map<char, std::string> kLookupMap = {
    {'0', "ZERO"},
    {'1', "ONE"},
    {'2', "TWO"},
    {'3', "THREE"},
    {'4', "FOUR"},
    {'5', "FIVE"},
    {'6', "SIX"},
    {'7', "SEVEN"},
    {'8', "EIGHT"},
    {'9', "NINE"},
  };

  if(std::isdigit(in_char))
    inputText += kLookupMap.at(in_char);
```