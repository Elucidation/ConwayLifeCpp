Simple C++ implementation of [Conway's Game of Life](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

Master branch uses a dynamically allocated 2D array, every cell in array is checked.
unordered_map branch holds a hash map of all cells followed (living and neighbors thereof), and only checks those.