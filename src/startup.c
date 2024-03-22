#include <stdint.h>

extern uint32_t _etext; 
extern uint32_t _srelocate; 
extern uint32_t _erelocate; 
extern uint32_t _sbss; 
extern uint32_t _ebss; 
extern uint32_t _stack_top; 

void main(void); 

void Reset_Handler(void);
void Default_Handler(void); 

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Hard_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Bus_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Svcall_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Debug_Monitor_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Pendsv_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Systick_Handler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t vector[114] __attribute__((section(".vector"))) = {
        (uint32_t)&_stack_top,
        (uint32_t)&Reset_Handler,
        (uint32_t)&NMI_Handler,
        (uint32_t)&Hard_Fault_Handler, 
        (uint32_t)&Bus_Fault_Handler,
        (uint32_t)&Usage_Fault_Handler,
        0,
        0,
        0,
        0,
        0,
        (uint32_t)&Svcall_Handler,
        (uint32_t)&Debug_Monitor_Handler,
        0,
        0,
        (uint32_t)&Pendsv_Handler,
        (uint32_t)&Systick_Handler,
};

void Default_Handler(void){
        while(1);
}

void Reset_Handler(void){
    uint32_t *pSrc, *pDest; 
        
    pSrc = &_etext;
    pDest = &_srelocate; 

    if (pSrc != pDest){
        for (; pDest < &_erelocate;){
            *pDest++ = *pSrc++;
        }
    }


    for (pDest = &_sbss; pDest < &_ebss;){
        *pDest++ = 0;
    }


    main(); 

}


