/***********************************************************************************************************************
* Copyright Leadcore Technology Co.,Ltd.
* All rights reserved by Leadcore Technology Co.,Ltd.
* No. 1258 Mingyue Road, Pudong new district, Shanghai, China
* This file and all its contents included remain the proprietary
* material of Leadcore Technology Co.,Ltd
* and are protected by the Chinese and international copyright laws.
* Any reproduction,transmission,disclosure or use of this file or the whole
* or part of its contents,in whatever form and by whatever means,is not permitted
* without prior express written authorization from Leadcore Technology.Offenders will be
* liable for any and all damages caused by their offence hereof and will be subject
* to all remedies that Leadcore Technology is entitled to seek under applicable laws.
* All intellectual property rights contained or involved herein,expressly or
* impliedly,including without limitation the generality of the foregoing,
* trademark rights,rights created by patent grant or registration of utility
* model or design and rights to apply or help apply for such grant or registration
* based on any technical elements extracted herein,are reserved.Technical
* modifications are only permitted when agreed in written contract.
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @file    osa_pub.c
 * @brief   This is a brief description.
 * @details This is the detail description.
//{0}
 * @par HISTORY:
 * DATE         AUTHOR          CRID                    DESC\n
 * 2019-11-06   GuXiaofeng    HawkBug10000054          [Hawk]modify case "3001" reply
***********************************************************************************************************************/
#undef THIS_FILE_NAME_ID
#define THIS_FILE_NAME_ID DEMO_TEST_ALGO_SELF_TEST_XC4210

/***********************************************************************************************************************
*  INCLUDE FILES
**********************************************************************************************************************/
#include "osa.h"
#include "dd_api.h"
#include "demo_common.h"
#include "demo_xc4210_comm.h"
/* FIX HawkReq10000029   BEGIN   2019-06-10 : xuyuan */
//#include "hwa_common.h"
/* FIX HawkReq10000029   END   2019-06-10 : xuyuan */
/* FIX HawkBug10000155   BEGIN   2021-07-02 : xuyuan */
#include "xc4210_mem_cfg.h"
/* FIX HawkBug10000155   END   2021-07-02 : xuyuan */
#include <vec-c.h> // ָ���

#include <vec-mem-modes.h>
#include "demo_hwa_qbman.h"
//{1}
#include "demo_hwa_qbman_config.h"

#define VECTOR_U32_LEN (16)
#define VECTOR_LEN (VECTOR_U32_LEN)
#define VECTOR_U16_LEN (32)


#define TURBO_3G_OUTPUT_WORD 0x8
#define TURBO_3G_OUTPUT_BYTE (TURBO_3G_OUTPUT_WORD << 2)
#define TURBO_W_3G_INPUT_WORD 0xE0
#define TURBO_LTE_INPUT_WORD 0x1100
#define TURBO_DTCM_INPUT_BUFF_BYTE 0x4000

/* FIX HawkEnh10000026   BEGIN   2020-09-07 : xuyuan */
#define ALGO_HWA_TYPE_TURBO_3G     (0)
#define ALGO_HWA_TYPE_TURBO_4G     (1)


/* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
//extern UINT32 g_u32_turbo_dma_cw0_end_flag;
/* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

/* FIX HawkReq10000029   BEGIN   2019-06-10 : xuyuan */

//{2}
UINT32 u32_wcdma_turbo_decoder_real_output[4] = {0,0,0,0};
UINT32 u32_wcdma_turbo_decoder_ref_output[4]  = {0x01064000,0x00200002,0x00000000,0x00000000};

WAVEFORM_DTCM_SECTION
UINT32 u32_wcdma_test_vector_120[128];

UINT32 u32_temp_buf[512]  __attribute__((aligned(32)));
/* FIX HawkReq10000029   END   2019-06-10 : xuyuan */
UINT8 g_u8_lte_turbo_input_data_before[] = {
#include "./data/turbo_4g_tbs349_byte_dec_in_before.dat"
};

UINT32 g_u32_lte_turbo_output_data[] = {
#include "./data/turbo_4g_tbs349_byte_dec_out.dat"
};




vec_t  v32_V;// ����Ϊ Uint32 v32_V[2][8];
vec_t  v16_V;// ����Ϊ Uint16 v32_V[2][16];

A[a..b] = v32_V[c..d][e..f];
OR
//{3}
v32_V[c..d][e..f] = A[a..b];
����Ϊ
int k = a;
for(int i = c; i <= d; ++i)
{
for(int j = e; j <= f; ++j)
{
A[k] = v32_V[i][j];   OR   v32_V[i][j] = A[k];
++k;
}
}
assert(k == b);

/* FIX HawkBug10000053 BEGIN 2019-11-06 GuXiaofeng */
VOID ucase_demo_module_algo_branch(osa_msg_t *fsm_msg_ptr,UINT16 u16_demo_cmd)
/* FIX HawkBug10000053 END 2019-11-06 GuXiaofeng */
{

    switch(u16_demo_cmd)
    {
        case ALGO_DEMO_TEST_START_XC4210_SELF_TEST:
        {
            OSA_PRINT(OSA_PRINT_INFO, "XC4210_TASK0: u16_demo_cmd = %d", u16_demo_cmd);
            ucase_algo_start_self_test_req();
//{4}
			/* FIX HawkBug10000053 BEGIN 2019-11-06 GuXiaofeng */
			demo_intercore_msg_send(fsm_msg_ptr, MSG_XC4210_2_X1643_PARAM_CNF, DEMO_CORE_ID_X1643);
			/* FIX HawkBug10000053 END 2019-11-06 GuXiaofeng */
            break;
        }
        default:
        {
            break;
        }
    }
}
void testcase_1(void)
{
    testcase_pass();
}

void testcase_2(void)
{
    testcase_fail();
}

void testcase_3(void)
{
    //ֻҪ����testcase_fail������������ʧ�ܡ�
//{5}
    testcase_fail();

    testcase_pass();
}

void testcase_4(void)
{
}

void testcase_vstdw_v32(void)
{
    UINT32 A[VECTOR_LEN];
    vec_t  v32_a;
    UINT32 B[VECTOR_LEN] = { 0 };
    int    i;

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 1 << i;
    }
    v32_a = vlddw_v32(8, A, 0);
    vstdw_v32(8, v32_a, 0, B);

    for(i = 0; i < VECTOR_LEN; ++i)
//{6}
    {
        if(A[i] != B[i])
        {
            testcase_fail();
        }
    }

    testcase_pass();
}

void testcase_vstdw_v32_offset(void)
{
    UINT32 A[VECTOR_LEN];
    vec_t  v32_V; //Uint32 v32_V[2][8]
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];

    int i;

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 7 << i;
        C[i] = B[i] = 5 << i;
    }
//{7}

    v32_V = vlddw_v32(5, A, 3); // v32_V[0..1][3..7] = A[0..9]
    vstdw_v32(8, v32_V, 0, B);  //B[0..15] = v32_V[0..1][0..7]

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);

        if(i < 3)
        {
            /*if (B[i] != C[i])
            {
                testcase_fail();
            }*/
        }
        else if(i < 8)
        {
            if(B[i] != A[i - 3])
            {
                testcase_fail();
            }
        }
//{8}
        else if(i < 11)
        {
            /*if (B[i] != C[i])
            {
                testcase_fail();
            }*/
        }
        else
        {
            if(B[i] != A[i - 6])
            {
                testcase_fail();
            }
        }
    }

    testcase_pass();
}

void testcase_vstdw_v32_offset_2(void)
{
    UINT32 A[VECTOR_LEN];
    vec_t  v32_V; //Uint32 v32_V[2][8]
    UINT32 B[VECTOR_LEN];
//{9}
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];

    int i;

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = i + 1;
        D[i] = C[i] = B[i] = i + 21;
    }

    v32_V = vlddw_v32(2, A, 0); // v32_V[0..1][0..1] = A[0..3]
    vstdw_v32(8, v32_V, 0, B);  //B[0..15] = v32_V[0..1][0..7]

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(i < 2)
        {
            if(B[i] != A[i])
            {
                testcase_fail();
//{10}
            }
        }
        else if(i < 8)
        {
        }
        else if(i < 10)
        {
            if(B[i] != A[i - 6])
            {
                testcase_fail();
            }
        }
    }

    vstdw_v32(2, v32_V, 0, D); //B[0..4] = v32_V[0..1][0..1]

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%08X", i, D[i], D[i]);

        if(i < 2)
        {
//{11}
            if(D[i] != A[i])
            {
                testcase_fail();
            }
        }
        else if(i < 8)
        {
            if(D[i] != C[i])
            {
                testcase_fail();
            }
        }
        else if(i < 10)
        {
            if(D[i] != A[i - 6])
            {
                testcase_fail();
            }
        }
        else
        {
            if(D[i] != C[i])
            {
                testcase_fail();
//{12}
            }
        }
    }
    testcase_pass();
}

void testcase_vmpyp_v32_c32_v32_low_1(void)
{
    UINT32 A[VECTOR_LEN];
    UINT16 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN] = { 0 };
    vec_t  v32_x;
    vec_t  v32_y;
    //  vec_t  v32_c;
    int i;
    //Q16,1
    UINT32 a      = 1 << 13; // a / 2^15 = 0.25
    coef_t coef_a = vmova_a0_c32_1op(a);
    //vlbf_imm6_vps0(2);
    vlbf_uimm5_vps0(2);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = (i + 1) << 8;
        B[i] = A[i] * a / (1 << 15);
//{13}
    }

    v32_x = vlddw_v32(8, A, 0);
    v32_y = vmpyp_v32_c32_v32(8, v32_x, 0, LOW, coef_a, LOW);
    vstdw_v32(8, v32_y, 0, C);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(B[i] != (UINT16)C[i])
        {
            testcase_fail();
        }
    }

    testcase_pass();
}

void testcase_vmpyp_v32_c32_v32_low_vps0(int int_bit)
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN] = { 0 };
//{14}
    vec_t  v32_x;
    vec_t  v32_y;
    //  vec_t  v32_c;
    int i;
    //Q16,int_bit
    UINT32 a = 1 << 13; // a / 2^15 = 0.25

    coef_t coef_a = vmova_a0_c32_1op(a);
    if(int_bit >= 5)
    {
        a = 1 << 3;
    }
    switch(int_bit)
    {
#define vlbf_uimm5_vps0_case(x)  \
    \
case x : vlbf_uimm5_vps0(x + 1); \
    break

        vlbf_uimm5_vps0_case(-1);
        vlbf_uimm5_vps0_case(0);
        vlbf_uimm5_vps0_case(1);
        vlbf_uimm5_vps0_case(2);
        vlbf_uimm5_vps0_case(3);
//{15}
        vlbf_uimm5_vps0_case(4);
        vlbf_uimm5_vps0_case(5);
        vlbf_uimm5_vps0_case(6);
        vlbf_uimm5_vps0_case(7);
        vlbf_uimm5_vps0_case(8);
        vlbf_uimm5_vps0_case(9);
    //vlbf_uimm5_vps0_case(17);

    default:
        testcase_fail();
        return;
    }

    //vlbf_imm6_vps0(2);
    //vlbf_uimm5_vps0(int_bit + 1);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = (i + 1) << 8;
        B[i] = A[i] * a;

        if(int_bit == 6)
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - int_bit - int_bit + 2)));
        }
//{16}
        else if(int_bit == 7)
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - int_bit - int_bit - 1)));
        }
        else if(int_bit >= 5)
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - int_bit - int_bit)));
        }
        else if(int_bit > 0)
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - int_bit)));
        }
        else if(int_bit == 0)
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - int_bit - 1)));
        }
        else
        {
            B[i] = (UINT16)(B[i] / (1 << (16 - 0)));
        }
    }

    v32_x = vlddw_v32(8, A, 0);
    v32_y = vmpyp_v32_c32_v32(8, v32_x, 0, LOW, coef_a, LOW);
//{17}
    vstdw_v32(8, v32_y, 0, C);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);

        if(B[i] != C[i])
        {
            testcase_fail();
        }
    }

    testcase_pass();
}

void testcase_vmpyp_v32_c32_v32_low_vps0_int()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(-1);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_0()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(0);
//{18}
}

void testcase_vmpyp_v32_c32_v32_low_vps0_1()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(1);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_2()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(2);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_3()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(3);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_4()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(4);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_5()
{
//{19}
    testcase_vmpyp_v32_c32_v32_low_vps0(5);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_6()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(6);
}

void testcase_vmpyp_v32_c32_v32_low_vps0_7()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(7);
}
void testcase_vmpyp_v32_c32_v32_low_vps0_8()
{
    testcase_vmpyp_v32_c32_v32_low_vps0(8);
}

void testcase_vmpyp_v32_c32_v32_high(void)
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN] = { 0 };
    vec_t  v32_x;
    vec_t  v32_y;
//{20}
    //  vec_t  v32_c;
    int i;
    //Q32,1
    UINT32 a      = 1 << 30; // a / 2^31 = 0.5
    coef_t coef_a = vmova_a0_c32_1op(a);
    //vlbf_imm6_vps0(2);
    vlbf_uimm5_vps0(2);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = (i + 1) << 24;
        B[i] = A[i] / 2 * (a / (1 << 30)) / (1 << 16);
    }

    v32_x = vlddw_v32(8, A, 0);
    v32_y = vmpyp_v32_c32_v32(8, v32_x, 0, HIGH, coef_a, HIGH);
    vstdw_v32(8, v32_y, 0, C);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(B[i] != C[i])
        {
            testcase_fail();
//{21}
        }
    }

    testcase_pass();
}

void testcase_vadd32_v32_v32_v32(void)
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    UINT32 C[VECTOR_LEN] = { 0 };
    int    i;

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 1 << i;
        B[i] = 7 << i;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vadd32_v32_v32_v32(8, v32_a, v32_b);
//{22}
    vstdw_v32(8, v32_c, 0, C);

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        if(A[i] + B[i] != C[i])
        {
            testcase_fail();
        }
    }

    testcase_pass();
}

void testcase_vadd32_v32_v32_v32_4(void)
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    UINT32 C[VECTOR_LEN] = { 0 };
    int    i;

    for(i = 0; i < VECTOR_LEN; ++i)
//{23}
    {
        A[i] = i + 1;  // 1 << i;
        B[i] = 20 + i; // 7 << i;
        C[i] = B[i];
    }
    v32_a = vlddw_v32(2, A, 0);                  //v32_a[0..1][0..1] = A[0..3]
    v32_b = vlddw_v32(2, B, 0);                  //v32_b[0..1][0..1] = B[0..3]
    v32_c = vadd32_v32_v32_v32(2, v32_a, v32_b); //v32_c[0..1][0..1] = v32_a[0..1][0..1] + v32_b[0..1][0..1]
    vstdw_v32(2, v32_c, 0, C);                   //C[0..3] = v32_c[0..1][0..1]

    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(i < 2)
        {
            if(A[i] + B[i] != C[i])
            {
                testcase_fail();
            }
        }
        else if(i < 8)
        {
//{24}
            if(B[i] != C[i])
            {
                testcase_fail();
            }
        }
        else if(i < 10)
        {
            if(A[i - 6] + B[i - 6] != C[i])
            {
                testcase_fail();
            }
        }
        else
        {
            if(B[i] != C[i])
            {
                testcase_fail();
            }
        }
    }

    testcase_pass();
}

//{25}
void testcase_ver(void)
{
    OSA_PRINT(OSA_PRINT_INFO, "%s, %s", __DATE__, __TIME__);
}

//40λ�ļ�32λ�ģ�����浽40λ��
void testcase_vadd40_v40_v32_v40()
{
    UINT32 A[VECTOR_LEN];
    /*UINT64 B[VECTOR_LEN];*/
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    vec_t  v32_a;
    coef_t vcoeff_c;
    //vec_t  v32_b;
    vec40_t v40_c;
    vec40_t v40_d;
    int     i;
    v40_c = vclr_v40(8);
    v40_d = vclr_v40(8);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //C[i] =
        A[i] = 1 << i;
//{26}
        B[i] = 2 << i;
        C[i] = 3 << i;
    }
    v32_a    = vlddw_v32(8, A, 0);
    vcoeff_c = vlddw_c32_1dw(&C[0]);
    v40_c    = vfill_c32_v40_dw(8, vcoeff_c);
    v40_d    = vadd40_v40_v32_v40(8, v40_c, v32_a);
    vstdw_v40(8, v40_d, 0, B);
    for(i = 0; i < VECTOR_LEN / 2; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(A[i] + 3 != B[i])
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//�������
void testcase_vclr()
{
    float  a      = 1.5;
//{27}
    coef_t coef_a = vmova_a0_c32_1op(a);

    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];
    UINT32 E[VECTOR_LEN];
    /*UINT32 F[VECTOR_LEN];*/
    vec_t   v32_a;
    vec_t   v32_b;
    vec_t   v32_c;
    vec_t   v32_d;
    vec_t   v32_e;
    vprex_t vpr0;
    /*vprex_t vp_a;*/
    int i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 1 << i;
        B[i] = 2 << i;
    }
    v32_a = vlddw_v32(8, A, 0);
    vlbf_uimm5_vps0(0);
    coef_a = vclr_c32_1op();
//{28}
    v32_b  = vmpyp_v32_c32_v32(8, v32_a, 0, LOW, coef_a, LOW);
    vstdw_v32(8, v32_b, 0, B);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        if(B[i] != 0)
        {
            testcase_fail();
        }
    }
    v32_a = vclr_v32(8);
    vstdw_v32(8, v32_a, 0, B);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        ///*OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);*/
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        if(B[i] != 0)
        {
            testcase_fail();
        }
    }
    for(i = 0; i < VECTOR_LEN; ++i)
    {
//{29}
        if(i < VECTOR_LEN - 3)
        {
            C[i] = 500;
            D[i] = 600;
        }
        else
        {
            C[i] = 600;
            D[i] = 500;
        }
        E[i] = 400;
    }

    v32_c = vlddw_v32(8, C, 0);
    v32_d = vlddw_v32(8, D, 0);
    vpr0  = vcmp_v32_v32_vpr_le(8, v32_c, v32_d);
    v32_e = vclr_v32_p(8, vpr0);
    vstdw_v32(8, v32_e, 0, E);
    /*vstdw_v32(8, vpr0, 0, F);*/
    for(i = 0; i < VECTOR_LEN - 3; i++)
    {
        if(E[i] != 0)
        {
            testcase_fail();
//{30}
        }
    }

    testcase_pass();
}
//�����ֵ
void testcase_vabs()
{
    SINT32 A[VECTOR_LEN];
    SINT32 B[VECTOR_LEN];
    SINT32 C[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; i++)
    {
        if((i % 2) == 0)
        {
            A[i] = 1;
            B[i] = 0x0001;
        }
        else
        {
            A[i] = -1; //��0xFFFF FFFF16λ����
//{31}
            B[i] = 0x00010001;
        }
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vabs16_v32_v32(8, v32_a);
    vstdw_v32(8, v32_b, 0, C);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    for(i = 0; i < VECTOR_LEN; i++)
    {
        if((i % 2) == 0)
        {
            A[i] = 32769;
        }
        else
        {
//{32}
            A[i] = -32769;
        }
        B[i] = 32769;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vabs32_v32_v32(8, v32_a);
    vstdw_v32(8, v32_b, 0, C);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��λ��չ���ͻ��
void testcase_unpack()
{
    SINT32 A[VECTOR_LEN];
    SINT32 B[VECTOR_LEN];
//{33}
    SINT32 C[VECTOR_LEN];
    SINT32 D[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    vec_t  v32_d;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 3 << i;
        B[i] = 4 << i;
    }
    v32_a = vlddw_v32(4, A, 0);
    v32_b = vlddw_v32(4, B, 0); //4��ӦVECTOR_LEN/2
    //v32_a = vlddw_v32(8, A, 0);//8��ӦVECTOR_LEN/4
    //v32_b = vlddw_v32(8, B, 0);
    v32_c = vunpackl_v32_v32_w(4, v32_a, 0);
    v32_d = vunpackh_v32_v32_w(4, v32_b, 0);
    vstdw_v32(8, v32_c, 0, C);
    vstdw_v32(8, v32_d, 0, D);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
//{34}
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%08X", i, D[i], D[i]);
    }
    for(i = 0; i < VECTOR_LEN / 2; i++)
    {
        if(C[i * 2] != A[i])
        {
            testcase_fail();
        }
        if(D[i * 2] != B[i] << 16)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��ȡ�ߵ���λ����
void testcase_pack()
{
    SINT32 A[VECTOR_LEN];
    SINT32 B[VECTOR_LEN];
    SINT32 C[VECTOR_LEN];
    SINT32 D[VECTOR_LEN];
    vec_t  v32_a;
//{35}
    vec_t  v32_b;
    vec_t  v32_c;
    vec_t  v32_d;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 0x04000800 + i;
        B[i] = 0x03000500 + (i << 16);
        C[i] = 0x11110000;
        D[i] = 0x00001111;
    }
    v32_a = vlddw_v32(4, A, 0);
    v32_b = vlddw_v32(4, B, 0); //4��ӦVECTOR_LEN/2
    //v32_a = vlddw_v32(8, A, 0);//8��ӦVECTOR_LEN/4
    //v32_b = vlddw_v32(8, B, 0);
    v32_c = vpack_v32_v32_wl(4, v32_a, 0);
    v32_d = vpack_v32_v32_wh(4, v32_b, 0);
    vstdw_v32(8, v32_c, 0, C);
    vstdw_v32(8, v32_d, 0, D);

    if(C[0] != (A[0] & 0x0000FFFF) + ((A[1] & 0x0000FFFF) << 16))
    {
        testcase_fail();
    }
//{36}
    if(D[0] != ((B[0] & 0xFFFF0000) >> 16) + (B[1] & 0xFFFF0000))
    {
        testcase_fail();
    }
    if(C[1] != (A[2] & 0x0000FFFF) + ((A[3] & 0x0000FFFF) << 16))
    {
        testcase_fail();
    }
    if(D[1] != ((B[2] & 0xFFFF0000) >> 16) + (B[3] & 0xFFFF0000))
    {
        testcase_fail();
    }
    if(C[8] != (A[4] & 0x0000FFFF) + ((A[5] & 0x0000FFFF) << 16))
    {
        testcase_fail();
    }
    if(D[8] != ((B[4] & 0xFFFF0000) >> 16) + (B[5] & 0xFFFF0000))
    {
        testcase_fail();
    }
    if(C[9] != (A[6] & 0x0000FFFF) + ((A[7] & 0x0000FFFF) << 16))
    {
        testcase_fail();
    }
//{37}
    if(D[9] != ((B[6] & 0xFFFF0000) >> 16) + (B[7] & 0xFFFF0000))
    {
        testcase_fail();
    }
    testcase_pass();
}
//ʸ������
void testcase_vmove_v()
{
    SINT32 A[VECTOR_LEN];
    SINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 3 << i;
        B[i] = 4 << i;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vmov_v32_v32(8, v32_a, 0, 0);
    vstdw_v32(8, v32_b, 0, B);

    for(i = 0; i < VECTOR_LEN; i++)
//{38}
    {
        if(B[i] != 3 << i)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//ʸ��->������>ʸ���İ��˼��������
void testcase_vmove_c_and_fill()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    coef_t vcoeff_c;
    vec_t  v32_c;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 3 << i;
        B[i] = 4 << i;
//{39}
        C[i] = 1 << i;
    }
    /*v32_a = vlddw_v32(1, A, 0);*/
    v32_a    = vlddw_v32(8, A, 0);
    vcoeff_c = vmov_v32_c32_1op(v32_a, 0);
    v32_b    = vfill_c32_v32_dw(8, vcoeff_c); //ֻ��ǰ8����Ч
    v32_c    = vfillw_c32_v32(8, vcoeff_c);
    vstdw_v32(8, v32_c, 0, D);
    vstdw_v32(8, v32_a, 0, C);
    vstdw_v32(8, v32_b, 0, B);

    for(i = 0; i < VECTOR_LEN / 2; i++)
    {
        if((B[i] != 3 << 0) || (D[i] != 0x00030003))
        {
            testcase_fail();
        }
    }
    for(i = VECTOR_LEN / 2; i < VECTOR_LEN; i++)
    {
        if((B[i] != 3 << 8) || (D[i] != 0x03000300))
        {
            testcase_fail();
        }
//{40}
    }
    testcase_pass();
}
//������λ����
void testcase_vshift()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a_src;
    vec_t  v32_b_result;
    coef_t vcoeff_shift;
    UINT32 shift = 1;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = i;
        B[i] = 4 << i;
    }
    vcoeff_shift = vlddw_c32_clone_1dw(&shift);
    v32_a_src    = vlddw_v32(8, A, 0);
    v32_b_result = vshift_v32_c32_v32(8, v32_a_src, vcoeff_shift);
    vstdw_v32(8, v32_b_result, 0, B);

    for(i = 0; i < VECTOR_LEN; i++)
//{41}
    {
        if(B[i] != (i << 1))
        {
            testcase_fail();
        }
    }
    testcase_pass();
}

void testcase_and_or_xor()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];
    UINT32 E[VECTOR_LEN];
    UINT32 F[VECTOR_LEN];
    UINT32 G[VECTOR_LEN];
    vec_t  vec_const_zero = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
    vec_t  vec_test_1     = { { 1, 2, 3, 4, 5, 4, 3, 2, 1, 15, 14, 13, 12, 11, 9, 8 } };
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    vec_t  v32_d;
//{42}
    vec_t  v32_e;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 0xFFFF0000;
        B[i] = 0xF0F0F0F0;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vand_v32_v32_v32(8, v32_a, v32_b);
    v32_d = vor_v32_v32_v32(8, v32_a, v32_b);
    v32_e = vxor_v32_v32_v32(8, v32_a, v32_b);
    vstdw_v32(8, v32_c, 0, C);
    vstdw_v32(8, v32_d, 0, D);
    vstdw_v32(8, v32_e, 0, E);
    vstdw_v32(8, vec_const_zero, 0, F);
    vstdw_v32(8, vec_test_1, 0, G);

    for(i = 0; i < VECTOR_LEN; i++)
    {
        if(C[i] != 0xF0F00000)
        {
            testcase_fail();
        }
//{43}
        if(D[i] != 0xFFFFF0F0)
        {
            testcase_fail();
        }
        if(E[i] != 0x0F0FF0F0)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��������
void testcase_vpermutew_v32_v32()
{
    vec_t vcfg = { { 0x012389AB,
                     0xFEDC7654,
                     0x12345678,
                     0x87654321,
                     0x12341234,
                     0x56781234,
                     0x0,
                     0x0,
                     0xDC985410,
                     0x2367ABEF,
//{44}
                     0x00000000,
                     0x00000000,
                     0x0,
                     0x0,
                     0x0,
                     0x0 } };
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 0x12345678;
        B[i] = i;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vpermutew_v32_v32(8, vcfg, v32_a);
    vstdw_v32(8, v32_b, 0, B);
    for(i = 0; i < 4; i++)
    {
        if(B[i] != 0x56781234)
        {
            testcase_fail();
//{45}
        }
    }
    for(i = 4; i < 8; i++)
    {
        if(B[i] != 0x12345678)
        {
            testcase_fail();
        }
    }
    for(i = 8; i < 12; i++)
    {
        if(B[i] != 0x12345678)
        {
            testcase_fail();
        }
    }
    for(i = 12; i < VECTOR_LEN; i++)
    {
        if(B[i] != 0x56781234)
        {
            testcase_fail();
        }
    }
    testcase_pass();
//{46}
}
//��ͣ��������������λ
void testcase_vaddint()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = i;
        B[i] = i + 1;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vaddint_v32_v32(8, v32_a);
    vstdw_v32(8, v32_b, 0, B);

    for(i = 0; i <= VECTOR_LEN / 2; i = i + 8)
    {
        if(B[i] != i + B[i + 1] + B[i + 2] + B[i + 3] + B[i + 4] + B[i + 5] + B[i + 6] + B[i + 7])
        {
            testcase_fail();
        }
//{47}
    }

    testcase_pass();
}

void testcase_vbpack()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        /*A[i] = 0x04320870+i;*/
        /*A[i] = 0x00320870 + i;*/
        A[i] = i;
        B[i] = i;
    }

    v32_a = vlddw_v32(8, A, 0);
    v32_b = vbpack_v32_v32_w(8, v32_a);
    vstdw_v32(8, v32_b, 0, B);
 
//{48}
    if(B[0] != 0x00004444)
    {
        testcase_fail();
    }
    else if(B[8] != 0x00004444)
    {
        testcase_fail();
    }
    else
    {
        testcase_pass();
    }
}
//����
void testcase_vsub32_v32_v32_v32()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
//{49}
    {
        A[i] = 2 << i;
        B[i] = 1;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vsub32_v32_v32_v32(8, v32_a, v32_b);
    vstdw_v32(8, v32_c, 0, C);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        if(C[i] != A[i] - B[i])
        {
            testcase_fail();
        }
    }

    testcase_pass();
}
//��δ��֤���
void testcase_vtracback_v32_v32_k7()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
//{50}
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        /*A[i] = 0x12345670+ i;*/
        A[i] = 0x12345678 + i;
        B[i] = 0x500;
        C[i] = 0x600;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vclr_v32(8);
    //v32_b = vtracback_v32_v32_k7(v32_a, v32_b);
    vstdw_v32(8, v32_b, 0, B);
    v32_c = vtracback_v32_v32_k7(v32_a, v32_b);
    vstdw_v32(8, v32_c, 0, C);
    #if 0
    for(i = 0; i < VECTOR_LEN; i++)
    {
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
    }
//{51}
    #endif
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  A[i] = 0x98765438 + i;
    //  B[i] = 0x500;
    //  C[i] = 0x600;
    //}
    //v32_a = vlddw_v32(8, A, 0);
    //v32_b = vclr_v32(8);
    //v32_c = vtracback_v32_v32_k7(v32_a, v32_b);
    //vstdw_v32(8, v32_c, 0, C);

    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%08X", i, C[i], C[i]);
    //}
    for(i = 0; i <= VECTOR_LEN; i++)
    {
        if(C[i] != A[i] - B[i])
        {
            testcase_fail();
        }
//{52}
    }

    testcase_pass();
}

//copy A[0]��A[8]
void testcase_vcopy_v32_vpr()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32* ptest = NULL_PTR;
    UINT32  C[VECTOR_LEN];
    vec_t   v32_a;
    //vec_t  v32_b;
    vprex_t vpre_a;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 500 + i;
        B[i] = i;
        C[i] = 0x500;
    }
    ptest  = &C[0];
    v32_a  = vlddw_v32(8, A, 0);
//{53}
    vpre_a = vcopy_v32_vpr(v32_a);
    vstdw_vpr_dw(vpre_a, ptest);
    //vstdw_vpr_dw(vpre_a, B);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        B[i] = *(ptest + i);
    }
    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
    //}
    for(i = 0; i < VECTOR_LEN; i = i + 8)
    {
        if(B[i] != (A[i] & 0xffff))
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//����
void testcase_vdivw_v32_v32()
{
    UINT16 A[VECTOR_LEN] = {
//{54}
        2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16,
    };
    //UINT32 A[VECTOR_LEN] = { 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16 };
    UINT16 B[VECTOR_LEN] = { 2, 2, 2, 2, 4, 4, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16 };
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vdivw_v32_v32(v32_a, 0, 0);
    vstdw_v32(8, v32_b, 0, B);
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        if(B[0] != 0x4000) //0x4000=2^16/A[0]>>1
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��δ��֤���
void testcase_vexp32_v32_v32_w()
{
//{55}
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 A_after[VECTOR_LEN];
    UINT32 B_after[VECTOR_LEN];
    //UINT16 A_after[VECTOR_LEN];
    //UINT16 B_after[VECTOR_LEN];
    vec_t v32_a;
    vec_t v32_b;
    int   i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 2;
        /*B[i] = i+2;*/
        B[i]       = i + 1;
        A_after[i] = 0x1111;
        B_after[i] = 0x3333;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_b = vexp32_v32_v32_w(8, v32_a, v32_b, 0);
    v32_a = vexp32_v32_v32_w(8, v32_b, v32_a, 0);
    vstdw_v32(8, v32_a, 0, A_after);
    vstdw_v32(8, v32_b, 0, B_after);
    #if 0
//{56}
    for(i = 0; i < VECTOR_LEN; i++)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%08X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%08X", i, B[i], B[i]);
        OAL_POWER_PRINT(
            UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A_after[%2d]=%10d, 0x%08X", i, A_after[i], A_after[i]);
        OAL_POWER_PRINT(
            UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B_after[%2d]=%10d, 0x%08X", i, B_after[i], B_after[i]);
    }
    #endif
}
//��Ϊ<0x00_7FFF_FFFF<FF_8000_0000<���䣬���������޷����
void testcase_vlim_v40_v40()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];
    UINT32 E[VECTOR_LEN];
    //UINT32 F[VECTOR_LEN];
    vec_t   v32_a;
    vec_t   v32_b;
    coef_t  vcoeff_c;
    vec40_t v40_c;
//{57}
    vec40_t v40_d;
    vec40_t v40_e;
    //vec40_t  v40_f;
    int i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //A[i] = 3 << i;
        A[i] = 3;
        //B[i] = 4 << i;
        C[i] = 1 << i;
        D[i] = 2 << 1;
    }
    for(i = 0; i < VECTOR_LEN; i = i + 3)
    {
        B[i] = 0x7FFAFFFA;
    }
    for(i = 1; i < VECTOR_LEN; i = i + 3)
    {
        B[i] = 0x7FFFFFFF;
    }
    for(i = 2; i < VECTOR_LEN; i = i + 3)
    {
        B[i] = 0x80000000;
    }
//{58}
    v32_a    = vlddw_v32(8, A, 0);
    v32_b    = vlddw_v32(8, B, 0);
    vcoeff_c = vmov_v32_c32_1op(v32_a, 0);
    v40_c    = vfillw_c32_v40(8, vcoeff_c);
    v40_d    = vadd40_v40_v32_v40(8, v40_c, v32_b);
    vstdw_v40(8, v40_c, 0, C);
    vstdw_v40(8, v40_d, 0, D);
    v40_e = vlim_v40_v40(8, v40_d);
    //v40_f = vlimw_v40_v40(8, v40_d);
    vstdw_v40(8, v40_e, 0, E);
    //vstdw_v40(8, v40_f, 0, F);
    //vstdw_v32(8, v32_b, 0, B);
    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "E[%2d]=%10d, 0x%8X", i, E[i], E[i]);
    //  //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "F[%2d]=%10d, 0x%08X", i, F[i], F[i]);
    //}
    for(i = 0; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != 0x7FFAFFFA)
        {
            testcase_fail();
//{59}
        }
    }
    for(i = 1; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != 0x7FFFFFFF)
        {
            testcase_fail();
        }
    }
    for(i = 2; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != 0x80000000)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}

void testcase_vlimw_v40_v40()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
//{60}
    UINT32  D[VECTOR_LEN];
    UINT32  E[VECTOR_LEN];
    vec_t   v32_a;
    vec_t   v32_b;
    coef_t  vcoeff_c;
    vec40_t v40_c;
    vec40_t v40_d;
    vec40_t v40_e;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 3;
        C[i] = 1 << i;
        D[i] = 2 << 1;
    }
    for(i = 0; i < VECTOR_LEN; i = i + 3)
    {
        B[i] = 0x7FFA7FFA;
    }
    for(i = 1; i < VECTOR_LEN; i = i + 3)
    {
        B[i] = 0x7FFF7FFF;
    }
    for(i = 2; i < VECTOR_LEN; i = i + 3)
//{61}
    {
        B[i] = 0x80008000;
    }
    v32_a    = vlddw_v32(8, A, 0);
    v32_b    = vlddw_v32(8, B, 0);
    vcoeff_c = vmov_v32_c32_1op(v32_a, 0);
    v40_c    = vfillw_c32_v40(8, vcoeff_c);
    v40_d    = vadd40_v40_v32_v40(8, v40_c, v32_b);
    vstdw_v40(8, v40_c, 0, C);
    vstdw_v40(8, v40_d, 0, D);
    v40_e = vlimw_v40_v40(8, v40_d);
    vstdw_v40(8, v40_e, 0, E);
    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "E[%2d]=%10d, 0x%8X", i, E[i], E[i]);
    //}
    for(i = 0; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != (0x00030003 + 0x7FFA7FFA))
        //if (E[i] != 0x7FFAFFFA)
        {
            testcase_fail();
//{62}
        }
    }
    for(i = 1; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != 0x7FFF7FFF)
        {
            testcase_fail();
        }
    }
    for(i = 2; i < VECTOR_LEN; i = i + 3)
    {
        if(E[i] != (0x00030003 + 0x80008000))
        {
            testcase_fail();
        }
    }
    testcase_pass();
}

void testcase_vmax_v32_v32_v32()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
//{63}
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    int    i;
    for(i = 0; i < VECTOR_LEN / 2; ++i)
    {
        A[i] = i;
        B[i] = 4;
        C[i] = 500;
    }
    for(i = VECTOR_LEN / 2; i < VECTOR_LEN; ++i)
    {
        A[i] = i;
        B[i] = 60;
        C[i] = 500;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vmax_v32_v32_v32(8, v32_a, v32_b);
    vstdw_v32(8, v32_c, 0, C);
    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //}
//{64}
    for(i = 0; i < 5; ++i)
    {
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    for(i = 5; i < VECTOR_LEN / 2; ++i)
    {
        if(C[i] != A[i])
        {
            testcase_fail();
        }
    }
    for(i = VECTOR_LEN / 2; i < VECTOR_LEN; ++i)
    {
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    testcase_pass();
}

//{65}
void testcase_vmaxw_v32_v32_v32()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 2 << i;
        B[i] = 0x40000004;
        C[i] = 500;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vmaxw_v32_v32_v32(8, v32_a, v32_b);
    vstdw_v32(8, v32_c, 0, C);
    //for (i = 0; i < VECTOR_LEN; i++)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //}
//{66}
    for(i = 0; i < 2; ++i)
    {
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    for(i = 3; i < 14; ++i)
    {
        if(C[i] != A[i] + (B[i] & 0xFFFF0000))
        {
            testcase_fail();
        }
    }
    for(i = 14; i < 15; ++i) //��i=14ʱ���������������Ӧ������
    {
        if(C[i] != B[i])
        {
            testcase_fail();
        }
    }
    for(i = 15; i < VECTOR_LEN; ++i)
    {
        if(C[i] != B[i])
//{67}
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//ʵ��+0x8000����
void testcase_vround_v40_v40()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
    vec_t   v32_a;
    vec40_t v40_b;
    vec40_t v40_c;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 2 << i;
        B[i] = 0x400;
        C[i] = 500;
    }
    v32_a = vlddw_v32(8, A, 0);
    v40_b = vmov_v32_v40(8, v32_a, 0, 0);
//{68}
    vstdw_v40(8, v40_b, 0, B);
    v40_c = vround_v40_v40(8, v40_b);
    vstdw_v40(8, v40_c, 0, C);
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //}
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        if(C[i] != B[i] + 0x8000)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//���ţ���ֵ���ƣ���ֵ����
void testcase_vscale_v40_c32_v32_and_vscale_v40_imm4_v32()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
//{69}
    UINT32  D[VECTOR_LEN];
    vec_t   v32_a;
    vec40_t v40_b;
    vec_t   v32_c;
    coef_t  coef_shift;
    vec_t   v32_d;
    //UINT32 shift = 2;//<<2
    UINT32 shift = -2; //>>2
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 2 << i;
        B[i] = 0x400;
        C[i] = 500;
        D[i] = 600;
    }

    v32_a      = vlddw_v32(8, A, 0);
    v40_b      = vmov_v32_v40(8, v32_a, 0, 0);
    coef_shift = vlddw_c32_clone_1dw(&shift);
    v32_c      = vscale_v40_c32_v32(8, v40_b, coef_shift, 0);
    v32_d      = vscale_v40_imm4_v32(8, v40_b, -2, 0);
    vstdw_v40(8, v40_b, 0, B);
    vstdw_v32(8, v32_c, 0, C);
//{70}
    vstdw_v32(8, v32_d, 0, D);
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  /*OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);*/
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    //}
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        if(C[i] != (B[i] >> 2))
        {
            testcase_fail();
        }
        if(D[i] != (B[i] >> 2))
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��δ��֤���
void testcase_vsqrt_v32_v32()
{
//{71}
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 1024;
        B[i] = 500;
    }
    //for (i = VECTOR_LEN/2; i < VECTOR_LEN ; ++i)
    //{
    //  A[i] = 16;
    //  B[i] = 500;
    //}
    v32_a = vlddw_v32(8, A, 0);
    //v32_b = vsqrt_v32_v32(v32_a, 0, 0);
    v32_b = vsqrt_v32_v32(v32_a, 2, 2);
    vstdw_v32(8, v32_b, 0, B);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
    }
//{72}
    for(i = 0; i < VECTOR_LEN / 2; ++i)
    {
        if(B[i] != 2)
        {
            testcase_fail();
        }
    }
    for(i = VECTOR_LEN / 2; i < VECTOR_LEN; ++i)
    {
        if(B[i] != 4)
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//����ת��
void testcase_vtransdw_v32_v32_uimm3_v32_2dw()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    UINT32 C[VECTOR_LEN];
    UINT32 D[VECTOR_LEN];
    UINT32 E[VECTOR_LEN];
//{73}
    UINT32 F[VECTOR_LEN];
    UINT32 G[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    vec_t  v32_c;
    vec_t  v32_d;
    vec_t  v32_e;
    vec_t  v32_f;
    vec_t  v32_g;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 0x30003000 + i;
        B[i] = 0x40004000 + i;
        C[i] = 500;
        D[i] = 500;
        E[i] = 500;
        F[i] = 500;
        G[i] = 500;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vtransdw_v32_v32_uimm3_v32_2dw(2, v32_a, v32_b, 0);
    v32_d = vtransdw_v32_v32_uimm3_v32_2dw(2, v32_a, v32_b, 1);
//{74}
    v32_e = vtransdw_v32_v32_uimm3_v32_2dw(2, v32_a, v32_b, 2);
    v32_f = vtransdw_v32_v32_uimm3_v32_2dw(2, v32_a, v32_b, 3);
    v32_g = vtransdw_v32_v32_uimm3_v32_2dw(2, v32_a, v32_b, 4); //���6
    vstdw_v32(8, v32_c, 0, C);
    vstdw_v32(8, v32_d, 0, D);
    vstdw_v32(8, v32_e, 0, E);
    vstdw_v32(8, v32_f, 0, F);
    vstdw_v32(8, v32_g, 0, G);
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "E[%2d]=%10d, 0x%8X", i, E[i], E[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "F[%2d]=%10d, 0x%8X", i, F[i], F[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "G[%2d]=%10d, 0x%8X", i, G[i], G[i]);
    //}
    if(((C[0] != A[0]) && (C[2] != A[1])) && ((C[1] != B[0]) && (C[3] != B[1])))
    {
        testcase_fail();
    }
    else if(((C[8] != A[8]) && (C[10] != A[9])) && ((C[9] != B[8]) && (C[11] != B[9])))
    {
//{75}
        testcase_fail();
    }
    else if(((D[0] != A[1]) && (D[2] != A[2])) && ((D[1] != B[1]) && (D[3] != B[2])))
    {
        testcase_fail();
    }
    else if(((D[8] != A[9]) && (D[10] != A[10])) && ((D[9] != B[9]) && (D[11] != B[10])))
    {
        testcase_fail();
    }
    else if(((E[0] != A[2]) && (E[2] != A[3])) && ((E[1] != B[2]) && (E[3] != B[3])))
    {
        testcase_fail();
    }
    else if(((E[8] != A[10]) && (E[10] != A[11])) && ((E[9] != B[10]) && (E[11] != B[11])))
    {
        testcase_fail();
    }
    else if(((F[0] != A[3]) && (F[2] != A[4])) && ((F[1] != B[3]) && (F[3] != B[4])))
    {
        testcase_fail();
    }
    else if(((F[8] != A[11]) && (F[10] != A[13])) && ((F[9] != B[11]) && (F[11] != B[12])))
    {
//{76}
        testcase_fail();
    }
    else if(((G[0] != A[4]) && (G[2] != A[5])) && ((G[1] != B[4]) && (G[3] != B[5])))
    {
        testcase_fail();
    }
    else if(((G[8] != A[12]) && (G[10] != A[14])) && ((G[9] != B[12]) && (G[11] != B[13])))
    {
        testcase_fail();
    }
    else
    {
        testcase_pass();
    }
}
//32λ����ƽ���ټ�40λ�ģ�Ȼ�����40λ�ļĴ����ڣ����Է���2����
void testcase_vsqacx_v32_v32_v40_v40()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
    UINT32  D[VECTOR_LEN];
    UINT32  Ebefore[VECTOR_LEN];
    UINT32  Fbefore[VECTOR_LEN];
//{77}
    UINT32  Eafter[VECTOR_LEN];
    UINT32  Fafter[VECTOR_LEN];
    UINT32  G[VECTOR_LEN];
    vec_t   v32_a;
    vec_t   v32_b;
    vec_t   v32_c;
    vec_t   v32_d;
    vec40_t v40_e;
    vec40_t v40_f;
    vec40_t v40_g;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i]       = i;
//{81}
        B[i]       = (i + 1);
        C[i]       = 0x10001000;
        D[i]       = 0x20002000;
        Ebefore[i] = 500;
        Fbefore[i] = 500;
        Eafter[i]  = 600;
        Fafter[i]  = 600;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vlddw_v32(8, B, 0);
    v32_c = vlddw_v32(8, C, 0);
    v32_d = vlddw_v32(8, D, 0);
    v40_e = vmov_v32_v40(8, v32_c, 0, 0);
    v40_f = vmov_v32_v40(8, v32_d, 0, 0);
    vstdw_v40(8, v40_e, 0, Ebefore);
    vstdw_v40(8, v40_f, 0, Fbefore);
    v40_g = vsqacx_v32_v32_v40_v40(16, v32_a, 0, v32_b, 0, v40_e, v40_f);
    vstdw_v40(8, v40_e, 0, Eafter);
    vstdw_v40(8, v40_f, 0, Fafter);
    vstdw_v40(8, v40_g, 0, G);
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
//{82}
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "Ebefore[%2d]=%10d, 0x%8X", i, Ebefore[i], Ebefore[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "Fbefore[%2d]=%10d, 0x%8X", i, Fbefore[i], Fbefore[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "Eafter[%2d]=%10d, 0x%8X", i, Eafter[i], Eafter[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "Fafter[%2d]=%10d, 0x%8X", i, Fafter[i], Fafter[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "G[%2d]=%10d, 0x%8X", i, G[i], G[i]);
    //}
    for(i = 0; i < VECTOR_LEN; i++)
    {
        if(G[i] != Ebefore[i] + A[i] * A[i])
        {
            testcase_fail();
        }
        if(Fafter[i] != Fbefore[i] + B[i] * B[i])
        {
            testcase_fail();
        }
        if(Eafter[i] != Eafter[i])
        {
            testcase_fail();
        }
//{83}
    }
    testcase_pass();
}
//������
void testcase_vneg_v32_v32()
{
    UINT32 A[VECTOR_LEN];
    UINT32 B[VECTOR_LEN];
    vec_t  v32_a;
    vec_t  v32_b;
    int    i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = i;
        B[i] = 0x10001000;
    }
    v32_a = vlddw_v32(8, A, 0);
    v32_b = vneg_v32_v32(8, v32_a);
    vstdw_v32(8, v32_b, 0, B);
    //for (i = 0; i < VECTOR_LEN; ++i)
    //{
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
    //  OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
//{84}
    //}
    for(i = 0; i < VECTOR_LEN; i++)
    {
        if(B[i] != -A[i])
        {
            testcase_fail();
        }
    }
    testcase_pass();
}
//��δ�㶮
void testcase_vnorm_v40_v32_v32()
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
    UINT32  D[VECTOR_LEN];
    vec_t   v32_a;
    vec40_t v40_FixedPointValue;
    vec_t   v32_Mantissa;
    vec_t   v32_Exponent;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
//{85}
    {
        //A[i] = 0x10001000+i;
        A[i] = i;
        B[i] = 0x1000;
        C[i] = 0x2000;
        D[i] = 0x3000;
    }
    v32_a               = vlddw_v32(8, A, 0);
    v40_FixedPointValue = vmov_v32_v40(8, v32_a, 0, 0);
    vstdw_v40(8, v40_FixedPointValue, 0, B);
    v32_Mantissa = vnorm_v40_v32_v32(8, v40_FixedPointValue, 0, v32_Exponent);
    vstdw_v32(8, v32_Mantissa, 0, C);
    vstdw_v32(8, v32_Exponent, 0, D);
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
       // OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
        //OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
    }
}
//�����δ���ֹ���
void testcase_vmac_v32_c32_v40()
//{86}
{
    UINT32  A[VECTOR_LEN];
    UINT32  B[VECTOR_LEN];
    UINT32  C[VECTOR_LEN];
    UINT32  D[VECTOR_LEN];
    UINT32  E[VECTOR_LEN];
    UINT32  F[VECTOR_LEN];
    vec_t   v32_a;
    vec40_t v40_b;
    vec40_t v40_c;
    vec40_t v40_d;
    vec40_t v40_e;
    vec40_t v40_f;
    coef_t  coef_factor;
    UINT32  factor = 2;
    int     i;
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        A[i] = 0x10001000 + i;
        B[i] = 0x1000;
        C[i] = 0x2000;
        D[i] = 0x3000;
        E[i] = 0x4000;
//{87}
        F[i] = 0x5000;
    }
    v32_a       = vlddw_v32(8, A, 0);
    v40_b       = vmov_v32_v40(8, v32_a, 0, 0);
    coef_factor = vlddw_c32_clone_1dw(&factor);
    v40_c       = vmac_v32_c32_v40(8, v40_b, 0, HIGH, coef_factor, HIGH, v40_c);
    v40_d       = vmac_v32_c32_v40(8, v40_b, 0, LOW, coef_factor, LOW, v40_d);
    v40_e       = vmac_v32_c32_v40(8, v40_b, 0, LOW, coef_factor, HIGH, v40_e);
    v40_f       = vmac_v32_c32_v40(8, v40_b, 0, HIGH, coef_factor, LOW, v40_f);
    vstdw_v40(8, v40_b, 0, B);
    vstdw_v40(8, v40_d, 0, D);
    vstdw_v40(8, v40_e, 0, E);
    vstdw_v40(8, v40_f, 0, F);
    vstdw_v40(8, v40_c, 0, C);
    #if 0
    for(i = 0; i < VECTOR_LEN; ++i)
    {
        
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "A[%2d]=%10d, 0x%8X", i, A[i], A[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "B[%2d]=%10d, 0x%8X", i, B[i], B[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "C[%2d]=%10d, 0x%8X", i, C[i], C[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "D[%2d]=%10d, 0x%8X", i, D[i], D[i]);
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "E[%2d]=%10d, 0x%8X", i, E[i], E[i]);
//{88}
        OAL_POWER_PRINT(UNSPECIFIED_STANDBY_ID, UNSPECIFIED_MODE, "F[%2d]=%10d, 0x%8X", i, F[i], F[i]);
    }
    #endif

}


UINT32 dd_absolute_time_get(VOID)
{
    UINT32 u32_1div10_ms = 0;
    UINT32 u32_1div26_us = 0;

    UINT32 u32_time_get = 0;

    //DD_IRQ_SAVE_AREA;
    OSA_IRQ_SAVE_AREA;

    /*get curr mmc time*/
    OSA_IRQ_DISABLE;
    u32_1div10_ms = *pDDR_PWR_AT_C2;
    u32_1div26_us = *pDDR_PWR_AT_C1; /* core bug: C1 & C2 must read simultaneity */
    OSA_IRQ_RESTORE;
        
//{89}
    u32_time_get = u32_1div10_ms * 100 + u32_1div26_us / 26;

    return (u32_time_get);
}

WAVEFORM_ITCM_SECTION
VOID fic_config(){
  // region4-7 unused
  // ADD7_START
  //register int r0 asm("r0");
  //register int r1 asm("r1");
  
  asm("mov #0xffffc, r0");
  asm("mov #0x590, r1");
  asm("out{dw, cpm} r0, (r1)");

  asm("mov #0xffffc, r0");
  asm("mov #0x580, r1");
  asm("out{dw, cpm} r0, (r1)");

  asm("mov #0xffffc, r0");
  asm("mov #0x570, r1");
  asm("out{dw, cpm} r0, (r1)");
//{90}

  asm("mov #0xffffc, r0");
  asm("mov #0x560, r1");
  asm("out{dw, cpm} r0, (r1)");

  // ADD3_START, MID EDP, region3 start 0xF004_0000
  asm("mov #0x00F0040, r0");
  asm("mov #0x550, r1");
  asm("out{dw, cpm} r0, (r1)");

  // ADD2_START, MID FICM1, region2 start 0xF002_0000
  asm("mov #0x22F0020, r0");
  asm("mov #0x540, r1");
  asm("out{dw, cpm} r0, (r1)");

  // ADD1_START, MID FICM0, region1 start 0xF000_0000
  asm("mov #0x11F0000, r0");
  asm("mov #0x530, r1");
  asm("out{dw, cpm} r0, (r1)");

  return;
}

//{91}

/* FIX HawkReq10000029   BEGIN   2019-06-10 : xuyuan */
VOID algo_turbo_3g_test_new(void)
{
    st_3g_turbo_config st_turbo_user_config;
    UINT32* u32p_bman_addr_dtcm;
    DEV_HANDLE dev_handle;
    VOID_PTR pTurboPara;
    SINT32 s32_status;
    UINT32 u32_status;
    UINT16 u16_loop_i;
    UINT32_PTR u32p_temp;

    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    g_u32_turbo_dma_cw0_end_flag = 0;
    /* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

    u32p_bman_addr_dtcm = OSA_MEM_ALLOC(g_u16_gpool_ID[0], 1024);

    dev_handle = dev_open("TURBO0", &s32_status, DEV_NO_OP_FLAG);

    /*�û��ӿ�����*/
    st_turbo_user_config.u32_comm_mode = ALGO_XC4210_HWA_TYPE_TURBO_3G;
//{92}
    st_turbo_user_config.u32_input_addr = (UINT32)&u32_wcdma_test_vector_120[0];
    //st_turbo_user_config.u32_de_rm_size = 0xFFFFFFFF;
    st_turbo_user_config.u32_output_addr = (UINT32)u32_wcdma_turbo_decoder_real_output;
    st_turbo_user_config.u32_tb_size = 120;
    st_turbo_user_config.u32_temp_buf_addr = (UINT32)&u32_temp_buf[0];//0x60000;
    st_turbo_user_config.u32_bman_addr = (UINT32)u32p_bman_addr_dtcm;
    st_turbo_user_config.u32_iter_num = 4;
    //st_turbo_user_config.u32_crc_result =  0XF;
    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    st_turbo_user_config.fcb = user_turbo_dma_cw0_end_isr;
	/* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

    pTurboPara = (VOID_PTR)(&st_turbo_user_config);
    u32_status = dev_control(dev_handle, st_turbo_user_config.u32_comm_mode, pTurboPara);

    dev_close(dev_handle);

    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    if(g_u32_turbo_dma_cw0_end_flag)
    {
        u32p_temp = (UINT32*)st_turbo_user_config.u32_output_addr;

        for(u16_loop_i = 0; u16_loop_i < 4; u16_loop_i++)
//{93}
        {
            if(u32_wcdma_turbo_decoder_ref_output[u16_loop_i]!=u32p_temp[u16_loop_i])
            {
                OSA_PRINT(OSA_PRINT_INFO, "turbo w mode result compare failed : %d, correct=%x, error=%x", u16_loop_i, u32_wcdma_turbo_decoder_ref_output[u16_loop_i], u32p_temp[u16_loop_i]);
                break;
            }
        }

        if(u16_loop_i != 4)
        {

            testcase_fail();
        }
        else
        {
            testcase_pass();
        }
    }
    /* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

    OSA_MEM_FREE((VOID_PTR)u32p_bman_addr_dtcm);
}

//{94}
VOID algo_turbo_4g_test_new(VOID)
{
    UINT32                                   u32_len;
    UINT32                                   u32_i;
    UINT32                                   u32_turbo_out_len;
    st_4g_turbo_config                       st_turbo_user_config;

    UINT32* u32p_4g_out_buff;
    UINT32* u32p_4g_out_buff1;
    UINT32* u32p_temp_buff;
    UINT32* u32p_dtcm_buff;
    SINT32 s32_status = 0x12345678;
    DEV_HANDLE dev_handle;
    VOID_PTR pTurboPara;
    UINT32 u32_status;
    UINT16 u16_tbs_list;

    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    g_u32_turbo_dma_cw0_end_flag = 0;
    /* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

    u16_tbs_list = 349;//NOTE: unit is byte
    u32_turbo_out_len = (u16_tbs_list + 3) / 4 * 4;
//{95}
    u32p_4g_out_buff1 = OSA_MEM_ALLOC(g_u16_gpool_ID[2], (u32_turbo_out_len + 64));
    u32_len = (CACAHE_MEM_ALIGN - ((UINT32)(u32p_4g_out_buff1) & (UINT32)(CACAHE_MEM_ALIGN - 1)));
    u32p_4g_out_buff = u32p_4g_out_buff1 + (u32_len / 4);
    OSA_MEM_SET(u32p_4g_out_buff, (UINT8)0, (UINT32)u32_turbo_out_len);

    u32p_dtcm_buff = OSA_MEM_ALLOC(g_u16_gpool_ID[0], TURBO_DTCM_INPUT_BUFF_BYTE);
    u32p_temp_buff = OSA_MEM_ALLOC(g_u16_gpool_ID[1], (TURBO_LTE_INPUT_WORD << 1));

    dev_handle = dev_open("TURBO0", &s32_status, DEV_NO_OP_FLAG);

    st_turbo_user_config.u32_comm_mode = ALGO_XC4210_HWA_TYPE_TURBO_4G;
    st_turbo_user_config.u32_input_addr = (UINT32)&g_u8_lte_turbo_input_data_before;
    //st_turbo_user_config.u32_de_rm_size = 8544;
    st_turbo_user_config.u32_output_addr = (UINT32)u32p_4g_out_buff;
    st_turbo_user_config.u32_tb_size = 349;//byte
    st_turbo_user_config.u32_temp_buf_addr = (UINT32)u32p_temp_buff;//&g_u8_input_data6;
    st_turbo_user_config.u32_bman_addr = (UINT32)u32p_dtcm_buff;
    st_turbo_user_config.u32_crc_mode = 0;/*24A*/
    st_turbo_user_config.u32_iter_num = (UINT32)5;
    //st_turbo_user_config.u32_cb_result = 0xF;
    //st_turbo_user_config.u32_tb_result = 0xF;
    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    st_turbo_user_config.fcb = user_turbo_dma_cw0_end_isr;
//{96}
    /* FIX HawkReq10000044   END   2019-08-01 : xuyuan */

    pTurboPara = (VOID_PTR)(&st_turbo_user_config);
    u32_status = dev_control(dev_handle, st_turbo_user_config.u32_comm_mode, pTurboPara);

    dev_close(dev_handle);
    
    /* FIX HawkReq10000044   BEGIN   2019-08-01 : xuyuan */
    if(g_u32_turbo_dma_cw0_end_flag)
    {
        for(u32_i = 0; u32_i < 88; u32_i++)
        {
            if(g_u32_lte_turbo_output_data[u32_i] != u32p_4g_out_buff[u32_i])
            {
                OSA_PRINT(OSA_PRINT_INFO, "turbo lte mode result compare failed : %d, correct=%x, error=%x", u32_i, g_u32_lte_turbo_output_data[u32_i], u32p_4g_out_buff[u32_i]);
                break;
            }
        }

        if(88 == u32_i)
        {
            testcase_pass();
        }
//{97}
        else
        {
            testcase_fail();
        }
    }
    /* FIX HawkReq10000044   END   2019-08-01 : xuyuan */
    
    OSA_MEM_FREE((VOID_PTR)u32p_4g_out_buff1);
    OSA_MEM_FREE((VOID_PTR)u32p_dtcm_buff);
    OSA_MEM_FREE((VOID_PTR)u32p_temp_buff);
}
/* FIX HawkReq10000029   END   2019-06-10 : xuyuan */

void self_test_callback(void)
{

    testcase_ver();

    TEST_CASE(testcase_vstdw_v32);
    TEST_CASE(testcase_vstdw_v32_offset);
    TEST_CASE(testcase_vstdw_v32_offset_2);
    TEST_CASE(testcase_vadd32_v32_v32_v32);

//{98}
    TEST_CASE(testcase_vadd32_v32_v32_v32_4);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_1);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_high);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_int);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_0);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_1);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_2);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_3);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_4);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_5);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_6);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_7);
    TEST_CASE(testcase_vmpyp_v32_c32_v32_low_vps0_8);

    TEST_CASE(testcase_vadd40_v40_v32_v40);
    TEST_CASE(testcase_vclr);
    TEST_CASE(testcase_vabs);
    TEST_CASE(testcase_unpack);
    TEST_CASE(testcase_pack);
    TEST_CASE(testcase_vmove_v);
    TEST_CASE(testcase_vmove_c_and_fill);
    TEST_CASE(testcase_vshift);
    TEST_CASE(testcase_and_or_xor);
//{99}
    TEST_CASE(testcase_vpermutew_v32_v32);
    TEST_CASE(testcase_vaddint);
    TEST_CASE(testcase_vbpack);
    TEST_CASE(testcase_vcopy_v32_vpr);
    TEST_CASE(testcase_vdivw_v32_v32); //��δ�������
    //TEST_CASE(testcase_vexp32_v32_v32_w);
    TEST_CASE(testcase_vsub32_v32_v32_v32);
    //TEST_CASE(testcase_vtracback_v32_v32_k7);
    TEST_CASE(testcase_vlim_v40_v40);
    TEST_CASE(testcase_vlimw_v40_v40);
    TEST_CASE(testcase_vmax_v32_v32_v32);
    TEST_CASE(testcase_vmaxw_v32_v32_v32);
    TEST_CASE(testcase_vround_v40_v40);
    TEST_CASE(testcase_vscale_v40_c32_v32_and_vscale_v40_imm4_v32);
    //TEST_CASE(testcase_vsqrt_v32_v32);
    TEST_CASE(testcase_vtransdw_v32_v32_uimm3_v32_2dw);
    TEST_CASE(testcase_vsqacx_v32_v32_v40_v40);
    TEST_CASE(testcase_vneg_v32_v32);
    //TEST_CASE(fft_lib_512_point_test);

    algo_common_test(); 

    fic_config();
    
    algo_qbman_init();

    common_qman_config();

	TEST_CASE(mrd_accelerator_test);

    TEST_CASE(mimo_hwa_single_port_lmmse_64qam_demo_test);
	
    TEST_CASE(algo_harq_turbo_demo_test);
	//TEST_CASE(hac_lpf_test);
    #if 0
    fic_config();

    algo_qbman_init();

    common_qman_config();

    TEST_CASE(algo_wcdma_fwht_demo);

    TEST_CASE(algo_wcdma_mrd_demo);

    TEST_CASE(algo_harq_turbo_demo_test);


    TEST_CASE(hac_lpf_test);
    #endif
    /* FIX HawkReq10000029   BEGIN   2019-06-10 : xuyuan */
    TEST_CASE(algo_turbo_3g_test_new);
    TEST_CASE(algo_turbo_4g_test_new);
    /* FIX HawkReq10000029   END   2019-06-10 : xuyuan */
    testcase_ver(); // ���һ����
}
