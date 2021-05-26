#ifndef SALSA20_H
#define SALSA20_H

void salsa20_hash(uint3_t seq[64]);
//typedef (void *salsa20_expansion)(uint3_t seq[64]);
void salsa20_encrypt();

#endif
