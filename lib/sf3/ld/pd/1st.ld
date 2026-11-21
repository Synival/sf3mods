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
_getDebugTextCoords                             = 0x06013c50;
_maybeSomeDspSetup                              = 0x06014fec;
_soundCommand_SOUND_INITIALIZE_initDSP          = 0x06017a1c;
_soundCommand_SOUND_INITIALIZE_stopSequences    = 0x06017acc;
_soundCommand_SEQUENCE_START                    = 0x06017b7c;
_soundCommand_SEQUENCE_STOP                     = 0x06017c7c;
_soundCommand_PAUSE                             = 0x06017d08;
_soundCommand_PAUSE_OFF                         = 0x06017d94;
_soundCommand_SEQUENCE_VOLUME                   = 0x06017e20;
_unknownResumeFromPauseRelatedFunc              = 0x06018994;
_divSigned                                      = 0x06020de8;

_g_buttonsDown                                  = 0x06021480;
_g_bufferedButtonsDown                          = 0x06021482;
_g_seqFileIdAndTonIds                           = 0x0602152c;
_g_tonFileIds                                   = 0x06021624;
_g_trackAndSeqDatasBySeqTonId                   = 0x06021654;
_g_trackVolumes                                 = 0x060217fc;
_g_sfxChannels                                  = 0x06021844;
_g_rememberedTrack                              = 0x060218dc;
_g_isPaused                                     = 0x060218e0;
_g_nextSfxPControl                              = 0x060218e8;
_g_loadSequenceMode                             = 0x06023818;
_g_trackNormalVolume                            = 0x0602381c;
_g_seqPlayingOnChannels                         = 0x06023820;
_g_seqPlayingOnChannels_1                       = 0x06023824;
_g_musicCmdBufferReadPos                        = 0x06023840;
_g_musicCmdBufferWritePos                       = 0x06023844;
_g_sfxCmdBufferReadPos                          = 0x06023848;
_g_sfxCmdBufferWritePos                         = 0x0602384c;
_g_musicCommands                                = 0x06023850;
_g_sfxCommands                                  = 0x06023870;
_g_setToTwoToFadeInNextTrack                    = 0x06023890;
_g_audioLock                                    = 0x06023894;
_g_isPlayingJingle                              = 0x06023898;
_g_currentTonId                                 = 0x060282e4;
_g_stopChannel1AndResumeChannel0Timer           = 0x060282e8;
_g_currentSeqLoadedInBank3                      = 0x060282ec;

/* TODO: What is this??? Some kind of struct? */
_DAT_06004f10                                   = 0x06004f10;
/* TODO: What is this??? */
_g_unknownAudioThing                            = 0x06029d54;

