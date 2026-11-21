/* 1ST.BIN */

_writeDebugStr                                  = 0x0600d298;
_writeDebugUIntWithoutZeroes                    = 0x0600d2b4;
_hexToDec                                       = 0x0600e8b0;
_waitFrames                                     = 0x060111c0;
_loadFileToAddrWithCallback                     = 0x0601249c;
_onSequenceLoaded                               = 0x06012814;
_onLoadTonFile                                  = 0x060128b4;
_queueAudioCommand                              = 0x060128e8;
_runMusicCommand                                = 0x0601293c;
_getDebugTextCoords                             = 0x06013c7c;
_maybeSomeDspSetup                              = 0x06015018;
_soundCommand_SOUND_INITIALIZE_initDSP          = 0x06017a48;
_soundCommand_SOUND_INITIALIZE_stopSequences    = 0x06017af8;
_soundCommand_SEQUENCE_START                    = 0x06017ba8;
_soundCommand_SEQUENCE_STOP                     = 0x06017ca8;
_soundCommand_PAUSE                             = 0x06017d34;
_soundCommand_PAUSE_OFF                         = 0x06017dc0;
_soundCommand_SEQUENCE_VOLUME                   = 0x06017e4c;
_unknownResumeFromPauseRelatedFunc              = 0x060189c0;
_divSigned                                      = 0x06020e14;

_g_buttonsDown                                  = 0x060214ac;
_g_bufferedButtonsDown                          = 0x060214ae;
_g_seqFileIdAndTonIds                           = 0x06021558;
_g_tonFileIds                                   = 0x06021650;
_g_trackAndSeqDatasBySeqTonId                   = 0x06021680;
_g_trackVolumes                                 = 0x0602182c;
_g_sfxChannels                                  = 0x06021874;
_g_rememberedTrack                              = 0x0602190c;
_g_isPaused                                     = 0x06021910;
_g_nextSfxPControl                              = 0x06021918;
_g_loadSequenceMode                             = 0x06023848;
_g_trackNormalVolume                            = 0x0602384c;
_g_seqPlayingOnChannels                         = 0x06023850;
_g_musicCmdBufferReadPos                        = 0x06023870;
_g_musicCmdBufferWritePos                       = 0x06023874;
_g_sfxCmdBufferReadPos                          = 0x06023878;
_g_sfxCmdBufferWritePos                         = 0x0602387c;
_g_musicCommands                                = 0x06023880;
_g_sfxCommands                                  = 0x060238a0;
_g_setToTwoToFadeInNextTrack                    = 0x060238c0;
_g_audioLock                                    = 0x060238c4;
_g_isPlayingJingle                              = 0x060238c8;
_g_currentTonId                                 = 0x06028314;
_g_stopChannel1AndResumeChannel0Timer           = 0x06028318;
_g_currentSeqLoadedInBank3                      = 0x0602831c;

/* TODO: What is this??? Some kind of struct? */
_DAT_06004f10                                   = 0x06004f10;
/* TODO: What is this??? */
_g_unknownAudioThing                            = 0x06029d84;

