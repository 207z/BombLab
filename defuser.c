#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    size_t p1_step2_result = (challenge ^ 0x7d05) + (challenge >> 32) * 8;
    size_t p1_step0_result = 0x333b ^ ((challenge >> 16) * 2 + challenge);
    size_t p1_step1_result = 0x9392 ^ (p1_step0_result * 3 + p1_step2_result);
    values[0] = p1_step1_result;
    count = 1;
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    values[0] = (((challenge >> 41) * 2) & 0x1e) + 0x3;
    for(int i=1,j=19;i<6;i++,j+=3){
        values[i] = (((challenge >> j) & 0xf) + i) ^ (3 * values[i-1]);
    }
    count = 6;
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    values[0] = challenge & 0x7;
    uint32_t tmp = (challenge >> 32) ^ (challenge >> 3);
    switch(values[0]){
        case 6:
            values[1] = (tmp * 2) ^ 0xe546;
            break;
        case 7:
            values[1] = (tmp ^ 0x693b) + (tmp >> 2);
            break;
        case 0:
            values[1] = (tmp ^ 0xbab1) + (tmp >> 2);
            break;
        case 1:
            values[1] = tmp * 3 + 0x5bae;
            break;
        case 2:
            values[1] = tmp * 5 + 0x40ddf;
            break;
        case 3:
            values[1] = tmp * 5 + 0x488c;
            break;
        case 4:
            values[1] = (tmp * 4) ^ 0x18fd;
            break;
        case 5:
            values[1] = tmp * 5 + 0x1d687;
            break;
        default:
            values[1] = 0;
    }
    count = 2;
    return write_answer(out, cap, values, count);
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
