# ball_sort
A brute-force solver for the Ball Sorting Puzzle.

## What is a Ball Sorting Puzzle?
A puzzle consists of a number of tubes filled with balls of different colours,
plus two empty tubes. A full tube contains four balls, and there are exactly
four balls of each colour.

The puzzle begins in a shuffled state, and the objective is to sort the balls
into full tubes of one colour each. Most initial configurations can be solved.

A move consists of taking a ball from one tube and placing it into another tube
that has space. If the destination contains balls, the colour of the top ball
must match the colour of the ball placed in it. If the tube is empty, any
colour ball can be placed in it.

For a fun logic puzzle, try to determine the minimum number of colours required
to create an unsolved puzzle configuration with no legal moves.

## Demo
![A demo of the program running](https://github.com/D4n93r3ux/ball_sort/assets/61416292/cce0551c-dac6-4aad-b23d-ffd75374b5b5)

*A short demo of the program running.*

## Usage
The project is a C++ terminal application and builds to an executable that
demonstrates the solution of one puzzle.

A `Puzzle` is instantiated by passing a vector of strings, with each character
representing a ball colour:

```cpp
Puzzle puzzle{{"DFHE", "ABAD", "EIIE", "BHII", "DHCC", "CBGF", "GGAC", "EBFF", "HDAG", "", ""}};
```

The number of strings in the vector must match the number of different
characters plus an additional two strings. The choice of initial configuration
is flexible, so this method allows the entry of a puzzle in a half-solved state.

The following is therefore also legal:
```cpp
Puzzle puzzle{{"DF", "ABAD", "EIIE", "BHII", "DHCC", "CBGF", "GGAC", "EBFF", "HDAG", "E", "H"}};
```

Alternatively, a `Puzzle` may be instantiated by passing a single string of
space-separated integers.

```cpp
Puzzle puzzle{"4 6 8 5 1 2 1 4 5 9 9 5 2 8 9 9 4 8 3 3 3 2 7 6 7 7 1 3 5 2 6 6 8 4 1 7"};
```

In this variant, the tubes of the puzzle will be filled sequentially,
bottom-to-top and left-to-right, with characters corresponding to each number.
Because this method is intended to produce a puzzle in its initial state, it
will automatically add the necessary extra empty tubes to make the puzzle
legal.

To solve the puzzle, the puzzle object is passed to the `solve` function.

```cpp
ballsort::solver::solve(puzzle);
```

This method can take an additional boolean parameter that determines whether to
display the solving process in the terminal, which defaults to `false`.

The solution history is stored in the puzzle object and can be played back by
passing the solved puzzle to the `play_solution` method.

```cpp
Solver::play_solution(puzzle);
```

## Building
Two build scripts are provided for debug and release builds. The binaries will
be output to a top-level `bin` directory.

Dependencies are currently managed with Conan, but support for alternative
dependency managers will be added at a later date.

## Run tests
If you would like to run tests, a `test.sh` script is also included. This will
build a Google Test executable.

## Known issues
Although all illegal and many wasteful moves have been eliminated, the
algorithm still makes unnecessary moves. This will be corrected in a future
update.

## Author
[David Jordan](https://github.com/d4n93r3ux)
