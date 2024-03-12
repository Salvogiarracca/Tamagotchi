;/*********************************************************************************************************
;**--------------File Info---------------------------------------------------------------------------------
;** File name:           utils.s
;** Descriptions:        Set of low level functions that can be useful for exam 
;** Correlated files:    utils.h
;**--------------------------------------------------------------------------------------------------------
;*********************************************************************************************************/
; Flags: NZCV
; - EQ:(==) Z set 
; - NE:(!=) Z clear 
; - HI:(> ) C set, Z clear 
; - HS:(>=) C set 
; - LO:(< ) C clear
; - LS:(<=) C clear, Z set 
; - MI:(negative) N set
; - PL:(positive) N clear
; - VS:(overflow) V set
; - VC:(no oflow) V clear

; ALU instructions:
; - TST r1, r2: (&)logical AND 	(Test Bits)
; - TEQ r1, r2: (&)logical AND	(Test Equivalence)
; - CMP r1, r2: arithmetic subtract (-)
; - ADD, MUL, SUB: 32 bit
; - ADC, U/SMULL, SBC: 64 bit
; - U/SDIV: 32 bit
; - LSL/R: logical shift left/right
; - MOV Rd, #const: loads 16-bit const (0x00XY00XY)
; - LDR Rd, =const: loads (word) const in register
; - LDR Rd, =label: loads address in register
; - LDRB/H/D/M: loads byte/half-word/2-words/multiple
; - STRB/H/D/M: stores byte/half-word/2-words/multiple
					
; Branch instructions:
; - B label: branch to label
; - BX Rn: branch to register address
; - BL label: branch and link
; - BLX Rn: branch to register and link

; Conditional (after CMP Rn, op {= Rm/#imm}):
; - BEQ: branch if Rn == op
; - BLO: branch if Rn < op
; - BLS: branch if Rn <= op
; - BHI: branch if Rn > op
; - BHS: branch if Rn >= op
; - see "Flags" for other suffix

; Directives:
; - name EQU expr : constant declaration
; - {label} DCxx expr{,expr}: constant allocation
; 	- DCB/W: define costant byte/half-word
;	- DCWU: half-word unaligned
;	- DCD: define costant word
;	- DCDU: word unaligned
;		- ('expr' can be a string)
; - ALIGN {expr{, offset}}: alignment, pad with 0s
; 	- current location: n * expr + offset
; - {label} SPACE expr: memory block reservation
; 	- expr: number of bytes
; - LTORG: collocates the literal pool

; Addressing:
; - load/store Rd, [Rn, offset{, LSL #const}]{!}: pre-indexed
;	- offset: 12-bit const or register
; 	- !: updates Rn at end of instruction
; - load/store Rd, [Rn], offset: post-indexed
; 	- offset: Rn is always updated

						AREA asm_functions, CODE, READONLY
;############### THIS FUNCTION PERFORM AVERAGE OF POS AND NEG IN AN ARRAY AND RETURN THE DIFFERNCE ######## turno 3 appello 6 febbraio
									EXPORT differenza_media_positivi_negativi
differenza_media_positivi_negativi	FUNCTION ; code goes below
									; save current sp for a faster access to parameters in the stack
									MOV r12, sp
									; save volatile registers
									STMFD sp!, {r4-r8, r10-r11, lr}
									
									mov r4, #0
									mov r5, #0
									mov r6, #0x80000000
d_m_p_n_loop						ldr r3, [r0, r4]
									push {r4}
									mov r4, #0xFF
									tst r3, r6
									addnes r5, r5, r3	;sum of negative values
									addne r7, r7, #1  	;number of negative values
									strvs r4, [r2]
									addeqs r8, r8, r3  	;sum of positive values
									strvs r4, [r2]

									pop {r4}
									add r4, r4, #4
									cmp r1, r4, lsr #2
									bne d_m_p_n_loop
									
									sub r4, r1, r7		;number of positive values
									
									sdiv r5, r5, r7		;neg avg
									sdiv r8, r8, r4		;pos avg
									
									add r0, r8, r5		;return on r0				

									LDMFD sp!, {r4-r8, r10-r11, pc}
										
									ENDFUNC
;##########################################################################################################	

									EXPORT media_e_superiori_alla_media
media_e_superiori_alla_media		FUNCTION ; code goes below
									; save current sp for a faster access to parameters in the stack
									MOV r12, sp
									; save volatile registers
									STMFD sp!, {r4-r8, r10-r11, lr}
									
									mov r4, #0
									mov r5, #0
loop1								ldrb r6, [r0, r4]
									add r5, r5, r6
									add r4, r4, #1
									cmp r1, r4
									bne loop1
									
									sdiv r5, r5, r1
									
									mov r4, #0
									mov r7, #0
loop2								ldrb r6, [r0, r4]
									cmp r6, r5
									addgt r7, r7, #1
									add r4, r4, #1
									cmp r1, r4
									bne loop2
									
									strb r7, [r2]
									mov r0, r5 ;not required
									
									LDMFD sp!, {r4-r8, r10-r11, pc}
										
									ENDFUNC

;############### THIS FUNCTION PERFORM MULTIPLICATION WITH ACCUMULATION OF ELEMENTS IN AN ARRAY ########### turno 1 appello 6 febbraio
						ALIGN
						EXPORT calcola_somma_prodotto
calcola_somma_prodotto	FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						;r0 vett
						;r1 n
						;r2 char *alarm
						mov r4, #0
						mov r7, #0
c_s_p_loop				ldm r0!, {r5, r6}
						mla r7, r5, r6, r7
						add r4, r4, #8
						cmp r1, r4, lsr #4
						bne c_s_p_loop
						
						mov r8, #1
						mov r3, #-1
						cmp r7, #0xFF
						strgt r8, [r2]
						b c_s_p_finish
						str r3, [r2]
						
c_s_p_finish			mov r0, r7
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC							
;##########################################################################################################

;############### THIS FUNCTION PERFORM R0 % R1 END RETURN THE REMAINDER ON R0 #############################
						EXPORT divisible
divisible				FUNCTION 
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
							
divisible_loop			cmp r0, r1
						blt divisible_finish 		;e1 is lower than e2 so return e1
						beq divisible_equal
						
						sub r0, r0, r1
						b divisible_loop
						
divisible_equal			mov r0, #0	
divisible_finish		; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
						ENDFUNC	
;##########################################################################################################				

;############### THIS FUNCTION COUNTS THE ONES IN CONTAIN IN REGISTER R0 AND RETURN THIS VALUE ############
						EXPORT count_bits_to_1
count_bits_to_1			FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}

						mov r4, #32 		;number of left shift to perform
						mov r5, #1  		;register to shift
						mov r6, #0  		;number of ones
count_bits_to_1_loop	tst r0, r5  		;bitwise and between r0 and r5 ;if 1 clear Zero flag ; if 0 set Zero flag
						addne r6, r6, #1   	; this add is performed only if Zero flag = 0 
						lsl r5, #1  		;shift the one of 1 position left
						subs r4, r4, #1  	;this sub set the Z flag if the result of subtraction is equal to zero
						bne count_bits_to_1_loop

						mov r0, r6
						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

;############### THIS FUNCTION SEARCH IF A VALUE IS PRESENT IN A DEFINED LITERAL POOL #####################
s_i_p_N					DCD 0x3					
s_i_p_pool				DCD 0x68, 0x86, 0x13			
					
						EXPORT search_in_pool
search_in_pool			FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						
						mov r7, #0
						ldr r4, =s_i_p_N
						ldr r4, [r4]
						ldr r5, =s_i_p_pool
s_i_p_loop				ldr r6, [r5]
						teq r0, r6
						add r7, r7, #1
						beq s_i_p_found
						add r5, r5, #4
						
						subs r4, r4, #1
						bne s_i_p_loop
						mov r0, #-1 		;not found -1 is returned
						b s_i_p_finish
s_i_p_found				mov r0, r7			;position in the pool of the value is returned
s_i_p_finish
						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

;############### THIS FUNCTION COUNTS HOW MANY NUMBERS ARE BOTH NEGATIVE AND ODD ##########################
						EXPORT count_negative_and_odd
count_negative_and_odd	FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						
						mov r4, #0
						mov r6, #0   ;tmp var if 2 numbers are both negative and odd
						mov r7, #1
						mov r8, #0
c_n_a_o_loop					ldr r5, [r0, r4]
						tst r5, #1   ;test if odd
						addne r6, r6, #1
						lsl r7, r7, #31
						tst r5, r7 	 ;test if negative
						addne r6, r6, #1 
						teq r6, #2
						addeq r8, r8, #1  ;both negative and odd
						mov r6, #0
						mov r7, #1
						add r4, r4, #4
						subs r1, r1, #1
						bne c_n_a_o_loop
						
						mov r0, r8
						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

;############### THIS FUNCTION RETURN THE DIFFERENCE BETWEEN POSITIVE AND NEGATIVE ITEMS IN AN ARRAY ######
						EXPORT diff_pos_neg
diff_pos_neg			FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						;r0 buffer
						; r1 buffer size
						; r2 *overflow variable
						
						mov r3, #0
						mov r4, #0
						mov r5, #0 	;num pos
						mov r6, #0	;num neg
						mov r7, #1
						lsl r7, #31
d_p_n_loop				ldr r8, [r0, r4]
						tst r8, r7
						addne r6, r6, #1
						addeq r5, r5, #1
						add r4, r4, #4
						adds r3, r3, #1
						cmp r3, r1
						bne d_p_n_loop
						
						cmp r6, #0 ;if all numbers are positive, then overflow
						bne d_p_n_finish
						mov r4, #1
						str r4, [r2]
d_p_n_finish			sub r0, r5, r6 

						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

;############### THIS FUNCTION PERFORM AN AVERAGE OF ARRAY ELEMENTS WITHOUT "BORDERS" #####################
						EXPORT avg_press_with_filter
avg_press_with_filter	FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						mov r7, #0
						sub r8, r1, r2
						mov r4, #0
a_p_w_f_loop			ldr r6, [r0, r4]
						cmp r2, r4, lsr#2
						bgt a_p_w_f_go_on
						cmp r8, r4, lsr#2 
						ble a_p_w_f_go_on
						add r7, r7, r6							
a_p_w_f_go_on			add r4, r4, #4
						cmp r4, r1, lsl #2
						bne a_p_w_f_loop
						
						lsl r2, #1
						sub r1, r1, r2
						udiv r7, r7, r1
						mov r0, r7
						
						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

;############### THIS FUNCTION TEST IF VALUE SEQUENCE OF VETT IS INCREASING MONOTONE ######################
						ALIGN ;only to remove annoying warnings 
						EXPORT increasing_monotone
increasing_monotone		FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
							
						; code body
						mov r4, #0
						mov r6, #0
						mov r7, r1
						mov r8, #0
i_m_loop				ldrb r5, [r0, r4]
						cmp r5, r6
						addge r8, r8, #1
						mov r6, r5
						add r4, r4, #1
						subs r7, r7, #1
						bne i_m_loop
						
						teq r1, r8
						moveq r0, #0xFF   	;return this value if values sequence is increasing monotone
						movne r0, #0x55		;return this value if not

						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################			

;############### THIS FUNCTION RECEIVE A NUMBER AND INSERT IT INTO AN ARRAY ORDINATELY (DESCENDING ORDER) #
						EXPORT get_and_sort
get_and_sort			FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}

						add r2, r0, r2
						
g_a_s_loop				sub r2, r2, #1
						sub r3, r2, #1
						cmp r0, r3
						bhi	g_a_s_finish
						ldrb r4, [r3]				
						cmp r4, r1
						strblo r4, [r2]
						bhi	g_a_s_finish
						b g_a_s_loop
						; setup a value for R0 to return
g_a_s_finish		 	strb r1, [r2]
						; restore volatile registers
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################			

;############### THIS FUNCTION PERFORMS THE BUBBLE SORT (ASCENDING) OF AN ARRAY IN LOCO ###################
						EXPORT bubble_sort
bubble_sort				FUNCTION ; code goes below
						; save current sp for a faster access to parameters in the stack
						MOV r12, sp
						; save volatile registers
						STMFD sp!, {r4-r8, r10-r11, lr}
						; Bubble sort an array of 32bit integers in place
						; Arguments: r0 = Array location, r1 = Array size
bsort_next				mov r4, #0 					;r4 = current element number
						mov r5, #0 					;r5 = number of swaps
													;start loop
bsort_loop				add r6, r4, #1 				;r6 = next element number
						cmp r6, r1					;check for the end of the array
						bge bsort_check				;when we reach the end, check for changes
						ldr r7, [r0, r4, lsl #2]	;r7 = current element value
						ldr r8, [r0, r6, lsl #2]	;r8 = next element value
						cmp r7, r8					;compare element values
						strgt r8, [r0, r4, lsl #2]	;if r7 > r8, store current value at next 
						strgt r7, [r0, r6, lsl #2]	;if r7 > r8, Store next value at current
						addgt r5, r5, #1			;if r7 > r8, increment swap counter
						mov r4, r6					;advance to the next element
						b bsort_loop				;end loop
bsort_check				cmp r5, #0					;were there changes this iteration?
						subgt r1, r1, #1			;optimization: skip last value in next loop
						bgt bsort_next				;if there were changes, do it again
													;NO RETURN VALUE (VOID)
						LDMFD sp!, {r4-r8, r10-r11, pc}
							
						ENDFUNC
;##########################################################################################################

						END
					

;/*****************************************************************************
;**                            End Of File
;******************************************************************************/
