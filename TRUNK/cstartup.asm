;=====================================================================
; File Name   : cstartup.asm
; Description : Startup routine for csu32P10
;               This file contains the CSCC startup routine           
;               and must usually be tailored to suit customer's hardware
; Body Name   : csu32P10
; Toolchain   : cscc V1.0.x
; Date        : 05/16/2017
;=====================================================================


;=====================================================================
; Register define eare
;=====================================================================
ind0					.equ		0x0
fsr0					.equ		0x2
status					.equ		0x4	
;bsr					.equ		0x8	
eadrh					.equ		0xA
eadrl					.equ		0xB
edat					.equ		0xC



;======================================================================
; macro define : init bank0~1 all sram to zero 
;======================================================================
init_bank01_sram_to_zero .macro bankx_start_addr, bankx_sram_sizes, temp_label
	movlw bankx_sram_sizes					; bankx sram sizes(less than 0x100)
	movwf RSP								; temp var(stack var)
	movlw bankx_start_addr					; bankx sram start address
	movwf fsr0
	movlw 0x00
temp_label:
	movwf ind0
	incf fsr0,1
	decfsz RSP, 1
	goto temp_label
.endm



;=====================================================================
; Basic Settings for User
;=====================================================================
LOOP_AT_END				.equ 		1		; Endless waiting after main()
CPU_HALT				.equ 		0		; Exception of invalid instruction
BANK0_SRAM_START_ADDR	.equ		0x40	; Bank0 sram start address
BANK0_SRAM_SIZES		.equ		0x40	; Bank0 sram sizes
FP						.equ		0x68	; Pseudo frame point(only at bank0)
RSP						.equ		0x7F	; Pseudo stack point top(only at bank0)
SP_PAGE_BANK 			.equ		0x00 	; PAGE and BANK for SP(sp on bank0, 0x00 => bsr)
LIBCSCC_TEMP_SIZES		.equ		0x06	; libcscc temp var sizes
LIBCSCC_TEMP_VAR_START_ADDR	 .equ	0x40	; libcscc temp var start addr



;=====================================================================
; GLOBAL area
;=====================================================================
.global	SP_PAGE_BANK					; public SP page bank symbol
.global	RSP								; public pseudo stack point symbol
.global	SP								; public stack point symbol
.global FP								; public frame point symbol
.global ind0							
.global fsr0
.global status
;.global bsr
.global eadrh
.global eadrl
.global edat
.global __swsub_status					; public cscc buildin status var
.global LIBCSCC_TEMP_VAR_START_ADDR		; public libcscc temp var start addr
.global LIBCSCC_TEMP_SIZES				; public libcscc temp var sizes
.global SAVED_ISR_AREA					; public backup libcscc temp var for isr


;=====================================================================
; EXTERN area
;=====================================================================
.extern _main							; where to begin execution
.extern CSCC_BANK0_INIT_TAB_START		; address of bank0 init table
.extern CSCC_BANK0_INIT_TAB_SIZE		; size of bank0 init table(word as a unit)
.extern CSCC_INTERRUPT_FUNCTION_ADDR	; interrupt function address



;=====================================================================
; SP ram size 
;=====================================================================
SP_RAM .section	bank0
	SP .ds 	2	
.ends



;=====================================================================
; Starting setup/reset code 
; CSCC_INIT_CODE - where the execution actually begins
;=====================================================================
CSCC_INIT_CODE 		.section rom,addr=0x00
V_RESET:
	goto __init_sram_to_zero
.ends



;=====================================================================
; Interrupt vector section 
;=====================================================================
CSCC_INTERRUPT_VECTOR	.section rom,addr=0x04
	goto CSCC_INTERRUPT_FUNCTION_ADDR
.ends



;======================================================================
; Init all sram to zero 
;======================================================================
CSCC_INIT_SRAM_TO_ZERO		.section rom
__init_sram_to_zero:
	;init bank0 sram
	init_bank01_sram_to_zero BANK0_SRAM_START_ADDR, BANK0_SRAM_SIZES, temp_bank0_init_label
	
	;goto init global var
	goto __init_global_var
.ends 	



;======================================================================
; Init all global variables 
;======================================================================
CSCC_INIT_GLOBAL_VAR		.section rom
__init_global_var:
	;not support global var init
	
__sp_init:									;sp reg init
	movlw .low(RSP)							;load rsp low byte to w
	movwf SP								;low w to sp
	movlw SP_PAGE_BANK						;move sp bank value to w
	movwf SP+1								;save sp bank value in sp+1
	
	goto __program_startup					
.ends



;=====================================================================	
; Now when we are init all global variables, then goto main function
;=====================================================================
.text
__program_startup:
	goto _main								; execute main()
	
__program_end:
;.if	LOOP_AT_END
;	goto	$								; 1. Endless Loop
;.endif
;.if CPU_HALT
;	halt									; 2. CPU Stop
;.endif
.ends 



;======================================================================
; Pseudo Stack point 
;======================================================================
CSCC_SIM_SP_stack	.section ram,addr=FP
	.ds		(RSP - FP + 1)					; Pseudo stack sizes 
.ends


;======================================================================
; __swsub_status sizes 
;======================================================================
__swsub_cscc_s		.section  	bank0
	__swsub_status		.ds			1	
.ends


;======================================================================
; reserve sizes for isr
;======================================================================
CSCC_RESERVE_AREA	.section   bank0
	SAVED_ISR_AREA	.ds		   LIBCSCC_TEMP_SIZES	
.ends



