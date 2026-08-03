#if !(SCENARIO == 1)
#error Sorry, this only applies to Scenario 1.
#endif

// --------------------------------------------------------------------------------------------------------------------

// Function that replaces a block of code in the '0x1b' command function, which handles attacks.
// We need to add some code there, so it's been moved to some new part of memory and it jumps here instead.
.section .updatedRunAttackFrameLoop, "ax"
.global updatedRunAttackFrameLoop

// (New code below)
// Registers we're using.
    mov.l r12, @-r15
    mov.l r11, @-r15
// Volatile registers we can use that will need to be restored at the end of execution.
    mov.l r7, @-r15
    mov.l r6, @-r15
    mov.l r3, @-r15
    mov.l r2, @-r15
// Register that absolutely must be restored after our own code.
// (It's here at the end so it can be popped earlier.)
    mov.l r8, @-r15

// 1. push values other than r10 we now need to use to the stack
// 2. see if the attack is far range:
//   if so,  subtract 0xc
//   if not, subtract 0x14
// 3. make sure it's >= 0

// For later: get the number of frames in the attack and store it in r11.
    mov.l      addr_getAnimFrameCount0,r11
    mov        r12,r4 // attackerPolyChar
    mov        r14,r5 // attackerAnimId
    jsr        @r11
    mov        #0x6,r6 // ??? some magic animation thing
    mov        r0,r11
// For later: the address of g_moveCam2ToVictim
    mov.l      addr_g_moveCam2ToVictim,r12
// if (isFarAttackFromPolyCharAttacker())
    mov.l      addr_isFarAttackFromPolyCharAttacker,r10
    jsr        @r10
    nop
    tst        r0,r0
    bt         is_close_attack
is_far_attack:
    bra        frames_calculated
    add        #-0xc,r11
is_close_attack:
    add        #-0x14,r11
frames_calculated:
// Make sure r11 >= 0
    cmp/pz     r11
    bt         frames_are_greater_than_zero
    mov        #0,r11
frames_are_greater_than_zero:

// Restore register that must be intact before the original code.
    mov.l      @r15+,r8

// (Original code below: lifted from the '0x1b' command that runs attacks)
//   Registers written before reading (can ignore completely): r0, r1, r4, r5, r9, r10
//   Registers untouched (should pop at end):                  r2, r3, r6, r7, r11, r12, r13, r14
//   (r11 through r14 should be popped in a function call, but the others won't be.)
//   Registers read here (must be intact):                     r8
    mov.l      func_run_attack_frame,r10
    mov.l      func_wait_frames,r9
    mov        r8,r5

loop_start:
// (slightly rearranged...)
    mov        r15,r4
    jsr        @r10 /*run_attack_frame*/
    add        #24,r4 // we're adding 24 to r4 because we pushed some 6 ints onto the stack.
// (...done)
    tst        r0,r0
    bt         loop_end
    mov.l      var_g_intFuncResetColorsAndSpeedsPtr,r1 
    mov.l      @r1 /*g_intFuncResetColorsAndSpeedsPtr*/,r1
    add        #0x4,r1
    mov.w      @r1,r1
    tst        r1,r1
    bf         not_in_animation

in_animation:
// (new code)
// if (r8 == r11)
    cmp/eq     r8,r11
    bf         not_the_right_frame_yet
is_the_right_frame:
// Set g_moveCam2ToVictim to 1. This triggers attack cam2 to suddenly snap to a view with the victim + target.
    mov        #1,r11
    mov.b      r11,@r12
not_the_right_frame_yet:
// (end new code)
    add        #0x1,r8

not_in_animation:
    jsr        @r9 /*wait_frames*/
    mov        #0x1,r4
    bra        loop_start
    mov        r8,r5

loop_end:
// (New code below)
// Pop the registers we need to be absolutely certain are in the same state as before our injected code.
    mov.l      @r15+,r2
    mov.l      @r15+,r3
    mov.l      @r15+,r6
    mov.l      @r15+,r7
    mov.l      @r15+,r11
    mov.l      @r15+,r12
// Now we need to jump back exactly where we were.  r10's value (run_attack_frame() addr) is never used again, so we
// can safely steal it for our purposes.
    mov.l      addr_jump_back,r10
    jmp        @r10
    nop

.balign 4
func_run_attack_frame:
    .long 0x0608ffa4
func_wait_frames:
    .long 0x06011824
var_g_intFuncResetColorsAndSpeedsPtr:
    .long 0x0609ccb8
addr_jump_back:
    .long 0x0608aad4
addr_isFarAttackFromPolyCharAttacker:
    .long _isFarAttackFromPolyCharAttacker
addr_g_moveCam2ToVictim:
    .long _g_moveCam2ToVictim
addr_getAnimFrameCount0:
// TODO: Add this to x014.ld!
    .long 0x06095d6c

// --------------------------------------------------------------------------------------------------------------------

// We need to add some stuff to he end of the bcmd_0x1b.
.section .bcmd0x1bEndJump, "ax"
.global bcmd0x1bEndJump

    mov.l addr_updatedBCmd0x1bEnd,r0
    jmp @r0
    nop

.balign 4
addr_updatedBCmd0x1bEnd:
    .long .updatedBCmd0x1bEnd

// --------------------------------------------------------------------------------------------------------------------

.section .updatedBCmd0x1bEnd
.global updatedBCmd0x1bEnd

// new code
    mov.l     var_g_moveCam2ToAttacker,r0
    mov       #0x01,r1
    mov.b     r1,@r0

// original code
    add       #0x30,r15
    lds.l     @r15+,pr
    mov.l     @r15+,r14
    mov.l     @r15+,r13
    mov.l     @r15+,r12
    mov.l     @r15+,r11
    mov.l     @r15+,r10
    mov.l     @r15+,r9
    rts
    mov.l     @r15+,r8

.balign 4
var_g_moveCam2ToAttacker:
    .long _g_moveCam2ToAttacker
