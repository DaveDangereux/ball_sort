# ball_sort
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/davedangereux/ball_sort/ci.yml)

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
The project builds to a console application. If run without arguments, it will
demonstrate the solution of a pre-defined puzzle.

### Multi-string arguments
You may pass a space-separated series of strings of no more than four
characters each, where each string represents a tube in the puzzle and each
unique character represents a ball colour. A puzzle must have two more tubes
than there are colours of ball, so an empty tube may be passed as an empty
quoted string.

```bash
ball_sort DFHE ABAD EIIE BHII DHCC CBGF GGAC EBFF HDAG "" ""
```

The choice of initial configuration is flexible, so this method allows the
entry of a puzzle in a half-solved state.

```bash
ball_sort DF ABAD EIIE BHII DHCC CBGF GGAC EBFF HDAG E H
```

### Single-string argument
Alternatively, you may pass a single quoted string of space-separated integers,
where each unique digit represents a ball colour. The integers will be
converted into characters (`1` = `A`) and the tubes of the puzzle will be
filled sequentially, bottom-to-top and left-to-right. Because this method is
intended to produce a puzzle in its initial state, it will automatically add
the necessary empty tubes to make the puzzle legal.

```bash
ball_sort "4 6 8 5 1 2 1 4 5 9 9 5 2 8 9 9 4 8 3 3 3 2 7 6 7 7 1 3 5 2 6 6 8 4 1 7"
```

## Building and Testing

To build both main and test executables, run the following commands:

```bash
cmake -B build
cmake --build build
```

If you prefer to use the included build scripts, note that these depend on
[sccache](https://github.com/mozilla/sccache) for Windows and
[ccache](https://ccache.dev/) for Mac / Linux respectively. Either ensure the
appropriate programs are installed and available on the system PATH, or remove
the `-DCMAKE_COMPILER_LAUNCHER=` flag from the relevant script.

## Planned Improvements

- Allow puzzle playback to be scrubbed back and forth with cursor keys
- Eliminate wasteful moves
- Support a wider range of tube sizes
- Infer tube size from supplied puzzle data
- Improve performance by optimising data structures
- Add better UI
- Draw puzzle with coloured balls and animated playback

## Known Issues
In Windows command prompt, the ANSI escape code to clear the screen seems to
require some kind of intiialisation. Puzzle playback is therefore somewhat
broken on Windows presently, but should be easy enough to fix. Although since I
only have a Macbook, this might require a creative solution using Docker
containers.

## Author
[David Jordan](https://github.com/d4n93r3ux)
