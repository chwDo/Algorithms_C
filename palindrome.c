#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool isPalindrome(char A[], int len){
    int i;
    for(i = 0;i<len/2;i++){
        if (A[i] != A[len - 1 -i]){  //minus 1 for correcting offset of array index
            return false;
        }
    }
    return true;
}
//int main(){
//    printf("Enter a word: ");
//    char str[BUFSIZ];
//    scanf("%s",str);
//    char output[4];
//    (isPalindrome(str, strlen(str)) ? strcpy(output,"yes") : strcpy(output,"no"));
//    printf("%s",output);
//    return 0;
//}