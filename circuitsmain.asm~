;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**
;Author information
;  Author name: Justin Stewart
;  Author email: scubastew@csu.fullerton.edu
;  Author location: Long Beach, Calif.
;Course information
;  Course number: CPSC240
;  Assignment number: 2
;  Due date: 2015-Sep-10
;Project information
;  Project title: Four-Device Current Calculator
;  Purpose: The purpose of this project is to demonstrate vector operations by utilizing user given watts and voltage and calculating the resulting current. This is then
;	    output to the user. 
;  Status: Executed with no errors.
;  Project files: circuitsdriver.c, circuitsmain.asm
;Module information
;  File name: circuitsmain.asm
;  This module's call name: circuits
;  Language: X86-64
;  Syntax: Intel
;  Date last modified: 2015-Sep-9
;  Purpose: Calculate the current given voltage and wattage for four devices.
;  Status: Executed with no errors.
;  Future enhancements: None planned.
;Translator information
;  Linux: nasm -f elf64 -l circuitsmain.lis -o circuitsmain.o circuitsmain.asm
;References and credits
;  Holliday, Test Presence of AVX - Project
;  Holliday, Floating Point Input and Ouput - Project
;  http://www.felixcloutier.com/x86/DIVPD.html - Information on DIVPD
;  http://www.felixcloutier.com/x86/VBROADCAST.html - Information on VBROADCAST
;Format information
;  Page width: 172 columns
;  Begin comments: 61
;  Optimal print specification: Landscape, 7 points, monospace, 8½x11 paper
;Permission Information
;  This work is private and shall not be posted online, copied or referenced. 
;===== Begin area for source code =========================================================================================================================================

extern printf                                               ;External program used to output data, backup of registers is important if data is to be preserved

extern scanf						    ;External program used to retrieve data, backup of registers is important if data is to be preserved
	
global circuits                                             ;Set a global call name in order to be called by another program, i.e. the driver.

segment .data                                               ;Initialized data are placed in this segment

;===== Messages to be output to user ======================================================================================================================================

welcome db "This program will help analyze direct current circuits configured in parallel.", 10, 0

voltprompt db "Please enter the voltage of the entire circuit in volts: ", 0

powerprompt db "Enter the power of 4 devices (watts) seperated by space and press enter: ", 0

thanks db 10, "Thank you. The computations have completed with the following results.", 10, 0

circuithead db 10, "Circuit total voltage: %1.18lf V", 10, 0

devicehead db "Device number:		1				2				3				4", 10, 0

powerout db "Power (watts):	%1.18lf		%1.18lf		%1.18lf		%1.18lf", 10, 0

currentout db "Current (amps):	%1.18lf		%1.18lf		%1.18lf		%1.18lf", 10, 0

totalcurrent db 10, "Total current in the circuit is %1.18lf amps.", 10, 0

totalpower db "Total power in the circuit is %1.18lf watts.", 10, 0

farewell db "The analyzer program will now return the total power to the driver.", 10, 0

;===== Declare output formats =============================================================================================================================================

circuits.stringformat db "%s", 0

;===== Declare input formats ==============================================================================================================================================

circuits.inputformat db "%lf", 0

circuits.fourfloatinput db "%lf %lf %lf %lf", 0

segment .bss                                                ;Uninitialized data are declared in this segment

;==========================================================================================================================================================================
;===== Begin the application here: Calculate the current in 4 devices given voltage and power consumption =================================================================
;==========================================================================================================================================================================

segment .text                                               ;Instructions for the program are placed in the following segment

circuits:                                                   ;Begin execution of the program here

;The next two instructions must be performed at the start of every assembly program.
push       rbp                                              ;This marks the start of a new stack frame belonging to this execution of this function.
mov        rbp, rsp                                         ;rbp holds the address of the start of this new stack frame.  When this function returns to its caller rbp must
                                                            ;hold the same value it holds now.

;===== Output the welcome message =========================================================================================================================================
;No important data in registers, therefore printf will be called without backup of any data.

mov  qword rax, 0                                           ;Zero indicates to printf that there is no data to grab from lower registers
mov        rdi, .stringformat                               ;"%s"
mov        rsi, welcome                                     ;"This program will help analyze direct current circuits configured in parallel."
call printf                                                 ;An external function handles output

;===== Output the prompt to the user for the voltage of entire circuit ====================================================================================================
;No important data in registers, therefore printf will be called without backup of any data.

mov  qword rax, 0                                           ;Zero indicates to printf that there is no data to grab from lower registers
mov    	   rdi, .stringformat                               ;"%s"
mov 	   rsi, voltprompt                                  ;"Please enter the voltage of the entire circuit in volts: "
call printf                                           	    ;An external function handles output

;===== Retrieve voltage of the entire circuit in volts and broadcast across ymm15 ========================================================
;No important data in registers, therefore scanf will be called without backup of any data.

mov  qword rax, 0					    ;Zero indicates to scanf that there is no data to grab from lower registers
mov 	   rdi, .inputformat				    ;"%lf"
push qword 0						    ;Reserve 8 bytes of storage for the incomming number
mov 	   rsi, rsp					    ;Give scanf a point to the reserved storage
call scanf					    	    ;An external function handles input of voltage from user
vbroadcastsd ymm15, [rsp]				    ;Broadcast(Copy) the user inputted circuit voltage across register ymm15
pop	   rax						    ;Make free the storage that was used by scanf

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt volt  volt  volt |
;         |-----------------------|

;===== Output the prompt to the user for the power of the 4 devices =======================================================================================================
;Important data in top most registers, printf should NOT change this data. If it is corrupted, try backup at this point. 

mov  qword rax, 0                                           ;Zero indicates to printf that there is no data to grab from lower registers
mov    	   rdi, .stringformat                               ;"%s"
mov 	   rsi, powerprompt                                 ;"Enter the power of 4 devices (watts) seperated by space and press enter: "
call printf                                           	    ;An external function handles output

;===== Retrieve power of the 4 devices and store the values in ymm14 and ymm13 ============================================================================================
;Important data in top most registers, scanf should NOT change this data. If it is corrupted, try backup at this point. 

mov  qword rax, 0					    ;Zero indicates to printf that there is no data to grab from lower registers
mov 	   rdi, .fourfloatinput				    ;"%lf %lf %lf %lf"
push qword 0						    ;Reserve 8 bytes of storage for the incomming number
mov 	   rsi, rsp					    ;Give scanf a point to the reserved storage for power consumption of device 1
push qword 0						    ;Reserve 8 bytes of storage for the incomming number
mov	   rdx, rsp					    ;Give scanf a point to the reserved storage for power consumption of device 2
push qword 0						    ;Reserve 8 bytes of storage for the incomming number
mov	   rcx, rsp					    ;Give scanf a point to the reserved storage for power consumption of device 3
push qword 0						    ;Reserve 8 bytes of storage for the incomming number
mov	   r8, rsp					    ;Give scanf a point to the reserved storage for power consumtpion of device 4

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:|  0.0 | rsi
;          |------|
;   rsp+16:|  0.0 | rdx
;          |------|
;   rsp+8: |  0.0 | rcx
;          |------|
;   rsp:   |  0.0 | r8
;          |------|

call scanf					    	    ;An external function handles input from user

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:| pow1 | rsi
;          |------|
;   rsp+16:| pow2 | rdx
;          |------|
;   rsp+8: | pow3 | rcx
;          |------|
;   rsp:   | pow4 | r8
;          |------|

vmovupd	   ymm14, [rsp]					    ;Copy the user inputted power consumption of 4 devices from the integer stack to ymm14
vmovupd	   ymm13, [rsp]					    ;Copy the user inputted power consumption of 4 devices from the integer stack to ymm13

pop	   rax						    ;Make free the storage that was used by scanf
pop	   rax						    ;Make free the storage that was used by scanf
pop	   rax						    ;Make free the storage that was used by scanf
pop	   rax						    ;Make free the storage that was used by scanf

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | pow1  pow2  pow3  pow4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|

;===== Calculate the current (amps) of each device ========================================================================================================================
;By someone else's law: Power (W) = Current (A) * Voltage (V). Therefore, A = W/V. Therefore we vector divide ymm14 by ymm15. 

vdivpd     ymm14, ymm15					    ;Vector divide each individual user inputted power (ymm14) by the user inputted voltage (ymm15)

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | cur1  cur2  cur3  cur4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|

;===== Output the thank you to the user and verification of completion of computation =====================================================================================
;Important data in top most registers, printf should NOT change this data. If it is corrupted, try backup at this point. 

mov  qword rax, 0                                           ;Zero indicates to printf that there is no data to grab from lower registers
mov    	   rdi, .stringformat                               ;"%s"
mov 	   rsi, thanks                                      ;"Thank you. The computations have completed with the following results."
call printf                                           	    ;An external function handles output

;===== Output the total circuit voltage inputted by user initially ========================================================================================================
;Relavant data for output in lowest register, will dumped after output. Top most registers should not be altered!! If they are, try a backup prior to this call.

movsd 	   xmm0, xmm15					    ;Move initial user input of total circuit voltage into xmm0 for use by printf
mov  qword rax, 1					    ;One indicates to printf that it will need to grab data from the first registers (xmm0)
mov 	   rdi, circuithead				    ;"Circuit total voltage: %1.18lf V"
call printf						    ;An external function that handles ouput

;===== Output the device number heading ===================================================================================================================================
;Important data in top most registers, printf should NOT change this data. If it is corrupted, try backup at this point. 

mov  qword rax, 0					    ;Zero indicates to printf that there is no data to grab from lower registers
mov 	   rdi, devicehead				    ;"Device number:		1				2...3...4"
call printf						    ;An external function that handles output

;===== Move the inputted power from stored area in higher registers to the integer stack, then spread out into individual lower registers for print =======================

push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:|  0.0 |
;          |------|
;   rsp+16:|  0.0 |
;          |------|
;   rsp+8: |  0.0 |
;          |------|
;   rsp:   |  0.0 | 
;          |------|

vmovupd    [rsp], ymm13					    ;Vector move the 2nd copy of the power input by user into the integer stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:| pow1 | = ymm13[255-192]
;          |------|
;   rsp+16:| pow2 | = ymm13[191-128]
;          |------|
;   rsp+8: | pow3 | = ymm13[127-64]
;          |------|
;   rsp:   | pow4 | = ymm13[63-0]
;          |------|

movsd      xmm0, [rsp+24]                                   ;Copy the power consumption of device 1 from integer stack[rsp+24] to xmm0[63-0]
movsd 	   xmm1, [rsp+16]                                   ;Copy the power consumption of device 2 from integer stack[rsp+16] to xmm1[63-0]
movsd 	   xmm2, [rsp+8]                                    ;Copy the power consumption of device 3 from integer stack[rsp+8] to xmm2[63-0]
movsd 	   xmm3, [rsp]                                      ;Copy the power consumption of device 4 from integer stack[rsp] to xmm3[63-0]

pop 	   rax						    ;Remove power consumption of device 4 (ymm13[63-0]) from integer stack
pop 	   rax						    ;Remove power consumption of device 3 (ymm13[127-64]) from integer stack
pop 	   rax						    ;Remove power consumption of device 2 (ymm13[191-128]) from integer stack
pop 	   rax						    ;Remove power consumption of device 1 (ymm13[255-192]) from integer stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp:   |rflags|
;          |------|

;===== Output the power consumption of each device input by the user ======================================================================================================
;Relevant data ready for output in lower registers, data will be dumped after display. Important data in top registers should not be altered.

mov  qword rax, 4					    ;4 will indicate to printf that there are 4 floating point numbers ready for use in registers
mov 	   rdi, powerout				    ;"Power (watts):	%1.18lf		%1.18lf		%1.18lf		%1.18lf"
call printf						    ;Extern function to print output

;===== Move the calculated current from stored area in higher registers to the integer stack, then spread out into individual lower registers for print ===================

push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack
push qword 0						    ;Reserve 8 bytes of storage for the incomming number on the stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:|  0.0 |
;          |------|
;   rsp+16:|  0.0 |
;          |------|
;   rsp+8: |  0.0 |
;          |------|
;   rsp:   |  0.0 | 
;          |------|

vmovupd    [rsp], ymm14					    ;Vector move the calculated current for each device onto the integer stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp+32:|rflags|
;          |------|
;   rsp+24:| cur1 | = ymm14[255-192]
;          |------|
;   rsp+16:| cur2 | = ymm14[191-128]
;          |------|
;   rsp+8: | cur3 | = ymm14[127-64]
;          |------|
;   rsp:   | cur4 | = ymm14[63-0]
;          |------|

movsd 	   xmm0, [rsp+24]                                   ;Copy the current of device 1 from integer stack[rsp+24] to xmm0[63-0]
movsd 	   xmm1, [rsp+16]                                   ;Copy the current of device 2 from integer stack[rsp+16] to xmm1[63-0]
movsd 	   xmm2, [rsp+8]                                    ;Copy the current of device 3 from integer stack[rsp+8] to xmm2[63-0]
movsd 	   xmm3, [rsp]                                      ;Copy the current of device 4 from integer stack[rsp] to xmm3[63-0]

pop 	   rax						    ;Remove current of device 4 (ymm14[63-0]) from integer stack
pop 	   rax						    ;Remove current of device 3 (ymm14[127-64]) from integer stack
pop 	   rax						    ;Remove current of device 2 (ymm14[191-128]) from integer stack
pop 	   rax						    ;Remove current of device 1 (ymm14[255-192]) from integer stack

;Integer stack as of last instruction:
;
;          |------|
;   rsp:   |rflags|
;          |------|

;===== Output the current calculations ====================================================================================================================================
;Relevant data in lower registers will be output, afterwards will be dumped

mov 	   rax, 4					    ;4 floating point numbers will be outputted to user (radius, surface area and volume)
mov 	   rdi, currentout				    ;"Current (amps):	%1.18lf		%1.18lf		%1.18lf		%1.18lf"
call printf						    ;Extern function to print output

;===== Calculate the total calculated current. Add horizontally across register, then split top half into lower register and add accordingly ==============================

vhaddpd    ymm12, ymm14, ymm14				    ;Vector horizontal add the calculated currents across register ymm14 and place in ymm12

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | cur1  cur2  cur3  cur4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|
;  ymm12: | cu12  cu12  cu34  cu34| (current 1+2) (current 1+2) (current 3+4) (current 3+4)
;         |-----------------------|

vextractf128 xmm0, ymm12, 1				    ;Vector extract the top half of ymm12 and place it in xmm0

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | cur1  cur2  cur3  cur4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|
;  ymm12: | cu12  cu12  cu34  cu34| (current 1+2) (current 1+2) (current 3+4) (current 3+4)
;         |-----------------------|
;  xmm0:  |   -    -    cu12  cu12| (current 1+2) (current 1+2)
;         |-----------------------|

addsd      xmm0, xmm12					    ;Add the values in xmm0 and xmm12 and place in xmm0 for calling by following printf function

;===== Output the total calculated current ================================================================================================================================
;Relevant data in register will be output and dumped. 

mov  qword rax, 1					    ;1 in rax indicates to printf to use one floating point value from the registers
mov 	   rdi, totalcurrent				    ;"Total current in the circuit is %1.18lf amps."
call printf						    ;Extern function to handle output

;===== Calculate the total power. Add horizontally across register, then split top half into lower register and add accordingly ===========================================

vhaddpd    ymm12, ymm13, ymm13				    ;Vector horizontal add the given power values across register ymm13 and place in ymm12

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | cur1  cur2  cur3  cur4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|
;  ymm12: | po12  po12  po34  po34| (power 1+2) (power 1+2) (power 3+4) (power 3+4)
;         |-----------------------|

vextractf128 xmm0, ymm12, 1				    ;Vector extract the top half of ymm12 and place it in xmm0

;AVX Registers as of last instruction:
;
;         |-----------------------|
;  ymm15: | volt  volt  volt  volt|
;         |-----------------------|
;  ymm14: | cur1  cur2  cur3  cur4|
;         |-----------------------|
;  ymm13: | pow1  pow2  pow3  pow4|
;         |-----------------------|
;  ymm12: | po12  po12  po34  po34| (power 1+2) (power 1+2) (power 3+4) (power 3+4)
;         |-----------------------|
;  xmm0:  |   -     -   po12  po12| (power 1+2) (power 1+2)
;         |-----------------------|

addsd      xmm0, xmm12					    ;Add the values in xmm0 and xmm12 and place in xmm0 for calling by following printf function

;Save a copy of the total power across all four devices to the integer stack before calling printf
push qword 0						    ;Reserve 8 bytes of storage on the stack for incomming power consumption
movsd 	   [rsp], xmm0					    ;Backup power consumption total to integer stack before printf

;===== Output the total power =============================================================================================================================================
;Important data that will be sent to driver has been backed up previously. It is safe to call printf.

push qword 0						    ;Out of bounds! Have to push a random value to the stack
mov  qword rax, 1					    ;1 value in rax indicates to printf that there is one value needed from the registers
mov 	   rdi, totalpower				    ;"Total power in the circuit is %1.18lf watts."
call 	   printf					    ;External function to handle output
pop 	   rax						    ;Reverse boundary push four instructions earlier.

;===== Say farewell =======================================================================================================================================================
;There is one data value on top of the stack that will be used soon, otherwise no need for further backups.

mov  qword rdi, .stringformat                               ;A little good-bye message will be outputted.
mov  qword rsi, farewell                                    ;"The analyzer program will now return the total power to the driver."
mov  qword rax, 0                                           ;Zero says that no data values from SSE registers are used by printf
call printf					   	    ;External function to handle output				

;===== Set the value to be returned to the caller =========================================================================================================================
;Presently the value to be returned to the caller is on the top of the system stack.  That value needs to be copied to xmm0 and removed from the stack.

movsd 	   xmm0, [rsp]					    ;A copy of total power consumption is now in xmm0
pop        rax                                              ;Remove the return value from the stack

pop        rbp                                              ;Restore the value rbp held when this function began execution

;Now the stack is in the same state as when the application area was entered.  It is safe to leave this application area.
;==========================================================================================================================================================================
;===== End of the application: Calculate the current in 4 devices given voltage and power consumption =====================================================================
;==========================================================================================================================================================================

ret                                                         ;Pop an 8-byte integer from the system stack and return to calling function
;===== End of program circuits ============================================================================================================================================
;========1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**

