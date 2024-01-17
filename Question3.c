/*
3. 无重复字符的最长子串
    给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
    示例 1:
    输入: s = "abcabcbb"
    输出 : 3
    解释 : 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

    示例 2 :
    输入 : s = "bbbbb"
    输出 : 1
    解释 : 因为无重复字符的最长子串是 "b"，所以其长度为 1。

    示例 3 :
    输入 : s = "pwwkew"
    输出 : 3
    解释 : 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
    请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

*/

#include <stdio.h>
#include <string.h>
#define MAX_CHARS 256

/*
    思路：
        对于一个字符数组（字符串），如果能保证[0,3]区间内没有重复元素，则新加入一个元素a，只需要保证 a!=s[0],...,a!=s[3],
        即能证明了加入新元素a后，字符数组仍然没有重复元素
    方法：
        设置一个head初值为0，一个slen初值为1
        即要一直保证[head,head+slen]内没有重复元素 
        即[0,1]没有重复元素，然后slen++
        继续保证[head,head+slen]内没有重复元素，即新加入的元素不重复字符数组中的老元素
        如果某次对比过程中出现，下标为i，让head=i+1,slen=1
        重新开始计算slen
        当head+slen>=strlen(s)时，遍历完成

    时间复杂度:O(n^2)
    空间复杂度:O(1)
*/
int lengthOfLongestSubstring(char* s) {
    if (strlen(s) == 0 || strlen(s) == 1) // 如果传入字符串为空或者只有一个字符，则直接返回字符串大小
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
    时间复杂度:O(n)
    空间复杂度:O(n)
*/
int lengthOfLongestSubstring1(char* s) {
    int last_index[MAX_CHARS]; // 存储字符最后出现的位置
    int max_length = 0;        // 存储最长子串的长度
    int start = 0;             // 子串的起始位置

    // 初始化所有字符的最后位置为 -1
    for (int i = 0; i < MAX_CHARS; i++) {
        last_index[i] = -1;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        // 如果字符已经出现过，更新子串的起始位置
        if (last_index[s[i]] >= start) {
            start = last_index[s[i]] + 1;
        }

        // 更新字符的最后位置
        last_index[s[i]] = i;

        // 更新最长子串的长度
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