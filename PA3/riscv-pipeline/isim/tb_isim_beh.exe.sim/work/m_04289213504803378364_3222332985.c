/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/csehome/csh3695/Desktop/PA3/CompArchi/PA3/memory.v";
static int ng1[] = {778330484, 0, 29556, 0};
static unsigned int ng2[] = {508U, 0U, 0U, 0U};
static unsigned int ng3[] = {0U, 0U};



static void Initial_28_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(29, ng0);

LAB2:    xsi_set_current_line(31, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1880);
    xsi_vlogfile_readmemh(t1, 48, t2, 0, 0, 0, 0);

LAB1:    return;
}

static void Cont_34_1(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[16];
    char t7[16];
    char t66[8];
    char t73[8];
    char *t1;
    char *t2;
    char *t5;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    unsigned int t20;
    char *t21;
    unsigned int t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    char *t34;
    char *t35;
    unsigned int t36;
    char *t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    int t46;
    int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    char *t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    char *t63;
    char *t64;
    char *t65;
    char *t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    char *t72;
    char *t74;
    char *t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    char *t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;
    char *t88;

LAB0:    t1 = (t0 + 3040U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 1320U);
    t5 = *((char **)t2);
    t2 = ((char*)((ng2)));
    xsi_vlogtype_unsigned_bit_neg(t6, 64, t2, 64);
    t8 = 0;

LAB7:    t9 = (t8 < 2);
    if (t9 == 1)
        goto LAB8;

LAB9:    xsi_vlogtype_logic(t4, 1, t7, 64);
    t54 = (t4 + 4);
    t55 = *((unsigned int *)t4);
    t56 = *((unsigned int *)t54);
    t57 = (t55 || t56);
    if (t57 > 0)
        goto LAB10;

LAB11:    t59 = *((unsigned int *)t4);
    t60 = (~(t59));
    t61 = *((unsigned int *)t54);
    t62 = (t60 || t61);
    if (t62 > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t54) > 0)
        goto LAB14;

LAB15:    if (*((unsigned int *)t4) > 0)
        goto LAB16;

LAB17:    memcpy(t3, t66, 8);

LAB18:    t83 = (t0 + 3440);
    t84 = (t83 + 56U);
    t85 = *((char **)t84);
    t86 = (t85 + 56U);
    t87 = *((char **)t86);
    memcpy(t87, t3, 8);
    xsi_driver_vfirst_trans(t83, 0, 31);
    t88 = (t0 + 3360);
    *((int *)t88) = 1;

LAB1:    return;
LAB4:    t29 = (t8 * 8);
    t30 = *((unsigned int *)t13);
    t31 = *((unsigned int *)t23);
    *((unsigned int *)t13) = (t30 | t31);
    t32 = (t5 + t29);
    t33 = (t29 + 4);
    t34 = (t5 + t33);
    t35 = (t6 + t29);
    t36 = (t29 + 4);
    t37 = (t6 + t36);
    t38 = *((unsigned int *)t32);
    t39 = (~(t38));
    t40 = *((unsigned int *)t34);
    t41 = (~(t40));
    t42 = *((unsigned int *)t35);
    t43 = (~(t42));
    t44 = *((unsigned int *)t37);
    t45 = (~(t44));
    t46 = (t39 & t41);
    t47 = (t43 & t45);
    t48 = (~(t46));
    t49 = (~(t47));
    t50 = *((unsigned int *)t23);
    *((unsigned int *)t23) = (t50 & t48);
    t51 = *((unsigned int *)t23);
    *((unsigned int *)t23) = (t51 & t49);
    t52 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t52 & t48);
    t53 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t53 & t49);

LAB6:    t8 = (t8 + 1);
    goto LAB7;

LAB5:    goto LAB6;

LAB8:    t10 = (t8 * 8);
    t11 = (t5 + t10);
    t12 = (t6 + t10);
    t13 = (t7 + t10);
    t14 = *((unsigned int *)t11);
    t15 = *((unsigned int *)t12);
    t16 = (t14 & t15);
    *((unsigned int *)t13) = t16;
    t17 = (t8 * 8);
    t18 = (t17 + 4);
    t19 = (t5 + t18);
    t20 = (t17 + 4);
    t21 = (t6 + t20);
    t22 = (t17 + 4);
    t23 = (t7 + t22);
    t24 = *((unsigned int *)t19);
    t25 = *((unsigned int *)t21);
    t26 = (t24 | t25);
    *((unsigned int *)t23) = t26;
    t27 = *((unsigned int *)t23);
    t28 = (t27 != 0);
    if (t28 == 1)
        goto LAB4;
    else
        goto LAB5;

LAB10:    t58 = ((char*)((ng3)));
    goto LAB11;

LAB12:    t63 = (t0 + 1880);
    t64 = (t63 + 56U);
    t65 = *((char **)t64);
    t67 = (t0 + 1880);
    t68 = (t67 + 72U);
    t69 = *((char **)t68);
    t70 = (t0 + 1880);
    t71 = (t70 + 64U);
    t72 = *((char **)t71);
    t74 = (t0 + 1320U);
    t75 = *((char **)t74);
    memset(t73, 0, 8);
    t74 = (t73 + 4);
    t76 = (t75 + 4);
    t77 = *((unsigned int *)t75);
    t78 = (t77 >> 2);
    *((unsigned int *)t73) = t78;
    t79 = *((unsigned int *)t76);
    t80 = (t79 >> 2);
    *((unsigned int *)t74) = t80;
    t81 = *((unsigned int *)t73);
    *((unsigned int *)t73) = (t81 & 127U);
    t82 = *((unsigned int *)t74);
    *((unsigned int *)t74) = (t82 & 127U);
    xsi_vlog_generic_get_array_select_value(t66, 32, t65, t69, t72, 2, 1, t73, 7, 2);
    goto LAB13;

LAB14:    xsi_vlog_unsigned_bit_combine(t3, 32, t58, 32, t66, 32);
    goto LAB18;

LAB16:    memcpy(t3, t58, 8);
    goto LAB18;

}


extern void work_m_04289213504803378364_3222332985_init()
{
	static char *pe[] = {(void *)Initial_28_0,(void *)Cont_34_1};
	xsi_register_didat("work_m_04289213504803378364_3222332985", "isim/tb_isim_beh.exe.sim/work/m_04289213504803378364_3222332985.didat");
	xsi_register_executes(pe);
}
