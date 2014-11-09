arduino-keymatrix
==================

Library for arduino that implements easy scanning of matrix keyboard.

This library does not use interrupts, you must manually call `update()` in main loop.
You should not use any long delays in your code - for the best is to use `millis()` instead.

==================

For start you need to new object using `KeyMatrix keypad = new KeyMatrix(numRows, numCols, rowsPins, colsPins, keymap)`.
Constructor is defined as follows: `KeyMatrix(int, int, int[], int[], char*)`.


Following public methods are provided:

`void setDebounce(int)` // set debounce - how much time button must be pressed to be counted as pressed (for eliminating hazard).

`void update()` // method to update keystates - must be called in main loop

`void whenPressed(keypadHandler fun, int ms)` // sets handler for when key is pressed - handler will be called periodically - second parameter will determinate min. delay between calls.

`void onRelease(keypadHandler fun)` // sets handler for when key is released

`void onPress(keypadHandler fun)` // sets handler for when key is pressed

===================
Please see example for more information.
