// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr != MAP_FAILED) {
        mem_list_add(ptr, size);
        return ptr;
    }
    return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
    void *ptr = mmap(NULL, nmemb * size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr != MAP_FAILED) {
        mem_list_add(ptr, nmemb * size);
        memset(ptr, 0, nmemb * size);
        return ptr;
    }
    return NULL;
}

void free(void *ptr)
{
    if (ptr == NULL)
        return;
    struct mem_list *struct_block = mem_list_find(ptr);
    if (struct_block == NULL)
        return;
    munmap(struct_block->start, struct_block->len);
    mem_list_del(struct_block->start);
}

void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return NULL;
    struct mem_list *struct_block = mem_list_find(ptr);
    if (struct_block == NULL)
        return NULL;
    void *new_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == MAP_FAILED)
        return NULL;
    mem_list_del(ptr);
    mem_list_add(new_ptr, size);
    memcpy(new_ptr, ptr, struct_block->len);
    munmap(ptr, struct_block->len);
    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (ptr == NULL)
        return NULL;
    struct mem_list *struct_block = mem_list_find(ptr);
    if (struct_block == NULL)
        return NULL;
    void *new_ptr = mmap(NULL, nmemb * size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == MAP_FAILED)
        return NULL;
    mem_list_del(ptr);
    mem_list_add(new_ptr, nmemb * size);
    memcpy(new_ptr, ptr, struct_block->len);
    munmap(ptr, struct_block->len);
    return new_ptr;
}
