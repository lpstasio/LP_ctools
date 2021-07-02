#if !defined(MEMORY_H)

struct Memory
{
    u64   size;
    u64   used;
    void *base;
};

internal inline void *_push_size(Memory *memory, u64 size)
{
    // @todo: log this in release mode
    Assert((memory->used + size) <= (memory->size));
    void *new_ptr = (void*)((u8 *)memory->base + memory->used);
    memory->used += size;
    return new_ptr;
}

#define push_struct(memory, type)      (type *)(_push_size((memory), sizeof(type)))
#define push_array(memory, type, len) (type *)(_push_size((memory), sizeof(type)*(len)))

#define MEMORY_H
#endif
