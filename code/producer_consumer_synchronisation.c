#define BUFFER_SIZE 4

// Shared memory
int buffer[BUFFER_SIZE];

// Shared variable
int count = 0; // Items to be consumed

int in = 0;  // Index for producer
int out = 0; // Index for consumer

void produce(int *produced)
{
    while (1)
    {
        // Wait until consumer has consumed next index
        while (count == BUFFER_SIZE)
            ; // Buffer is full, do nothing

        // Buffer has space, produce item
        buffer[in] = *produced;

        // Update index
        in = (in + 1) % BUFFER_SIZE;
        count++;
    }
}

void consume(int *consumed)
{
    while (1)
    {
        // Wait until producer has produced next index
        while (count == 0)
            ; // Buffer is empty, do nothing

        // Buffer has item, consume it
        *consumed = buffer[in];

        // Update index
        out = (out + 1) % BUFFER_SIZE;
        count--;
    }
}
