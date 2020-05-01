#ifndef FASTER_STR
#define FASTER_STR
inline int fast_len(char* str)
{
    unsigned long long* chunk = reinterpret_cast<unsigned long long*>(str);
    int res = 0;

    asm("mov    rcx, 0\n\t"
        "mov    rdi, %1\n\t"
        "mov    rbx, 0\n\t"
        "not    rbx\n\t"
        "fast_len_loop:\n\t"
        "cmp    rcx, 6\n\t"
        "je     fast_len_loop_end\n\t"
        "mov    rax, [rdi]\n\t"
        "xor    rax, rbx\n\t"
        "inc    rcx\n\t"
        "cmp    rax, rbx\n\t"
        "jne    fast_len_loop\n\t"
        "fast_len_loop_end:\n\t"
        "shl    rcx, 3\n\t"
        "mov    %0, ecx\n\t"
        :"=r"(res)
        :"r"(chunk)
        :"rax", "rcx", "rdi", "rbx");
    return res;
}

inline bool fastcmpeq(char* str1, char* str2)
{
    unsigned long long* chunk_arr1 = reinterpret_cast<unsigned long long*>(str1);
    unsigned long long* chunk_arr2 = reinterpret_cast<unsigned long long*>(str2);
    unsigned long long int result = 0;
        asm("mov    rdi, %1\n\t"       
            "mov    rsi, %2\n\t"
            "mov    ecx, 6\n\t"
            "cmp_loop:\n\t"
            "cmp    ecx, 0\n\t"
            "je     cmp_loop_end\n\t"
            "dec    ecx\n\t"
            "mov    rax, [rdi]\n\t"
            "mov    rbx, [rsi]\n\t"
            "xor    rax, rbx\n\t"
            "cmp    rax, 0\n\t"
            "add    rsi, 8\n\t"
            "add    rdi, 8\n\t"
            "je     cmp_loop\n\t"
            "cmp_loop_end:\n\t"
            "mov    %0, rax\n\t"
            :"=r"(result)             
            :"r"(chunk_arr1), "r"(chunk_arr2)    
            : "rax", "rbx", "rcx", "rdi", "rsi"        
            );

    return !result;
}


#endif
