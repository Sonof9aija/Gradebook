# Gradebook System

## Files Overview

### `gradebook.h`
This file contains the header declarations for a gradebook system. It defines data structures and functions for managing a gradebook, including creating, adding, searching, printing, and writing to files.

### `gradebook.c`
This file implements the functions declared in `gradebook.h`. It includes functionalities like creating a new gradebook instance, adding scores, searching for student scores, printing gradebooks, and writing/reading gradebooks to/from text and binary files.

### `gradebook_main.c`
This file contains the main program that interacts with the gradebook system. It provides a command-line interface for users to create, manage, and interact with gradebooks. Users can perform operations like creating a new class, adding scores, looking up scores, writing/reading gradebooks from files, and more.

## Functionality Overview

### `gradebook.h`
- Defines data structures (`gradebook_t` and `node_t`) for representing a gradebook and its elements.
- Declares functions for creating, managing, and interacting with gradebooks, such as `create_gradebook`, `add_score`, `find_score`, `print_gradebook`, `write_gradebook_to_text`, `read_gradebook_from_text`, `write_gradebook_to_binary`, `read_gradebook_from_binary`, and `free_gradebook`.

### `gradebook.c`
- Implements the functions declared in `gradebook.h`, including hash calculations, gradebook creation, score addition/searching, printing, memory management, and file I/O operations.

### `gradebook_main.c`
- Implements a command-line interface for users to interact with the gradebook system.
- Provides commands such as creating a new class, adding scores, looking up scores, printing gradebooks, and writing/reading gradebooks from/to files.
- Handles user input, error checking, and gradebook operations based on user commands.

## How to Use

1. Include `gradebook.h` in your project to utilize the gradebook functionalities.
2. Implement the required functionalities in your main program using the functions defined in `gradebook.c`.
3. Compile and run your program to interact with the gradebook system via the command-line interface provided in `gradebook_main.c`.
4. Follow the commands and prompts to create, manage, and save/load gradebooks as needed.

## Notes
- Ensure to handle memory management appropriately, such as freeing allocated memory using `free_gradebook`.
- Use the provided command-line interface (`gradebook_main.c`) as a reference for integrating the gradebook system into your application.
- Customize the gradebook system as per your requirements, such as modifying data structures, adding new functionalities, or extending file I/O operations.
