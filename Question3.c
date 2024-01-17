/*
3. ���ظ��ַ�����Ӵ�
    ����һ���ַ��� s �������ҳ����в������ظ��ַ��� ��Ӵ� �ĳ��ȡ�
    ʾ�� 1:
    ����: s = "abcabcbb"
    ��� : 3
    ���� : ��Ϊ���ظ��ַ�����Ӵ��� "abc"�������䳤��Ϊ 3��

    ʾ�� 2 :
    ���� : s = "bbbbb"
    ��� : 1
    ���� : ��Ϊ���ظ��ַ�����Ӵ��� "b"�������䳤��Ϊ 1��

    ʾ�� 3 :
    ���� : s = "pwwkew"
    ��� : 3
    ���� : ��Ϊ���ظ��ַ�����Ӵ��� "wke"�������䳤��Ϊ 3��
    ��ע�⣬��Ĵ𰸱����� �Ӵ� �ĳ��ȣ�"pwke" ��һ�������У������Ӵ���

*/

#include <stdio.h>
#include <string.h>
#define MAX_CHARS 256

/*
    ˼·��
        ����һ���ַ����飨�ַ�����������ܱ�֤[0,3]������û���ظ�Ԫ�أ����¼���һ��Ԫ��a��ֻ��Ҫ��֤ a!=s[0],...,a!=s[3],
        ����֤���˼�����Ԫ��a���ַ�������Ȼû���ظ�Ԫ��
    ������
        ����һ��head��ֵΪ0��һ��slen��ֵΪ1
        ��Ҫһֱ��֤[head,head+slen]��û���ظ�Ԫ�� 
        ��[0,1]û���ظ�Ԫ�أ�Ȼ��slen++
        ������֤[head,head+slen]��û���ظ�Ԫ�أ����¼����Ԫ�ز��ظ��ַ������е���Ԫ��
        ���ĳ�ζԱȹ����г��֣��±�Ϊi����head=i+1,slen=1
        ���¿�ʼ����slen
        ��head+slen>=strlen(s)ʱ���������

    ʱ�临�Ӷ�:O(n^2)
    �ռ临�Ӷ�:O(1)
*/
int lengthOfLongestSubstring(char* s) {
    if (strlen(s) == 0 || strlen(s) == 1) // ��������ַ���Ϊ�ջ���ֻ��һ���ַ�����ֱ�ӷ����ַ�����С
        return strlen(s);
    int head = 0, slen = 1, max = 0, flag = 1;
    char temp;
    for (; head + slen < strlen(s); ) {
        for (int i = head, temp = s[head+slen]; i < head+slen; i++) {
            if (s[i] == temp) {
                head = i+1;
                slen = 1;
                flag = 0;
            }
            if (!flag)
                break;
        }
        if (flag)
            slen++;
        else
            flag = 1;
        if (max < slen)
            max = slen;
    }
    return max;
}

/*
    ʱ�临�Ӷ�:O(n)
    �ռ临�Ӷ�:O(n)
*/
int lengthOfLongestSubstring1(char* s) {
    int last_index[MAX_CHARS]; // �洢�ַ������ֵ�λ��
    int max_length = 0;        // �洢��Ӵ��ĳ���
    int start = 0;             // �Ӵ�����ʼλ��

    // ��ʼ�������ַ������λ��Ϊ -1
    for (int i = 0; i < MAX_CHARS; i++) {
        last_index[i] = -1;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        // ����ַ��Ѿ����ֹ��������Ӵ�����ʼλ��
        if (last_index[s[i]] >= start) {
            start = last_index[s[i]] + 1;
        }

        // �����ַ������λ��
        last_index[s[i]] = i;

        // ������Ӵ��ĳ���
        if (i - start + 1 > max_length) {
            max_length = i - start + 1;
        }
    }
    return max_length;
}

int main() {
    char a[] = "pwwkew";
    printf("%d\n", lengthOfLongestSubstring(a));
    return 0;
}