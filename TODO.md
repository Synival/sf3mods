TODO:

- Update 1ST.BIN functions to correct names for SGL, GFS, etc.
- Rewrite the music patch:
    - Don't use X001 anymore - find a new spot for the new code
    - Verify command requirements
    - Migrate ASM in DFRs to actual .S files
    - Generate DFRs
- Music fix patch for PD

Done:

- Documentation (README.md)
- Make DFR(s) for compressAniTables
- Complain if an .ld file doesn't have objects
- Add explicit objects to link steps
- Complain if a .DFR.in file doesn't have parameters
- Update `dfrc_action_t` input to be extracted from named parameters
- Update dfrc to use actions
- Wildcards for finding projects and their src's, ld's, and dfr's
