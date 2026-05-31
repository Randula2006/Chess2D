# Chess2D

> A handcrafted 2D chess experience built in C with SDL2.

[![Language: C99](https://img.shields.io/badge/Language-C99-00599C?style=for-the-badge)](https://en.cppreference.com/w/c/language)
[![Renderer: SDL2](https://img.shields.io/badge/Renderer-SDL2-2B2E3A?style=for-the-badge)](https://www.libsdl.org/)
[![Status: Playable Prototype](https://img.shields.io/badge/Status-Playable%20Prototype-2F7D32?style=for-the-badge)](#project-status)
[![Platform: WSL/Linux](https://img.shields.io/badge/Platform-WSL%20%2F%20Linux-4EAA25?style=for-the-badge)](#quick-start-wsllinux)

---

## Overview

Chess2D is a learning-driven and performance-conscious chess project focused on:

- clean C architecture (separate board/input/render/moves modules)
- deterministic game logic (move generation + legal move filtering)
- minimal SDL2 rendering (board + pieces + highlights)
- an approachable path from prototype to full rules-complete chess

The current build is already playable for local two-player chess: click a piece to see legal moves, then click a highlighted square to move. The game detects check, checkmate, and stalemate.

---

## Project Status

### Implemented

- 800×800 fixed-size SDL window + renderer (VSync)
- board representation + standard starting position
- board rendering + PNG piece textures (one file per piece)
- left-click selection + legal move highlighting
- move generation for all piece types
- legal move filtering (prevents moving into check)
- check detection + in-check king highlight
- checkmate + stalemate detection + game-over overlay

### In Progress (Next Milestones)

- special rules: castling, en passant, promotion
- richer UI: move history, captured pieces, reset/new game
- stricter rules/edge cases and correctness testing

### Controls

- Left click a piece (of the side to move) to select it
- Legal destination squares highlight in yellow
- Left click a highlighted square to move
- Left click another own piece to change selection

There are no keyboard controls yet.

### Known Limitations

- No castling, en passant, or promotion yet
- No draw rules beyond stalemate (e.g., repetition, 50-move rule)
- The window is forced back to 800×800 if you try to resize it

---

## Quick Start (WSL/Linux)

### 1. Install dependencies

```bash
sudo apt update
sudo apt install -y build-essential pkg-config libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

### 2. Build

```bash
make
```

### 3. Run

```bash
make run
```

Important: run from the repo root so asset paths like `assets/pawn-w.png` resolve correctly.

### 4. Clean build artifacts

```bash
make clean
```

---

## Build Notes

- The Makefile currently targets WSL/Linux using `pkg-config`.
- SDL linker/compiler flags are resolved automatically through:
	- `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
	- `pkg-config --libs sdl2 SDL2_image SDL2_ttf`
- Source entry point: `src/main.c`

---

## Project Layout

```text
Chess2D/
├── assets/                 # Piece PNGs + font
├── include/                # Project headers
├── libs/                   # Vendored SDL-related headers/libs (not used by default Makefile)
├── src/                    # Game code
├── makefile                # Build script for WSL/Linux
├── testPhases.txt          # Planning notes
└── README.md               # Project documentation
```

### Planned Internal Modules

Current and planned modules:

- `board` for board state and initialization
- `piece` for piece types/colors
- `moves` for move generation + legality filtering + check detection
- `render` for board/piece/highlight drawing
- `input` for mouse interactions and turn actions

---


## Development Roadmap

### Phase 1: Window and Loop

- SDL init, window, renderer, event loop
- done

### Phase 2: Board Representation

- define `Piece`, `Color`, `PieceType`, and `Board`
- initialize standard chess starting position
- status: done

### Phase 3: Rendering

- draw checkered board
- load and render piece sprites
- status: done

### Phase 4: Input and Selection

- map mouse coordinates to board squares
- selectable piece + highlighted destinations
- status: done

### Phase 5: Move Generation

- generate piece moves by type
- add bounds checks, collisions, captures
- status: in progress (special rules remain)

### Phase 6: Rule Validation

- check detection
- legal move filtering (prevent self-check)
- status: done (baseline)

### Phase 7: Full Match Flow

- turn switching
- checkmate/stalemate detection
- status: done (promotion not yet)

### Phase 8: Polish

- move history, timers, audio, optional AI

---

## Documentation Design System

To keep documentation and UI direction visually consistent, use this lightweight style language:

| Element | Style Direction |
|---|---|
| Tone | Technical, concise, practical |
| Color idea | Forest (`#1B5E20`), Ivory (`#F6F1E9`), Slate (`#2F3A45`), Gold accent (`#D4A017`) |
| Typography | Monospace for code and engine data, serif or geometric sans for headings |
| Visual motif | Chessboard contrast, clear spacing, minimal ornament |

This gives the project docs an intentional identity instead of generic boilerplate.

---

## Troubleshooting

### `pkg-config` cannot find SDL packages

Install missing dev packages:

```bash
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev pkg-config
```

### Build fails with missing compiler tools

Install toolchain:

```bash
sudo apt install -y build-essential
```

### Window does not open in WSL

- ensure you are using WSLg (Windows 11) or an X server setup
- confirm graphical apps work by testing another simple SDL app

### Pieces/fonts don’t load

- make sure you run the executable from the repo root (`make run` does this)
- verify the `assets/` files exist and are readable

---

## Current Goal

Immediate target: fill in the missing chess rules (castling, en passant, promotion) and tighten correctness around check detection and edge cases.

When this is complete, Chess2D transitions from “playable prototype” to “rules-complete game”.