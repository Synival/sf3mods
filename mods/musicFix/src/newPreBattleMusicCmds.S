# Runs F2 (75% volume) and F6 (pause) commands. Used before entering a 3D battle scene.
# Re-written in ASM from the original .DFR patch by Rika
.section .newPreBattleMusicCmds
.global _newPreBattleMusicCmds

_newPreBattleMusicCmds:
    sts.l      pr,@-r15
    mov.w      data_0x00f2,r4
    mov.l      func_queueMusicCommand,r0
    jsr        @r0
    nop
    mov.w      data_0x00f6,r4
    mov.l      func_queueMusicCommand,r0
    jsr        @r0
    nop
    lds.l      @r15+,pr
    rts
    nop

data_0x00f2:
    .word 0x00f2
data_0x00f6:
    .word 0x00f6
.balign 4
func_queueMusicCommand:
    .long _queueAudioCommand
