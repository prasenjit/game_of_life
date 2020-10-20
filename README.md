**Rules :**
- Any cell with more than 3 neighbours will die of overcrowding.
- Any cell with less than 2 neighbours will die of underpopulation.
- Any cell with 2 or 3 neighbours will live.
- Any dead cell with exactly 3 live neighbours will become live again.

**To compile:** 
"g++ game_of_life.cpp -o <output_file_name>"

**To run the program:**
"./output"

**To run the program taking input from a text file for the initial board:**
"./output <path_to_input_text_file>"
