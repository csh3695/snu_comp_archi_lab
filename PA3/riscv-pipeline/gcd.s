x10 : lhs, x11 : rhs


GCD:
    beq x10 x11 EXIT
    bge x10 x11 C1
    sub x11 x11 x10
    beq x0 x0 GCD
C1:
    sub x10 x10 x11
    beq x0 x0 GCD
EXIT:
    


// x10 : opt, x11 : count
FIB:
    addi t0 x0 1
    sd t0 0(x10)
    addi t1 t0 1
    bge x11 t0 CASE1
    beq x0 x0 RET:
CASE1:
    sd t0 8(x10)
    addi t2 x0 2
    //for문
FOR:
    bge t2 x11 RET
    addi t3 x0 t2
    mul t3 t3 8
    addi t3 t3 x10
    ld t4 -16(t3)
    ld t5 -8(t3)
    add t4 t4 t5
    sd t4 0(t3)
    beq x0 x0 FOR
RET:
    jr ra


//Selection Sort
// a0 A[], a1 size

for(int i=0;i<size;i++){
    int minaddr = i;
    for(int j=i;j<size;j++){
        if(a[minaddr]>a[j]) minaddr = j;
    }
    swap(i, minaddr);
}

//


    li t0, 0
fortest1:
    bge t0 a1 EXIT1
    mv t1 t0
    mv t2 t0
fortest2:
    bge t1 a1 EXIT2
    muli t3 t1 8
    add t3 t3 a0
    muli t4 t2 8 
    add t4 t4 a0
    ld t3 0(t3)
    ld t4 0(t4)
    ble t4 t3 JMP
    mv t2 t1
JMP:
    addi t1 t1 1
    beq x0 x0 fortest1
EXIT2:
    swap(t0, t2)
    muli t0 t0 8
    muli t2 t2 8
    ld t3 0(t0)
    ld t4 0(t2)
    sd t3 0(t2)
    sd t4 0(t0)
    addi t0 t0 1
EXIT1:

//fibonacci

