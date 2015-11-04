#include <stdio.h>
#include <stdlib.h>

typedef struct
{
        float *val;
} Matrix4;

typedef struct{
        float **val;
}Matrix4x4;

Matrix4 Mat_sum(Matrix4 m1, Matrix4 m2)
{
        Matrix4 ret;
        for(int i = 0; i < 4; i++)
        {
                ret.val[i] = m1.val[i] + m2.val[i];
        }
        return ret;
}

Matrix4 Mat_difference(Matrix4 m1, Matrix4 m2)
{
        Matrix4 ret;
        for(int i = 0; i < 4; i++)
        {
                ret.val[i] = m1.val[i] - m2.val[i];
        }
        return ret;
}

Matrix4 Mat_init (float a1, float a2, float a3, float a4);
{
        float s[4] = {a1, a2, a3, a4};
        Matrix4 ret;
        ret.val = s;
        return ret;
}

Matrix4x4 Mat4_init(Matrix4 m1, Matrix4 m2, Matrix4 m3, Matrix4 m4)
{
        Matrix4x4 ret;
        ret.val = (float**)malloc(16*sizeof(float));
        ret.val[0] = m1.val;
        ret.val[1] = m2.val;
        ret.val[2] = m3.val;
        ret.val[3] = m4.val;
}
