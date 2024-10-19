// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "osmem.h"
#include "block_meta.h"

/* defining relevant macros */
#define MMAP_THRESHOLD (128 * 1024)
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define STRUCT_SIZE (ALIGN(sizeof(struct block_meta)))
#define PAGE_SIZE getpagesize()
#define MIN(a, b) ((a < b) ? (a) : (b))

int check_sbrk;
struct block_meta *block_start_brk;
struct block_meta *block_start_mmap;

/*
 * Pre-allocating with the maximum size of a block for malloc or calloc
 * and returning the pointer to the block
 */
struct block_meta *preallocate(int is_malloc)
{
    struct block_meta *temp_block = NULL;
    int threshold = PAGE_SIZE;
    /*
     * If we allocate with malloc we preallocate with the maximum size of a
     * block else we preallocate with the threshold
     */
    if (is_malloc)
        threshold = MMAP_THRESHOLD;

    void *brk_ptr = sbrk(MMAP_THRESHOLD);

    DIE(brk_ptr == ((void *)-1), "sbrk");
    temp_block = (struct block_meta *) brk_ptr;
    temp_block->size = threshold - STRUCT_SIZE;
    temp_block->status = STATUS_ALLOC;
    temp_block->prev = NULL;
    temp_block->next = NULL;
    return temp_block;
}

/* Coalescing the free blocks */
void coalesce(void)
{
    struct block_meta *temp_start = block_start_brk;

    while (temp_start && temp_start->next != NULL) {
        if (temp_start->status == STATUS_FREE &&
            temp_start->next->status == STATUS_FREE) {
            temp_start->size += temp_start->next->size + STRUCT_SIZE;
            if (temp_start->next->next != NULL) {
                temp_start->next->next->prev = temp_start;
                temp_start->next = temp_start->next->next;
            } else {
                temp_start->next = NULL;
            }
        } else {
            temp_start = temp_start->next;
        }
    }
}

/* Finding the best free block for the given size */
struct block_meta *find_best_block(size_t size)
{
    struct block_meta *temp_start = block_start_brk;
    struct block_meta *best_size = NULL;

    while (temp_start != NULL) {
        if (temp_start->status == STATUS_FREE && temp_start->size >= size)
            if (best_size == NULL || temp_start->size < best_size->size)
                best_size = temp_start;
        temp_start = temp_start->next;
    }
    return best_size;
}

/*
 * Splitting the block into two blocks, one for the allocation
 * and one for the rest
 */
void split_block(struct block_meta *use_block, size_t size_check)
{
    struct block_meta *rest_block = (struct block_meta *)(((char *)use_block)
                                                          + size_check);
    rest_block->status = STATUS_FREE;
    rest_block->size = use_block->size - size_check;
    rest_block->prev = use_block;
    rest_block->next = use_block->next;
    use_block->next = rest_block;
    if (rest_block->next)
        rest_block->next->prev = rest_block;
    use_block->size = size_check - STRUCT_SIZE;
    use_block->status = STATUS_ALLOC;
}

/* Expanding the heap with the given size in order to add the memory block*/
struct block_meta *expand(size_t size)
{
    struct block_meta *temp_start = block_start_brk;

    while (temp_start->next != NULL)
        temp_start = temp_start->next;

    if (temp_start->status == STATUS_FREE) {
        void *sbrk_ptr = (void *)sbrk(size - temp_start->size);

        DIE(sbrk_ptr == (void *)-1, "sbrk");
        temp_start->status = STATUS_ALLOC;
        temp_start->size = size;
        return temp_start;
    }
    struct block_meta *temp_block = NULL;
    void *sbrk_ptr = (void *)sbrk(size + STRUCT_SIZE);

    DIE(sbrk_ptr == (void *)-1, "sbrk");
    temp_block = (struct block_meta *) sbrk_ptr;
    temp_block->size = size;
    temp_block->status = STATUS_ALLOC;
    temp_block->next = NULL;
    temp_block->prev = temp_start;
    temp_start->next = temp_block;
    return temp_block;
}

/* Allocating memory with mmap */
struct block_meta *mmap_allocate(size_t size)
{
    struct block_meta *temp_block = NULL;
    void *mmap_ptr = mmap(NULL, size + STRUCT_SIZE, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    DIE(mmap_ptr == ((void *)-1), "mmap");
    temp_block = (struct block_meta *)mmap_ptr;
    temp_block->status = STATUS_MAPPED;
    temp_block->size = size;
    temp_block->prev = NULL;
    temp_block->next = NULL;
    return temp_block;
}

void *os_malloc(size_t size)
{
    int is_malloc = 1;
    struct block_meta *use_block = NULL;

    if (size == 0)
        return NULL;

    /* If the size is bigger than the threshold we allocate with mmap */
    if (ALIGN(size) + STRUCT_SIZE >= MMAP_THRESHOLD) {
        use_block = mmap_allocate(ALIGN(size));
        if (block_start_mmap == NULL) {
            block_start_mmap = use_block;
        } else {
            struct block_meta *temp_start = block_start_mmap;

            while (temp_start->next != NULL)
                temp_start = temp_start->next;
            use_block->prev = temp_start;
            temp_start->next = use_block;
        }
        return (void *)(use_block + 1);
    }

    /*
     * If the size is smaller than the threshold we allocate with brk
     * also we check if we preallocate or not
     */
    if (check_sbrk == 0 && (ALIGN(size) + STRUCT_SIZE) < MMAP_THRESHOLD) {
        /* First call, preallocate a chunk of memory */
        check_sbrk = 1;
        use_block = preallocate(is_malloc);
        block_start_brk = use_block;
        return (void *)(use_block + 1);
    }

    /*
     * If the size is smaller than the threshold we allocate with brk
     * without pre-allocation
     */
    if (check_sbrk == 1 && (ALIGN(size)) + STRUCT_SIZE < MMAP_THRESHOLD) {
        coalesce();
        use_block = find_best_block(ALIGN(size));
        if (use_block != NULL) {
            size_t size_check = ALIGN(size) + STRUCT_SIZE;

            if (use_block->size >= (size_check + ALIGN(1)))
                split_block(use_block, size_check);
            use_block->status = STATUS_ALLOC;
            return (void *)(use_block + 1);
        }
        use_block = expand(ALIGN(size));
        return (void *)(use_block + 1);
    }
    return (void *)(use_block + 1);
}

void os_free(void *ptr)
{
    if (ptr == NULL)
        return;
    struct block_meta *temp_block = (struct block_meta *) (((char *) ptr)
                                                           - STRUCT_SIZE);

    if (temp_block->status == STATUS_ALLOC) {
        /* If the block is allocated with brk we mark it as free */
        temp_block->status = STATUS_FREE;
    } else {
        if (temp_block->status == STATUS_MAPPED) {
            /* If the block is allocated with mmap we free it */
            if (temp_block == block_start_mmap) {
                if (temp_block->next)
                    temp_block->next->prev = NULL;
                block_start_mmap = temp_block->next;
            } else {
                temp_block->prev->next = temp_block->next;
                if (temp_block->next)
                    temp_block->next->prev = temp_block->prev;
            }
            int munmap_ret = munmap(temp_block, temp_block->size + STRUCT_SIZE);

            DIE(munmap_ret == -1, "munmap");
        }
    }
}

void *os_calloc(size_t nmemb, size_t size)
{
    int is_malloc = 0;
    struct block_meta *use_block = NULL;

    if (nmemb <= 0 || size <= 0)
        return NULL;

    /* If the size is bigger than the threshold we allocate with mmap */
    if (ALIGN(size * nmemb) + STRUCT_SIZE >= (size_t) PAGE_SIZE) {
        use_block = mmap_allocate(ALIGN(size * nmemb));
        if (block_start_mmap == NULL) {
            block_start_mmap = use_block;
        } else {
            struct block_meta *temp_start = block_start_mmap;

            while (temp_start->next != NULL)
                temp_start = temp_start->next;
            use_block->prev = temp_start;
            temp_start->next = use_block;
        }
        memset((void *) (use_block + 1), 0, size * nmemb);
        return (void *)(use_block + 1);
    }

    /*
     * If the size is smaller than the threshold we allocate with brk
     * also we check if we preallocate or not
     */
    if (check_sbrk == 0 && (ALIGN(size * nmemb) + STRUCT_SIZE)
                           < (size_t) PAGE_SIZE) {
        /* First call, preallocate a chunk of memory */
        check_sbrk = 1;
        use_block = preallocate(is_malloc);
        block_start_brk = use_block;
        memset((void *) (use_block + 1), 0, size * nmemb);
        return (void *)(use_block + 1);
    }

    /* If the size is smaller than the threshold we allocate with brk */
    /* without pre-allocation */
    if (check_sbrk == 1 && (ALIGN(size * nmemb)) + STRUCT_SIZE
                           < (size_t) PAGE_SIZE) {
        coalesce();
        use_block = find_best_block(ALIGN(size * nmemb));
        if (use_block != NULL) {
            size_t size_check = ALIGN(size * nmemb) + STRUCT_SIZE;

            if (use_block->size >= (size_check + ALIGN(1)))
                split_block(use_block, size_check);
            use_block->status = STATUS_ALLOC;
            memset((void *) (use_block + 1), 0, size * nmemb);
            return (void *)(use_block + 1);
        }
        use_block = expand(ALIGN(size * nmemb));
        memset((void *) (use_block + 1), 0, size * nmemb);
        return (void *)(use_block + 1);
    }
    memset((void *) (use_block + 1), 0, size * nmemb);
    return (void *)(use_block + 1);
}

void *os_realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return os_malloc(size);

    if (size == 0) {
        os_free(ptr);
        return NULL;
    }
    struct block_meta *use_block = (struct block_meta *) (((char *) ptr)
                                                          - STRUCT_SIZE);

    if (use_block->status == STATUS_FREE)
        return NULL;
    if (use_block->size == ALIGN(size))
        return ptr;

    /*
     * Memory allocated with mmap cannot be reused so a new block is needed
     * then copying data and freeing the old one
     */
    if (ALIGN(size) + STRUCT_SIZE >= MMAP_THRESHOLD ||
        use_block->status == STATUS_MAPPED) {
        void *new_block = os_malloc(size);

        memcpy(new_block, ptr, MIN(use_block->size, ALIGN(size)));
        os_free(ptr);
        return new_block;
    }

    /*
     * Memory allocated with sbrk can be reused but memory might need
     * to be expanded. if not, coalesce the blocks and create
     * new blocks to fit the memory
     */
    if (ALIGN(size) + STRUCT_SIZE < MMAP_THRESHOLD) {
        if (ALIGN(size) > use_block->size) {
            struct block_meta *temp_start = block_start_brk;

            while (temp_start->next != NULL)
                temp_start = temp_start->next;
            if (use_block->next == NULL) {
                void *brk_ptr = (void *) sbrk(ALIGN(size) - temp_start->size);

                DIE(brk_ptr == (void *)-1, "sbrk");
                temp_start->status = STATUS_ALLOC;
                temp_start->size = ALIGN(size);
            }
            while (ALIGN(size) > use_block->size &&
                   use_block->next && use_block->next->status == STATUS_FREE) {
                use_block->size += use_block->next->size + STRUCT_SIZE;
                if (use_block->next->next) {
                    use_block->next->next->prev = use_block;
                    use_block->next = use_block->next->next;
                } else {
                    use_block->next = NULL;
                }
            }
            if (ALIGN(size) > use_block->size) {
                void *new_block = os_malloc(size);

                memcpy(new_block, ptr, MIN(use_block->size, ALIGN(size)));
                os_free(ptr);
                return new_block;
            }
        }

        if (ALIGN(size) + STRUCT_SIZE + ALIGN(1) <= use_block->size)
            split_block(use_block, ALIGN(size) + STRUCT_SIZE);
    }
    return (void *) (use_block + 1);
}
