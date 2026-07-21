# Mini Game Project – Tic Tac Toe (C++)

A console-based Tic Tac Toe game built in C++ for the Thiranex internship task. It demonstrates core programming concepts — loops, arrays, and conditional logic — through a simple, playable game.

## What it does

- **Two Player mode** – play against a friend on the same console.
- **Player vs Computer mode** – play against a computer opponent with basic strategy.
- Redraws the board after every move.
- Detects wins, blocks (in computer mode), and draws.
- Lets you replay without restarting the program.
- Validates input so you can't pick an already-taken cell or an out-of-range number.

## How the computer opponent thinks

The computer isn't just picking random cells. Before every move it checks, in order:

1. Can I win right now? If yes, take that move.
2. Can the opponent win on their next move? If yes, block it.
3. Is the center free? Take it (statistically the strongest opening/mid-game cell).
4. Is a corner free? Take one (corners are stronger than edges).
5. Otherwise, take whatever's left.

It's not unbeatable (it's not a full minimax), but it plays a solid, sensible game and will punish careless mistakes.

## Board layout

Cells are numbered 1–9 like a numeric keypad:

```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

Just enter the number of the cell you want to place your mark in.

## Files

```
04-mini-game-tic-tac-toe/
├── main.cpp
├── Makefile
└── README.md
```

## How to run

```bash
g++ -std=c++17 -Wall -o ttt main.cpp
./ttt
```

or:

```bash
make run
```

## Possible improvements

- Full minimax so the computer never loses
- Score tracking across multiple rounds
- A larger board (e.g. 4x4, connect-4 style win condition)
