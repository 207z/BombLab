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
    uint32_t p1_step2_result = (challenge ^ 0x7d05) + (challenge >> 32) * 8;
    uint32_t p1_step0_result = 0x333b ^ ((challenge >> 16) * 2 + challenge);
    uint32_t p1_step1_result = 0x9392 ^ (p1_step0_result * 3 + p1_step2_result);
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

uint32_t ecx_4;
uint32_t eax_4;
uint32_t edi_4;
uint32_t esi_4;
uint32_t edx_4;
void work_4(){
    eax_4 = edi_4;
    edi_4 = edx_4;
    edi_4 -= esi_4;
    edi_4 >>= 1;
    edi_4 += esi_4;
    if(eax_4 != edi_4){
        uint32_t ebx_4 = ecx_4 + edi_4;
        if(edi_4 <= eax_4){
            esi_4 = edi_4 + 1;
            edi_4 = eax_4;
            work_4();
            eax_4 = (5 * eax_4) ^ ebx_4 ^ 0x1f;
        }
        else{
            edx_4 = edi_4 - 1;
            edi_4 = eax_4;
            work_4();
            eax_4 = (5 * eax_4) ^ ebx_4 ^ 0x14;
        }
        return ;
    }
    eax_4 = edi_4 + 0xfc;
    eax_4 ^= ecx_4;
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    ecx_4 = (challenge >> 7) ^ (challenge >> 32);
    eax_4 = challenge >> 32;
    edi_4 = challenge & 0x7f;
    edx_4 = 0x7f;
    esi_4 = 0;
    work_4();
    values[0] = eax_4;
    count = 1;
    return write_answer(out, cap, values, count);
}

struct p5_nodes{
    uint32_t value1;
    uint32_t value2;
}p5_heads[12];

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    p5_heads[0].value1 = 2608;
    p5_heads[0].value2 = 6738;
    p5_heads[1].value1 = 1357;
    p5_heads[1].value2 = 41841;
    p5_heads[2].value1 = 2148;
    p5_heads[2].value2 = 45786;
    p5_heads[3].value1 = 1121;
    p5_heads[3].value2 = 25315;
    p5_heads[4].value1 = 1860;
    p5_heads[4].value2 = 19446;
    p5_heads[5].value1 = 2844;
    p5_heads[5].value2 = 1221;
    p5_heads[6].value1 = 2322;
    p5_heads[6].value2 = 1124;
    p5_heads[7].value1 = 1666;
    p5_heads[7].value2 = 53720;
    p5_heads[8].value1 = 554;
    p5_heads[8].value2 = 51799;
    p5_heads[9].value1 = 59;
    p5_heads[9].value2 = 9401;
    p5_heads[10].value1 = 369;
    p5_heads[10].value2 = 58527;
    int j = challenge & 0x7;
    values[1] = p5_heads[j].value1;
    values[0] = ((challenge >> 32) ^ (challenge >> 6) ^ p5_heads[j].value2 ^ 0xef5e) + values[1];
    int top = (challenge >> 3) & 3;
    for(int i = 1 ; i <= top ; i++){
        j++;
        values[1] = p5_heads[j].value1;
        values[0] = (values[0] ^ p5_heads[j].value2) + values[1];
    }
    count = 2;
    return write_answer(out, cap, values, count);
}

void p6_op_3(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = ((*tmp2) >> 3) + ((*tmp2) << 29);
}

void p6_op_5(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = (*tmp2) + 0xabbd;
    *tmp2 >>= 0x5;
    *tmp1 ^= (*tmp2);
}

void p6_op_4(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = (*tmp2) ^ 0xab81;
    *tmp1 = (*tmp1) + 2 * (*tmp2);
}

void p6_op_1(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = ((*tmp2) * 2 + 0xaaf5) ^ (7 * (*tmp2));
}

void p6_op_0(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = (((*tmp2) >> 3) ^ (*tmp2)) + 0x271c;
}

void p6_op_2(uint32_t *tmp1,uint32_t *tmp2){
    *tmp1 = (((*tmp2) << 7) + ((*tmp2) >> 25)) ^ 0x2e4d;
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    uint32_t tmp2 = (challenge >> 32) ^ (challenge >> 6);
    uint32_t tmp1 = challenge & 0x7;
    switch(challenge & 0x7){
        case 0:
            p6_op_3(&tmp1, &tmp2);
            break;
        case 1:
            p6_op_5(&tmp1, &tmp2);
            break;
        case 2:
            p6_op_4(&tmp1, &tmp2);
            break;
        case 3:
            p6_op_5(&tmp1, &tmp2);
            break;
        case 4:
            p6_op_1(&tmp1, &tmp2);
            break;
        case 5:
            p6_op_0(&tmp1, &tmp2);
            break;
        case 6:
            p6_op_4(&tmp1, &tmp2);
            break;
        case 7:
            p6_op_2(&tmp1, &tmp2);
            break;
    }
    tmp1 = tmp1 ^ 0x91bb;
    tmp2 = tmp1;
    switch((challenge >> 3) & 0x7){
        case 0:
            p6_op_3(&tmp1, &tmp2);
            break;
        case 1:
            p6_op_5(&tmp1, &tmp2);
            break;
        case 2:
            p6_op_4(&tmp1, &tmp2);
            break;
        case 3:
            p6_op_5(&tmp1, &tmp2);
            break;
        case 4:
            p6_op_1(&tmp1, &tmp2);
            break;
        case 5:
            p6_op_0(&tmp1, &tmp2);
            break;
        case 6:
            p6_op_4(&tmp1, &tmp2);
            break;
        case 7:
            p6_op_2(&tmp1, &tmp2);
            break;
    }
    values[0] = tmp1 + 0x676b;
    count = 1;
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    uint32_t first_number = context & 0x3;
    uint32_t tmp = ((challenge >> 32) ^ challenge) ^ ((context >> 32) ^ context);
    tmp = (tmp ^ 0x28c4) + ((tmp >> 3) ^ 0x93db);
    uint32_t second_number = tmp ^ ((first_number * 0x28c4) ^ (context >> 16));
    uint32_t third_number = ((uint32_t)((challenge >> 32) ^ challenge) >> 3) + ((context >> 32) ^ context) + 0x93db + first_number;
    third_number = third_number ^ second_number;

    for(int i = 0 ; i < 163 ; i++){
        out[i]=' ';
    }
    out[163] = '\0';
    out[32] = 'O';
    out[33] = 'P';
    out[34] = 'E';
    out[35] = 'N';
    snprintf(out + 36, 163 - 36 + 1, "%u %u %u", first_number, second_number, third_number);
    return 0;
}
