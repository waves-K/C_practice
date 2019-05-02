#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stdin, FILE* => 标准输入
// stdout, FILE* => 标准输出
// 键盘，显示器，一切皆文件的思想

int main() {
    
    // printf("hehe");
    // fprintf(stdout, "hehe\n");

    // c string 
    // 能够把一个数据进行格式化，然后放大偶一个字符串中
    // 这个操作就是在把一个整数，转换成了字符串
    char buf[1024] = { 0 };
    sprintf(buf, "%d", 100);
    printf("%s\n", buf);
    int num = 0;
    scanf(buf, "%d", &num);
    printf("%d\n", num);

    // FILE* fp = fopen("./test.txt", "w");
    // if (fp == NULL) {
    //     printf("test.txt fopen failed!\n");
    //     return 1;
    // }

    // char buf[1024] = { 0 };
    // // fgets 如果返回空指针，说明读到了 EOF
    // while (fgets(buf, sizeof(buf), stdin) != NULL) {
    //     fputs(buf, stdout);
    //     fputs(buf, fp);
    // }


    // int c;
    // while ((c = fgetc(stdin)) != EOF) {
    //     fputc(c, stdout);
    //     fputc(c, fp);
    // }
    // fflush(fp);
    // fclose(fp);
    

    // // 假设在文件中保存 数字 1
    // // 在文件中写一个 字符 1
    // // 在文件中写一个 数字 1
    // 
    // // fp 这类对象起了个专业术语名词，叫做 "句柄"

    // // r:只读   w:只写    a:追加写
    // FILE *fp = fopen("./test.txt", "a");
    // if (fp == NULL) {
    //     printf("fopen failed\n");
    // } else {
    //     printf("fopen ok!\n");
    // }

    // char buf[1024] = "bbbbb";
    // fwrite(buf, 1, strlen(buf), fp);

    // // char buf[1024] = { 0 };
    // // size_t size = fread(buf, 1, 4,fp);
    // printf("%s\n", buf);
    // // printf("%u\n", size);

    // // 对文件进行操作...
    // // 如果频繁进行文件打开，又没有关闭，叫做 "文件描述符泄漏"
    // fclose(fp);


    return 0;
}
