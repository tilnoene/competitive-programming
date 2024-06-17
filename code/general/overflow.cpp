// Signatures of some built-in functions to perform arithmetic operations with overflow check
// Source: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
// 
// you can also check overflow by performing the operation with double
// and checking if the result it's greater than the maximum value supported by the variable

bool __builtin_add_overflow (type1 a, type2 b, type3 *res)
bool __builtin_sadd_overflow (int a, int b, int *res)
bool __builtin_saddl_overflow (long int a, long int b, long int *res)
bool __builtin_saddll_overflow (long long int a, long long int b, long long int *res)
bool __builtin_uadd_overflow (unsigned int a, unsigned int b, unsigned int *res)
bool __builtin_uaddl_overflow (unsigned long int a, unsigned long int b, unsigned long int *res)
bool __builtin_uaddll_overflow (unsigned long long int a, unsigned long long int b, unsigned long long int *res)

bool __builtin_sub_overflow (type1 a, type2 b, type3 *res)
bool __builtin_ssub_overflow (int a, int b, int *res)
bool __builtin_ssubl_overflow (long int a, long int b, long int *res)
bool __builtin_ssubll_overflow (long long int a, long long int b, long long int *res)
bool __builtin_usub_overflow (unsigned int a, unsigned int b, unsigned int *res)
bool __builtin_usubl_overflow (unsigned long int a, unsigned long int b, unsigned long int *res)
bool __builtin_usubll_overflow (unsigned long long int a, unsigned long long int b, unsigned long long int *res)

bool __builtin_mul_overflow (type1 a, type2 b, type3 *res)
bool __builtin_smul_overflow (int a, int b, int *res)
bool __builtin_smull_overflow (long int a, long int b, long int *res)
bool __builtin_smulll_overflow (long long int a, long long int b, long long int *res)
bool __builtin_umul_overflow (unsigned int a, unsigned int b, unsigned int *res)
bool __builtin_umull_overflow (unsigned long int a, unsigned long int b, unsigned long int *res)
bool __builtin_umulll_overflow (unsigned long long int a, unsigned long long int b, unsigned long long int *res)

bool __builtin_add_overflow_p (type1 a, type2 b, type3 c)
bool __builtin_sub_overflow_p (type1 a, type2 b, type3 c)
bool __builtin_mul_overflow_p (type1 a, type2 b, type3 c)