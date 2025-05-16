#include <stdio.h>
#include <stddef.h>
#define SIZE 12000

char memory[SIZE];

// The structure definition to contain metadata of each block allocated or deallocated
typedef struct block_tag
{
    size_t size;
    int free;
    struct block_tag *next;
} block;

block *freeList = (void *)memory;

void initialize();
void split(block *fitting_block, size_t size);
void *allocate_block(size_t noOfBytes);
void merge();
void free_block(void *ptr);

void initialize()
{
    freeList->size = 20000 - sizeof(block);
    freeList->free = 1;
    freeList->next = NULL;
}

// Assume first fit algorithm
void split(block *fitting_block, size_t size)
{
    block *new = (void *)(((void *)fitting_block) + size + sizeof(block));
    new->size = (fitting_block->size) - size - sizeof(block);
    new->free = 1;
    new->next = fitting_block->next;
    fitting_block->size = size;
    fitting_block->free = 0;
    fitting_block->next = new;
}

void *allocate_block(size_t noOfBytes)
{
    block *curr, *prev;
    void *result;
    if (!(freeList->size))
    {
        initialize();
    }
    curr = freeList;
    while (((curr->size < noOfBytes) || (curr->free == 0)) && (curr->next != NULL))
    {
        prev = curr;
        curr = curr->next;
    }
    if ((curr->size) == noOfBytes)
    {
        curr->free = 0;
        result = (void *)(++curr);
        printf("Exact fitting block allocated\n");
        return result;
    }
    else if (curr->size > (noOfBytes + sizeof(block)))
    {
        split(curr, noOfBytes);
        result = (void *)(++curr);
        printf("Fitting block allocated with a split\n");
        return result;
    }
    else
    {
        result = NULL;
        printf("Sorry! No sufficient memory to allocate\n");
        return result;
    }
}

void merge()
{
    block *curr, *prev;
    curr = freeList;
    while ((curr->next) != NULL)
    {
        if ((curr->free) && (curr->next->free))
        {
            curr->size += (curr->next->size) + sizeof(block);
            curr->next = curr->next->next;
        }
        prev = curr;
        curr = curr->next;
    }
}

void free_block(void *ptr)
{
    if (((void *)memory <= ptr) && (ptr <= (void *)(memory + SIZE)))
    {
        block *curr = ptr;
        --curr;
        curr->free = 1;
        merge();
    }
    else
        printf("Provide a valid pointer for deallocation.\n");
}

void display_memory()
{
    block *curr = freeList;
    int block_num = 0;
    printf("\nMemory Blocks:\n");
    printf("--------------------------------------------------------\n");
    printf("| Block | Address     | Size (bytes) | Status          |\n");
    printf("--------------------------------------------------------\n");
    while (curr != NULL)
    {
        printf("| %5d | %p | %12zu | %s |\n",
               block_num,
               (void *)curr,
               curr->size,
               (curr->free ? "Free" : "Allocated"));
        curr = curr->next;
        block_num++;
    }
    printf("--------------------------------------------------------\n\n");
}

int main()
{

    int *ptr1 = (int *)allocate_block(200 * sizeof(int));
    display_memory();
    char *ptr2 = (char *)allocate_block(150 * sizeof(char));
    display_memory();
    int *ptr3 = (int *)allocate_block(1200 * sizeof(int));
    display_memory();
    free_block(ptr1);
    display_memory();
    char *ptr4 = (char *)allocate_block(750);
    display_memory();
    free_block(ptr3);
    display_memory();
    int *ptr5 = (int *)allocate_block(650 * sizeof(int));
    display_memory();
    printf("Allocation and deallocation is done successfully!");
}