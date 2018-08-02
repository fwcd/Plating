#ifndef PLATING_HASH_FUNCTION_H
#define PLATING_HASH_FUNCTION_H

#define DECLARE_HASH_FUNCTION(T) typedef int (*HashFunction_ ## T)(T);

#endif // PLATING_HASH_FUNCTION_H
