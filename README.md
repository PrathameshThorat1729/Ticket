# Ticket
Ticket : A Collection of interactive, puzzled, joyful game at your terminal.

# Installation and Building

## Cloaning
```bash
$ git clone https://github.com/PrathameshThorat1729/Ticket
```

## Building
```bash
$ make build
```
use
```bash
$ make run
```
for instant running ir run '*bin/buildticket*'

objects are stored in '*bin/obj/*'

## Cleaning Workspace
```bash
$ make clean
```

# Contributing

## Adding new Game
- Add game.c in src/ and game.h in include
- copy templates from template folder
- replace *game* with your game name ( Case Sensitive )
- add your GAME_PAGE in Ticket.h -> enum Pages { ... }
- add game function in Ticket.c -> function pointer array
- add game option in home.c
- code your game 

## Anything else
use your brain and fix any issue or update code to be more useful