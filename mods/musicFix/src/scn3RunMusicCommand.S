// Scenario 3's run music command function for placement into the PD
.section .scn3RunMusicCommand
.global _scn3RunMusicCommand

// Scenario 3's function starts right at the original spot.
// The Premium Disk starts a bit earlier, but enters the function in the original spot.
#if SCENARIO == 3
_scn3RunMusicCommand:
#elif SCENARIO == 4
top_of_memory:
#endif
    mov.l      r8,@-r15              // + 0x00
    mov.l      r9,@-r15
    mov.l      r10,@-r15
    mov.l      r11,@-r15
    mov.l      r12,@-r15
    mov.l      r13,@-r15
    sts.l      pr,@-r15
    add        #-0x4,r15
    mov.l      a_var_g_audioLock,r2  // +0x10
    mov.l      @r2,r1
    tst        r1,r1
    bt/s       label_0601295a
    mov        #0x0,r12
    bra        label_06012fa0
    nop
label_0601295a:
    movt       r0
    mov.l      r0,@r2                // +0x20
    mov.l      a_var_g_stopChannel1AndResumeChannel0Timer,r8
    mov.l      @r8,r1
    movt       r3
    tst        r1,r1
    bt         label_060129d6
    mov.l      a_var_g_isPlayingJingle,r10
    mov.l      @r10,r1
    tst        r1,r1                 // +0x30
    bt/s       label_06012992
    mov        #0x0,r9
    mov.l      @r8,r2
    mov.w      a_value_0x01a3,r1
    cmp/gt     r1,r2
    bt/s       label_06012992
    mov        r3,r5
    mov.l      a_func_unknownResumeFromPauseRelatedFunc,r1 // + 0x40

// On the PD, we need to insert code and jump over it when not entered directly.
#if SCENARIO == 4
    bra        skip_over_entry_point_target
    nop
    nop        // need some sort of a gap here for alignment

// On the PD, this is RAM address 0x0601293c, where the game expects this function to be.
_scn3RunMusicCommand:
    bra        top_of_memory
    nop

skip_over_entry_point_target:
#endif

    jsr        @r1
    mov        r15,r4
    mov.w      @r15,r1
    extu.w     r1,r1
    tst        r1,r1
    bf/s       label_06012990
    mov        #0x3,r1
    mov.l      r1,@r8
    mov.l      r12,@r10
label_06012990:
    mov.l      a_var_g_stopChannel1AndResumeChannel0Timer,r8
label_06012992:
    mov.l      @r8,r0
    cmp/eq     #0x5,r0
    bf         label_060129a0
    mov.l      a_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    movt       r4
    add        #0x1,r9
label_060129a0:
    mov.l      @r8,r0
    cmp/eq     #0x1,r0
    bf         label_060129c6
    mov.l      a_var_g_seqPlayingOnChannels,r10
    mov.l      @r10,r0
    cmp/eq     #-0x1,r0
    bt/s       label_060129ba
    mov        #-0x1,r1
    mov.l      a_func_soundCommand_PAUSE_OFF,r0
    jsr        @r0
    mov        #0x0,r4
    add        #0x1,r9
    mov        #-0x1,r1
label_060129ba:
    mov.l      r1,@(0x4,r10)
    mov        #0x0,r2
    mov.l      r2,@r8
    mov.l      a_var_g_isPaused,r1
    bra        label_060129ce
    mov.l      r2,@r1
label_060129c6:
    mov.l      @r8,r1
    add        #-0x1,r1
    mov.l      r1,@r8
    mov.l      @r8,r1
label_060129ce:
    tst        r9,r9
    bt         label_060129d6
    bra        done
    nop
label_060129d6:
    mov.l      a_var_g_sfxCmdBufferWritePos,r13
    mov.l      @r13,r1
    mov.l      a_var_g_sfxCmdBufferReadPos,r9
    mov.l      @r9,r2
    cmp/eq     r2,r1
    bf/s       label_060129e8
    mov        r2,r0
    bra        label_06012ae4
    nop
label_060129e8:
    shll2      r0
    mov.l      a_var_g_sfxCommands,r8
    mov.l      @(r0,r8),r2
    mov.w      a_value_0x01ff,r1
    cmp/gt     r1,r2
    bt/s       label_06012a34
    mov        r2,r0
    mov.l      a_func_soundCommand_PAUSE,r0
    jsr        @r0
    mov        #0x0,r4
    mov.l      a_func_soundCommand_SEQUENCE_VOLUME,r0
    mov        #0x0,r6
    mov        #0x69,r5
    jsr        @r0
    mov        #0x1,r4
    mov        #0x2,r7
    mov.l      @r9,r1
    mov        #0x1,r5
    mov        r1,r0
    shll2      r0
    mov.l      @(r0,r8),r6
    mov        #0x1,r4
    mov.l      a_func_soundCommand_SEQUENCE_START,r0
    jsr        @r0
    extu.b     r6,r6
    mov.l      a_var_g_stopChannel1AndResumeChannel0Timer,r2
    mov.w      a_value_0x01c2,r1
    mov.l      r1,@r2
    mov.l      a_var_g_isPlayingJingle,r2
    mov        #0x1,r1
    mov.l      r1,@r2
    mov.l      @r9,r1
    mov        r1,r0
    shll2      r0
    mov.l      @(r0,r8),r1
    mov.l      a_var_g_seqPlayingOnChannels,r2
    bra        label_06012a96
    mov.l      r1,@(0x4,r2)
label_06012a34:
    mov.l      a_var_g_sfxChannelsMinus0x200,r1
    mov.b      @(r0,r1),r8
    mov        #0x7,r1
    cmp/gt     r1,r8
    bf         label_06012a50
    mov.l      a_var_g_nextSfxPControl,r2
    mov.l      @r2,r8
    mov        r8,r0
    add        #0x1,r0
    cmp/eq     #0x8,r0
    bf/s       label_06012a50
    mov.l      r0,@r2
    mov        #0x5,r1
    mov.l      r1,@r2
label_06012a50:
    mov.l      a_var_g_sfxCmdBufferReadPos,r1
    mov.l      @r1,r1
    mov        r1,r2
    shll2      r2
    mov.l      a_var_g_sfxCommands,r1
    mov        r2,r0
    mov.l      @(r0,r1),r2
    mov.w      a_value_0xfe00,r1
    mov        r8,r0
    cmp/eq     #0x2,r0
    bf/s       label_06012a72
    add        r1,r2
    extu.b     r2,r6
    extu.b     r8,r4
    mov.l      a_func_soundCommand_SEQUENCE_START,r0
    bra        label_06012a7a
    mov        #0x2,r7
label_06012a72:
    extu.b     r2,r6
    extu.b     r8,r4
    mov.l      a_func_soundCommand_SEQUENCE_START,r0
    mov        #0x1,r7
label_06012a7a:
    jsr        @r0
    mov        #0x0,r5
    mov        r8,r7
    mov.l      a_var_g_sfxCmdBufferReadPos,r1
    mov.l      @r1,r1
    shll2      r7
    mov        r1,r3
    shll2      r3
    mov.l      a_var_g_sfxCommands,r1
    mov        r3,r0
    mov.l      @(r0,r1),r1
    mov.l      a_var_g_seqPlayingOnChannels,r2
    mov        r7,r0
    mov.l      r1,@(r0,r2)
label_06012a96:
    mov.l      a_var_g_sfxCmdBufferReadPos,r2
    bra        label_06012f92
    mov.l      @r2,r1

a_value_0x01a3:
    .short 0x01a3
a_value_0x01ff:
    .short 0x01ff
a_value_0x01c2:
    .short 0x01c2
a_value_0xfe00:
    .short 0xfe00
.balign 4
a_var_g_audioLock:
    .long _g_audioLock
a_var_g_stopChannel1AndResumeChannel0Timer:
    .long _g_stopChannel1AndResumeChannel0Timer
a_var_g_isPlayingJingle:
    .long _g_isPlayingJingle
a_func_unknownResumeFromPauseRelatedFunc:
    .long _unknownResumeFromPauseRelatedFunc
a_func_soundCommand_SEQUENCE_STOP:
    .long _soundCommand_SEQUENCE_STOP
a_var_g_seqPlayingOnChannels:
    .long _g_seqPlayingOnChannels
a_func_soundCommand_PAUSE_OFF:
    .long _soundCommand_PAUSE_OFF
a_var_g_isPaused:
    .long _g_isPaused
a_var_g_sfxCmdBufferWritePos:
    .long _g_sfxCmdBufferWritePos
a_var_g_sfxCmdBufferReadPos:
    .long _g_sfxCmdBufferReadPos
a_var_g_sfxCommands:
    .long _g_sfxCommands
a_func_soundCommand_PAUSE:
    .long _soundCommand_PAUSE
a_func_soundCommand_SEQUENCE_VOLUME:
    .long _soundCommand_SEQUENCE_VOLUME
a_func_soundCommand_SEQUENCE_START:
    .long _soundCommand_SEQUENCE_START
a_var_g_sfxChannelsMinus0x200:
    .long _g_sfxChannels - 0x200
a_var_g_nextSfxPControl:
    .long _g_nextSfxPControl

label_06012ae4:
    mov.l      b_var_g_musicCmdBufferWritePos,r11
    mov.l      @r11,r1
    mov.l      b_var_g_musicCmdBufferReadPos,r10
    mov.l      @r10,r2
    cmp/eq     r2,r1
    bf/s       label_06012af6
    mov        r2,r0
    bra        done
    nop
label_06012af6:
    shll2      r0
    mov.l      b_var_g_musicCommands,r1
    mov.l      @(r0,r1),r8
    mov.w      b_value_0x00f7,r1
    cmp/eq     r1,r8
    bf/s       label_06012b08
    cmp/gt     r1,r8
    bra        label_06012dd2
    nop
label_06012b08:
    bt         label_06012b60
    mov.w      b_value_0x00f2,r1
    cmp/eq     r1,r8
    bf/s       label_06012b16
    cmp/gt     r1,r8
    bra        label_06012cec
    nop
label_06012b16:
    bt         label_06012b36
    mov.w      b_value_0x00f0,r1
    cmp/eq     r1,r8
    bf         label_06012b22
    bra        label_06012cd2
    nop
label_06012b22:
    cmp/gt     r1,r8
    bf/s       label_06012b2c
    tst        r8,r8
    bra        label_06012ce4
    nop
label_06012b2c:
    bf         label_06012b32
    bra        label_06012d90
    nop
label_06012b32:
    bra        start_loading_musicCmd_as_track
    nop
label_06012b36:
    mov.w      b_value_0x00f4,r1
    cmp/eq     r1,r8
    bf/s       label_06012b42
    cmp/ge     r1,r8
    bra        label_06012c6a
    nop
label_06012b42:
    bt/s       label_06012b4a
    mov        #0x1,r6
    bra        label_06012d12
    nop
label_06012b4a:
    mov.w      b_value_0x00f5,r1
    cmp/eq     r1,r8
    bt/s       label_06012c04
    mov        #-0x80,r2
    mov.w      b_value_0x00f6,r1
    cmp/eq     r1,r8
    bf         label_06012b5c
    bra        label_06012db6
    nop
label_06012b5c:
    bra        start_loading_musicCmd_as_track
    nop
label_06012b60:
    mov.w      b_value_0x00fb,r1
    cmp/eq     r1,r8
    bf/s       label_06012b6c
    cmp/gt     r1,r8
    bra        label_06012d22
    nop
label_06012b6c:
    bt         label_06012b84
    mov.w      b_value_0x00f9,r1
    cmp/eq     r1,r8
    bf/s       label_06012b7a
    cmp/gt     r1,r8
    bra        label_06012dfc
    nop
label_06012b7a:
    bf         label_06012b80
    bra        label_06012dac
    nop
label_06012b80:
    bra        move_to_next_music_command_and_finish
    nop
label_06012b84:
    mov.w      b_value_0x00fd,r1
    cmp/eq     r1,r8
    bf/s       label_06012b90
    cmp/ge     r1,r8
    bra        label_06012d36
    nop
label_06012b90:
    bt         label_06012b96
    bra        label_06012d2c
    nop
label_06012b96:
    mov.w      b_value_0x00fe,r1
    cmp/eq     r1,r8
    bf         label_06012ba0
    bra        label_06012d4c
    nop
label_06012ba0:
    mov.w      b_value_0x00ff,r1
    cmp/eq     r1,r8
    bt         label_06012baa
    bra        start_loading_musicCmd_as_track
    nop
label_06012baa:
    mov.l      b_func_soundCommand_SOUND_INITIALIZE_initDSP,r0
    jsr        @r0
    mov        #0x0,r8
    mov.l      b_func_soundCommand_SOUND_INITIALIZE_stopSequences,r0
    jsr        @r0
    nop
    mov        #0x0,r1
    mov.l      r1,@r9
    mov.l      r1,@r13
    mov.l      r1,@r10
    mov.l      r1,@r11
    mov        #0x7,r3
    mov        #-0x1,r2
    mov.l      b_var_g_seqPlayingOnChannels,r1
label_06012bc6:
    mov.l      r2,@r1
    add        #0x1,r8
    cmp/gt     r3,r8
    bf/s       label_06012bc6
    add        #0x4,r1
    bra        move_to_next_music_command_and_finish
    nop

b_value_0x00f7:
    .short 0x00f7
b_value_0x00f2:
    .short 0x00f2
b_value_0x00f0:
    .short 0x00f0
b_value_0x00f4:
    .short 0x00f4
b_value_0x00f5:
    .short 0x00f5
b_value_0x00f6:
    .short 0x00f6
b_value_0x00fb:
    .short 0x00fb
b_value_0x00f9:
    .short 0x00f9
b_value_0x00fd:
    .short 0x00fd
b_value_0x00fe:
    .short 0x00fe
b_value_0x00ff:
    .short 0x00ff
.balign 4
b_var_g_musicCmdBufferWritePos:
    .long _g_musicCmdBufferWritePos
b_var_g_musicCmdBufferReadPos:
    .long _g_musicCmdBufferReadPos
b_var_g_musicCommands:
    .long _g_musicCommands
b_func_soundCommand_SOUND_INITIALIZE_initDSP:
    .long _soundCommand_SOUND_INITIALIZE_initDSP
b_func_soundCommand_SOUND_INITIALIZE_stopSequences:
    .long _soundCommand_SOUND_INITIALIZE_stopSequences
b_var_g_seqPlayingOnChannels:
    .long _g_seqPlayingOnChannels

label_06012c04:
    mov.l      c_var_g_unknownAudioThing,r1
    mov.l      @r1,r1
    add        #0x3,r1
    mov.b      r2,@r1
    mov.l      c_addr_20100063,r1
label_06012c0e:
    mov.b      @r1,r0
    and        #0x1,r0
    tst        r0,r0
    bf         label_06012c0e
    mov        #0x1,r1
    mov.l      c_addr_20100063,r6
    mov.b      r1,@r6
    mov.l      c_addr_20100001,r2
    mov.l      c_addr_06004f10,r1
    mov.l      @r1,r7
    mov.l      @(0x10,r7),r1
    shlr16     r1
    shlr8      r1
    mov.b      r1,@r2
    mov.l      c_addr_20100003,r3
    mov.l      @(0x10,r7),r1
    mov.w      c_value_0x0200,r2
    shlr16     r1
    mov.b      r1,@r3
    mov.l      c_addr_20100005,r3
    mov.l      @(0x10,r7),r1
    or         r2,r1
    shlr8      r1
    mov.b      r1,@r3
    mov.l      c_addr_20100007,r3
    mov.l      @(0x10,r7),r1
    or         r2,r1
    mov.b      r1,@r3
    mov.l      c_addr_2010001f,r2
    mov        #0x17,r1
    mov.b      r1,@r2
    mov.b      @r6,r0
    and        #0x1,r0
    tst        r0,r0
    bf/s       label_06012c5a
    mov        r6,r1
    bra        move_to_next_music_command_and_finish
    nop
label_06012c5a:
    mov.b      @r1,r0
    and        #0x1,r0
    tst        r0,r0
    bf         label_06012c66
    bra        move_to_next_music_command_and_finish
    nop
label_06012c66:
    bra        label_06012c5a
    nop
label_06012c6a:
    mov.l      c_var_g_unknownAudioThing,r1
    mov.l      @r1,r1
    mov        #0x0,r2
    add        #0x3,r1
    mov.b      r2,@r1
    mov.l      c_addr_20100063,r1
label_06012c76:
    mov.b      @r1,r0
    and        #0x1,r0
    tst        r0,r0
    bf         label_06012c76
    mov        #0x1,r1
    mov.l      c_addr_20100063,r6
    mov.b      r1,@r6
    mov.l      c_addr_20100001,r2
    mov.l      c_addr_06004f10,r1
    mov.l      @r1,r7
    mov.l      @(0x10,r7),r1
    shlr16     r1
    shlr8      r1
    mov.b      r1,@r2
    mov.l      c_addr_20100003,r3
    mov.l      @(0x10,r7),r1
    mov.w      c_value_0xfdff,r2
    shlr16     r1
    mov.b      r1,@r3
    mov.l      c_addr_20100005,r3
    mov.l      @(0x10,r7),r1
    and        r2,r1
    shlr8      r1
    mov.b      r1,@r3
    mov.l      c_addr_20100007,r3
    mov.l      @(0x10,r7),r1
    and        r2,r1
    mov.b      r1,@r3
    mov.l      c_addr_2010001f,r2
    mov        #0x17,r1
    mov.b      r1,@r2
    mov.b      @r6,r0
    and        #0x1,r0
    tst        r0,r0
    bf/s       label_06012cc2
    mov        r6,r1
    bra        move_to_next_music_command_and_finish
    nop
label_06012cc2:
    mov.b      @r1,r0
    and        #0x1,r0
    tst        r0,r0
    bf         label_06012cce
    bra        move_to_next_music_command_and_finish
    nop
label_06012cce:
    bra        label_06012cc2
    nop
label_06012cd2:
    mov.l      c_func_soundCommand_SEQUENCE_VOLUME,r0
    movt       r6
    mov        #0x0,r5
    jsr        @r0
    mov        #0x0,r4
    mov.l      c_var_g_seqPlayingOnChannels,r2
    mov        #-0x1,r1
    bra        move_to_next_music_command_and_finish
    mov.l      r1,@r2
label_06012ce4:
    mov.l      c_var_g_setToTwoToFadeInNextTrack,r2
    mov        #0x2,r1
    bra        move_to_next_music_command_and_finish
    mov.l      r1,@r2
label_06012cec:
    mov.l      c_var_g_trackNormalVolume,r1
    mov.l      @r1,r2
    mov        r2,r1
    add        r1,r1
    add        r2,r1
    cmp/pz     r1
    bt         label_06012cfc
    add        #0x3,r1
label_06012cfc:
    mov        r1,r0
    shlr2      r0
    mov.w      c_value_0x00ff,r1
    and        r0,r1
    mov.l      c_func_soundCommand_SEQUENCE_VOLUME,r0
    mov        #0x1,r6
    mov        r1,r5
    jsr        @r0
    mov        #0x0,r4
    bra        move_to_next_music_command_and_finish
    nop
label_06012d12:
    mov.l      c_var_g_trackNormalVolume,r1
    mov.l      @r1,r5
    mov.l      c_func_soundCommand_SEQUENCE_VOLUME,r0
    mov        #0x0,r4
    jsr        @r0
    extu.b     r5,r5
    bra        move_to_next_music_command_and_finish
    nop
label_06012d22:
    mov.l      c_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    mov        #0x2,r4
    bra        move_to_next_music_command_and_finish
    nop
label_06012d2c:
    mov.l      c_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    mov        #0x3,r4
    bra        move_to_next_music_command_and_finish
    nop
label_06012d36:
    mov.l      c_func_soundCommand_SEQUENCE_STOP,r8
    jsr        @r8
    mov        #0x4,r4
    jsr        @r8
    mov        #0x5,r4
    jsr        @r8
    mov        #0x6,r4
    jsr        @r8
    mov        #0x7,r4
    bra        move_to_next_music_command_and_finish
    nop
label_06012d4c:
    mov.l      c_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    movt       r4
    bra        move_to_next_music_command_and_finish
    nop

c_value_0x0200:
    .short 0x0200
c_value_0xfdff:
    .short 0xfdff
c_value_0x00ff:
    .short 0x00ff
.balign 4
c_var_g_unknownAudioThing:
    .long _g_unknownAudioThing
c_addr_20100063:
    .long 0x20100063           // undefined4 20100063h
c_addr_20100001:
    .long 0x20100001           // undefined4 20100001h
c_addr_06004f10:
    .long _DAT_06004f10
c_addr_20100003:
    .long 0x20100003           // undefined4 20100003h
c_addr_20100005:
    .long 0x20100005           // undefined4 20100005h
c_addr_20100007:
    .long 0x20100007           // undefined4 20100007h
c_addr_2010001f:
    .long 0x2010001f           // undefined4 2010001Fh
c_func_soundCommand_SEQUENCE_VOLUME:
    .long _soundCommand_SEQUENCE_VOLUME
c_var_g_seqPlayingOnChannels:
    .long _g_seqPlayingOnChannels
c_var_g_setToTwoToFadeInNextTrack:
    .long _g_setToTwoToFadeInNextTrack
c_var_g_trackNormalVolume:
    .long _g_trackNormalVolume
c_func_soundCommand_SEQUENCE_STOP:
    .long _soundCommand_SEQUENCE_STOP

label_06012d90:
    mov        #0x0,r8
    mov.l      d_func_soundCommand_SEQUENCE_STOP,r10
    mov.l      d_var_g_seqPlayingOnChannels,r9
label_06012d96:
    jsr        @r10
    extu.b     r8,r4
    mov        #-0x1,r1
    mov.l      r1,@r9
    add        #0x1,r8
    mov        #0x1,r1
    cmp/gt     r1,r8
    bf/s       label_06012d96
    add        #0x4,r9
    bra        move_to_next_music_command_and_finish
    nop
label_06012dac:
    mov.l      d_var_g_seqPlayingOnChannels,r2
    mov.l      @r2,r2
    mov.l      d_var_g_rememberedTrack,r1
    bra        move_to_next_music_command_and_finish
    mov.l      r2,@r1
label_06012db6:
    mov.l      d_var_g_isPaused,r8
    mov.l      @r8,r1
    tst        r1,r1

#if USE_UNCHANGED_SCN3_RUN_MUSIC_COMMAND_BEHAVIOR
// Original code.
    bt/s       label_06012dc4
    mov        #0x0,r6
    bra        move_to_next_music_command_and_finish
    nop
label_06012dc4:
    mov.l      d_func_soundCommand_SEQUENCE_VOLUME,r0
    movt       r5
    jsr        @r0
    mov        #0x0,r4
    mov        #0x1,r1
    bra        move_to_next_music_command_and_finish
    mov.l      r1,@r8

#else
// Modified code for fix.

// Do nothing if already paused.
    bt         perform_pause
    bra        move_to_next_music_command_and_finish
// Run PAUSE command.
perform_pause:
    mov.l      z_func_soundCommand_PAUSE,r0
    jsr        @r0
    mov        #0,r4
// Set g_isPaused to 1 and finish.
    mov        #1,r0
    bra        move_to_next_music_command_and_finish
    mov.l      r0,@r8

// Data.
.balign 4
z_func_soundCommand_PAUSE:
    .long _soundCommand_PAUSE

// (need some junk to also be exactly 22 bytes)
    .word 0x0000

#endif

label_06012dd2:
    mov.l      d_var_g_isPaused,r1
    mov.l      @r1,r0
    cmp/eq     #0x1,r0
    bf/s       label_06012dfc
    movt       r6
    mov.l      d_func_soundCommand_SEQUENCE_VOLUME,r0
    mov        #0x0,r5
    jsr        @r0
    movt       r4
    mov.l      d_var_g_stopChannel1AndResumeChannel0Timer,r2
#if USE_UNCHANGED_SCN3_RUN_MUSIC_COMMAND_BEHAVIOR
    mov        #0x1e,r1
#else
    mov        #0x19,r1
#endif
    mov.l      r1,@r2
    mov.l      d_var_g_isPlayingJingle,r2
    mov        #0x0,r1
    bra        move_to_next_music_command_and_finish
    mov.l      r1,@r2
label_06012df2:
    mov        r2,r1
    add        #0x2,r1
    mov.w      @r1,r12
    bra        track_not_present_in_this_seqTonId_segment
    mov        r3,r10
label_06012dfc:
    mov.l      d_var_g_rememberedTrack,r1
    mov.l      @r1,r8
start_loading_musicCmd_as_track:
    mov.l      d_var_g_trackAndSeqDatasBySeqTonId,r2
    mov.w      d_value_0x03e7,r10
    mov.l      d_var_g_currentSeqLoadedInBank3,r7
load_next_seqId_segment:
    mov.w      @r2+,r3
label_06012e08:
    mov        r3,r0
    cmp/eq     #-0x1,r0
    bt/s       track_not_present_in_this_seqTonId_segment
    tst        r3,r3
    bt         label_06012e18
    mov.l      @r7,r1
    cmp/eq     r1,r3
    bf         label_06012e2a
label_06012e18:
    mov.w      @r2,r1
track_already_loaded_here_in_this_seqTonId_segment:
    mov        r1,r0
    cmp/eq     #-0x1,r0
    bt/s       ffff_in_seqTonId_segment
    cmp/eq     r8,r1
    bt         label_06012df2
    add        #0x4,r2
    bra        track_already_loaded_here_in_this_seqTonId_segment
    mov.w      @r2,r1
label_06012e2a:
    mov.w      @r2+,r0
    cmp/eq     #-0x1,r0
    bt         load_next_seqId_segment
label_06012e30:
    mov.w      @r2+,r0
    cmp/eq     #-0x1,r0
    bf         label_06012e30
    mov.w      @r2+,r3
    bra        label_06012e08
    nop
ffff_in_seqTonId_segment:
    bra        load_next_seqId_segment
    add        #0x2,r2
track_not_present_in_this_seqTonId_segment:
    mov.w      d_value_0x03e7,r1
    cmp/eq     r1,r10
    bf/s       seqTonIdToLoad_found
    tst        r10,r10
    mov        #0x0,r10
    mov        #0x0,r12
    mov.l      d_var_g_trackAndSeqDatasBySeqTonId,r2
label_06012e4e:
    mov.w      @r2+,r3
    mov        r3,r0
    cmp/eq     #-0x1,r0
    bt/s       seqTonIdToLoad_found
    tst        r10,r10
    mov.w      @r2,r1
not_loaded_loop_keep_looking_for_trackId:
    mov        r1,r0
    cmp/eq     #-0x1,r0
    bf/s       label_06012e66
    cmp/eq     r8,r1
    bra        label_06012e4e
    add        #0x2,r2
label_06012e66:
    bt         label_06012e6e
    add        #0x4,r2
    bra        not_loaded_loop_keep_looking_for_trackId
    mov.w      @r2,r1
label_06012e6e:
    mov        r3,r10
    mov        r2,r1
    add        #0x2,r1
    mov.w      @r1,r12
label_06012e76:
    tst        r10,r10
seqTonIdToLoad_found:
    bf/s       label_06012e7e
    mov        #0x3,r11
    mov        #0x2,r11
label_06012e7e:
    mov.l      d_var_g_isPaused,r2
    mov.l      @r2,r1
    tst        r1,r1
    bt/s       label_06012ef4
    tst        r10,r10
    bt         label_06012e98
    mov.l      d_var_g_currentSeqLoadedInBank3,r1
    mov.l      @r1,r1
    cmp/eq     r10,r1
    bt/s       label_06012e98
    mov        #0x0,r1
    bra        label_06012e76
    mov.l      r1,@r2
label_06012e98:
    mov.l      d_var_g_seqPlayingOnChannels_1,r9
    mov.l      @r9,r1
    cmp/eq     r8,r1
    bt/s       move_to_next_music_command_and_finish
    mov        r8,r0
    mov.l      d_var_g_trackVolumes,r1
    mov.b      @(r0,r1),r5
    mov        #0x0,r6
    mov        #0x1,r4
    mov.l      d_func_soundCommand_SEQUENCE_VOLUME,r0
    jsr        @r0
    extu.b     r5,r5
    extu.b     r12,r6
    extu.b     r11,r5
    mov        #0x2,r7
    mov.l      d_func_soundCommand_SEQUENCE_START,r0
    jsr        @r0
    mov        #0x1,r4
    bra        move_to_next_music_command_and_finish
    mov.l      r8,@r9

d_value_0x03e7:
    .short 0x03e7
.balign 4
d_func_soundCommand_SEQUENCE_STOP:
    .long _soundCommand_SEQUENCE_STOP
d_var_g_seqPlayingOnChannels:
    .long _g_seqPlayingOnChannels
d_var_g_rememberedTrack:
    .long _g_rememberedTrack
d_var_g_isPaused:
    .long _g_isPaused
d_func_soundCommand_SEQUENCE_VOLUME:
    .long _soundCommand_SEQUENCE_VOLUME
d_var_g_stopChannel1AndResumeChannel0Timer:
    .long _g_stopChannel1AndResumeChannel0Timer
d_var_g_isPlayingJingle:
    .long _g_isPlayingJingle
d_var_g_trackAndSeqDatasBySeqTonId:
    .long _g_trackAndSeqDatasBySeqTonId
d_var_g_currentSeqLoadedInBank3:
    .long _g_currentSeqLoadedInBank3
d_var_g_seqPlayingOnChannels_1:
    .long _g_seqPlayingOnChannels + 0x04
d_var_g_trackVolumes:
    .long _g_trackVolumes
d_func_soundCommand_SEQUENCE_START:
    .long _soundCommand_SEQUENCE_START

label_06012ef4:
    mov.l      e_var_g_seqPlayingOnChannels,r1
    mov.l      @r1,r1
    cmp/eq     r8,r1
    bt/s       move_to_next_music_command_and_finish
    mov        r8,r0
    mov.l      e_var_g_loadSequenceMode,r2
    mov.l      e_var_g_setToTwoToFadeInNextTrack,r3
    mov.l      @r3,r1
    mov.l      r1,@r2
    mov.l      e_var_g_trackVolumes,r1
    mov.b      @(r0,r1),r1
    mov.l      e_var_g_trackNormalVolume,r2
    mov.l      r1,@r2
    mov        #0x1,r1
    mov.l      r1,@r3
    mov        r10,r1
    shll2      r1
    add        r1,r1
    mov.l      e_var_g_seqFileIdAndTonIds,r2
    add        r2,r1
    mov.l      @(0x4,r1),r9
    mov.l      e_var_g_currentTonId,r13
    mov.l      @r13,r1
    cmp/eq     r9,r1
    bt/s       label_06012f48
    mov        r9,r0
    cmp/eq     #0x63,r0
    bt/s       label_06012f4a
    tst        r10,r10
    mov.l      e_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    mov        #0x0,r4
    mov.l      e_func_onLoadTonFile,r6
    mov.l      e_var_g_scsp_unknown1,r5
    mov        r9,r0
    shll2      r0
    mov.l      e_var_g_tonFileIds,r1
    mov.l      @(r0,r1),r4
    mov.l      e_func_loadFileToAddrWithCallback,r0
    jsr        @r0
    mov        #0x0,r7
    mov.l      r9,@r13
label_06012f48:
    tst        r10,r10
label_06012f4a:
    bt/s       label_06012f7e
    mov        r11,r1
    mov.l      e_var_g_currentSeqLoadedInBank3,r9
    mov.l      @r9,r1
    cmp/eq     r10,r1
    bt/s       label_06012f7e
    mov        r11,r1
    mov.l      e_func_soundCommand_SEQUENCE_STOP,r0
    jsr        @r0
    mov        #0x0,r4
    mov        r11,r1
    shll16     r1
    mov        r12,r7
    or         r1,r7
    mov.l      e_func_onSequenceLoaded,r6
    mov        r10,r0
    shll2      r0
    add        r0,r0
    mov.l      e_var_g_seqFileIdAndTonIds,r1
    mov.l      @(r0,r1),r4
    mov.l      e_var_g_scsp_unknown2,r5
    mov.l      e_func_loadFileToAddrWithCallback,r0
    jsr        @r0
    nop
    bra        label_06012f8a
    mov.l      r10,@r9
label_06012f7e:
    shll16     r1
    mov        r12,r4
    or         r1,r4
    mov.l      e_func_onSequenceLoaded,r1
    jsr        @r1
    nop
label_06012f8a:
    mov.l      e_var_g_seqPlayingOnChannels,r1
    mov.l      r8,@r1
move_to_next_music_command_and_finish:
    mov.l      e_var_g_musicCmdBufferReadPos,r2
    mov.l      @r2,r1
label_06012f92:
    mov        r1,r0
    add        #0x1,r0
    and        #0x7,r0
    mov.l      r0,@r2
done:
    mov.l      e_var_g_audioLock,r2
    mov        #0x0,r1
    mov.l      r1,@r2
label_06012fa0:
    add        #0x4,r15
    lds.l      @r15+,pr
    mov.l      @r15+,r13
    mov.l      @r15+,r12
    mov.l      @r15+,r11
    mov.l      @r15+,r10
    mov.l      @r15+,r9
    rts
    mov.l      @r15+,r8

.balign 4
e_var_g_seqPlayingOnChannels:
    .long _g_seqPlayingOnChannels
e_var_g_loadSequenceMode:
    .long _g_loadSequenceMode
e_var_g_setToTwoToFadeInNextTrack:
    .long _g_setToTwoToFadeInNextTrack
e_var_g_trackVolumes:
    .long _g_trackVolumes
e_var_g_trackNormalVolume:
    .long _g_trackNormalVolume
e_var_g_seqFileIdAndTonIds:
    .long _g_seqFileIdAndTonIds
e_var_g_currentTonId:
    .long _g_currentTonId
e_func_soundCommand_SEQUENCE_STOP:
    .long _soundCommand_SEQUENCE_STOP
e_func_onLoadTonFile:
    .long _onLoadTonFile
e_var_g_scsp_unknown1:
    .long 0x25a70800           // undefined4 25A70800h
e_var_g_tonFileIds:
    .long _g_tonFileIds
e_func_loadFileToAddrWithCallback:
    .long _loadFileToAddrWithCallback
e_var_g_currentSeqLoadedInBank3:
    .long _g_currentSeqLoadedInBank3
e_func_onSequenceLoaded:
    .long _onSequenceLoaded
e_var_g_scsp_unknown2:
    .long 0x25a6a800           // undefined4 25A6A800h
e_var_g_musicCmdBufferReadPos:
    .long _g_musicCmdBufferReadPos
e_var_g_audioLock:
    .long _g_audioLock
