#include <stdio.h>
#include <stdlib.h>

// Variadric macro
// #define my_printf(...) printf(__VA_ARGS__)

#define debug(M, ...) fprintf(stderr, "[+][DEBUG][%s]:%d:  " M "\n", __func__, __LINE__, ##__VA_ARGS__);


