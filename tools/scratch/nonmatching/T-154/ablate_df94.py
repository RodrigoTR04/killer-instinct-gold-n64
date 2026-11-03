ATOMS = {
 'no_tick': [("    tick = &D_80282DC0;\n", ""), ("*tick", "D_80282DC0", "all"), ("(D_80282DC0)++;", "D_80282DC0++;"), ("    s32 *tick;\n", "")],
 'no_sine': [("    sine = sinf(*tick * 0.017453292519943295);\n    guLookAtReflect(&reflection, D_802D36B0, sine * 60.0f,", "    guLookAtReflect(&reflection, D_802D36B0, sinf(*tick * 0.017453292519943295) * 60.0f,"), ("    f32 sine;\n", "")],
 'split_join1': [("        g->w0 = 0x03820010; g->w1 = (u32)D_802D36C0;", "        g->w0 = 0x03820010;\n        g->w1 = (u32)D_802D36C0;")],
 'split_join2': [("        g->w0 = 0x06000000; g->w1 = (u32)D_80282D28;", "        g->w0 = 0x06000000;\n        g->w1 = (u32)D_80282D28;")],
 'two_width': [("    f64 width;\n", "    f64 width;\n    f64 width2;\n"), ("            if (fixed) width = 35.8;\n            else width = glyph->width * 10.0f;\n            x = x + scale * width;", "            if (fixed) width2 = 35.8;\n            else width2 = glyph->width * 10.0f;\n            x = x + scale * width2;")],
 'ternary': [("            if (fixed) width = 32.22;\n            else width = glyph->width * 9.0f;\n            x = x + scale * width;", "            x = x + scale * (fixed ? 32.22 : glyph->width * 9.0f);")],
 'idx_loop_ptr': [("    for (length = 0; text[length]; length++) {\n    }\n    angle -= length * 30;", "    length = strlen(text);\n    angle -= length * 30;")],
 'matrix_var': [("            guTranslate(&matrices[count], x, y, z);", "            matrix = &matrices[count];\n            guTranslate(matrix, x, y, z);"), ("    s32 length;\n", "    s32 length;\n    TextMtx *matrix;\n")],
}
