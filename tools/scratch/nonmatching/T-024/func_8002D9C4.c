/* T-112: structural reconstruction; nonmatching, see REPORT.md. */
void func_8002D9C4(RenderCameraPose *pose, s32 frame, s32 duration, s32 reverse) {
    float to[5], from[5];
    float t, total;
    s32 i;
    if (reverse == 0) {
        for (i = 0;
        i < 5;
        i++) to[i] = ((float *)pose)[i];
        from[0] = D_800695CC;
        from[1] = D_800695D0;
        from[2] = D_800695D4;
        from[3] = D_800695D8;
        from[4] = D_800695DC;
    }
    else {
        for (i = 0;
        i < 5;
        i++) from[i] = ((float *)pose)[i];
        to[0] = D_800695CC;
        to[1] = D_800695D0;
        to[2] = D_800695D4;
        to[3] = D_800695D8;
        to[4] = D_800695DC;
    }
    t = frame;
    total = duration;
    D_800695CC = (to[0]-from[0])*t/total+from[0];
    D_800695D0 = (to[1]-from[1])*t/total+from[1];
    D_800695D4 = (to[2]-from[2])*t/total+from[2];
    func_8002DBDC(to[3], &from[3]);
    D_800695D8 = (to[3]-from[3])*t/total+from[3];
    func_8002DC48(&D_800695D8);
    func_8002DBDC(to[4], &from[4]);
    D_800695DC = (to[4]-from[4])*t/total+from[4];
    func_8002DC48(&D_800695DC);
}
