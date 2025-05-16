# Custom Memory Allocator in C (First Fit Strategy)

This project implements a **custom dynamic memory allocator** in C using the **first-fit memory allocation** strategy. It simulates memory management using a fixed-size memory array and provides functionalities for memory allocation, deallocation, and block merging.


---

##  Features

- Fixed memory array of 12,000 bytes.
- Block-based memory allocation using a linked list.
- First-Fit memory allocation strategy.
- Block splitting to minimize internal fragmentation.
- Block merging (coalescing) of adjacent free blocks to reduce external fragmentation.
- Memory display function to visualize the state of memory blocks.

---


##  How It Works

### Memory Structure

Memory is divided into blocks. Each block contains:
- Size of the block
- Status (`free` or `allocated`)
- Pointer to the next block

### Functions

| Function         | Description                                                  |
|------------------|--------------------------------------------------------------|
| `initialize()`    | Initializes the memory pool and sets up the first free block |
| `allocate_block(size_t)` | Allocates memory using the first-fit strategy                |
| `split(block *, size_t)` | Splits a larger free block if extra space is available       |
| `free_block(void *)` | Frees a previously allocated block and triggers merging      |
| `merge()`         | Merges adjacent free blocks to reduce fragmentation          |
| `display_memory()`| Displays the state of memory (size, address, and status)     |

