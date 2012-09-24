Simple C++ implementation of [Conway's Game of Life](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

![Visualization of Life board](http://i.imgur.com/MYzeM.png)

Basic Usage
---
Run `life.exe`
Defaults to 32x32 boards for 100 turns with visuals on.

For more control pass arguments via `life.exe SIZE TURNS VISUAL?`
* 2D board size is NxN where N = SIZE
* TURNS is the number of turns to step through
* VISUAL? is whether to show visuals or not, can be 'v' for yes or anything else for no


Branches
---
Master branch uses a dynamically allocated 2D array, every cell in array is checked.
unordered_map branch holds a hash map of all cells followed (living and neighbors thereof), and only checks those.