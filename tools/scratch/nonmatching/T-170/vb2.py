{
 # one shared s16 temp instead of two
 'one_s16': ("""    s16 temp_a1;
    s16 temp_a1_2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_v1;
    u8 var_a2;""", """    s16 temp_a1;
    s32 temp_t7;
    s32 var_a1;
    s32 var_v1;
    u8 var_a2;"""),
 # no temp at all: inline the lh in each call
 'no_s16': ("""    s16 temp_a1;
    s16 temp_a1_2;
    s32 temp_t7;
    s32 var_a1;
    s32 var_v1;
    u8 var_a2;""", """    s32 temp_t7;
    s32 var_a1;
    s32 var_v1;
    u8 var_a2;"""),
}
