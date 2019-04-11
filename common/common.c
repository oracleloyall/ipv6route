#include"common.h"
char *search(char *s, char *t) {
	int i, j, k = 0, slen, tlen;
	char *p = NULL;

	slen = strlen(s);
	tlen = strlen(t);
	for (i = 0; i < slen; i++) {
		j = i;
		while (s[j] == t[k]) {
			k++;
			j++;
		}
		if (k >= tlen) {
			p = &s[i];
			return p;
		}
		k = 0;
	}

	return p;
}
//该函数执行时会显示最大匹配的字符串，返回值结果为最大匹配字符串的长度。
unsigned int FindMaxSubstr(const char *pcStr1,const char *pcStr2)
{
    int num=0;
    int n1,n2;
    int i,j,k,z;
    char a[50]={};

    n1=strlen(pcStr1);
    n2=strlen(pcStr2);

    for(i=0;i<n1;i++) //遍历pcStr1
    {
        k=1;
        for(j=0;j<n2;j++) //遍历pcStr2
        {
            if(pcStr2[j]==pcStr1[i]) //如果遇到相同字符串就继续判断下一个字符是否匹配
            {
                z=0; //统计匹配字符的个数，
                for(k=0;k<n2-j;k++)
                {
                    if(pcStr2[j+k]==pcStr1[i+k]) z++;
                    else break;
                }
            }
            if (z>num) //如果当前匹配字符串长度大于已存储的字符串，将新的更长的字符串放到a[]中
            {
                for(k=0;k<z;k++)
                {
                    a[k]=pcStr2[j+k];
                }
                a[k]='\0';
                num=z;
            }
        }
    }
    printf("最大匹配字符串：%s\n",a);
    return num;
}

void substr(char *s1, char *s2, int len)
{
    int i, j, m = 0;
    int p, q;
    int length = strlen(s2);
    char a[100] = {0};
    char b[100] = {0};
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < length; j++)
        {
            strcpy(a, "0");
            p = i;
            q = j;

            while(s1[p] == s2[q] && s1[p] != 0)
            {
                a[m] = s2[q];
                p++;
                q++;
                m++;
            }

            if(strlen(a) > strlen(b))
            {
                strcpy(b, a);
            }
            m = 0;
        }
    }
    printf("最大公子串：%s\n", b);
}
