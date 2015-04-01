#ifndef HASHDEF_H
#define HASHDEF_H

typedef int KeyType;
typedef int DataType;

typedef int (*HashFunction)(KeyType key);

#endif // HASHDEF_H