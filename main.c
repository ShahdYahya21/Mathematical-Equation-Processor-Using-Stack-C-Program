//Shahd Yahya 1210249
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Stack"

#define maxLength 100
typedef struct balance balance;
typedef struct valid valid;
struct valid{
    char val[maxLength];
    int validity;
};
struct balance{
    char val[maxLength];
    int balanceOrNot;
};
balance IsBalanced(char equation[maxLength][maxLength]) ;
valid ValidOperators(char equation[maxLength][maxLength]);
void reverse(char array[maxLength][maxLength]);
char*** InfixToPrefix(char equations[maxLength][maxLength][maxLength],int count,const int valid[maxLength]);
char** evaluation(char arr[maxLength][maxLength][maxLength],int count,const int valid[maxLength]);
void PrintEquations(char equations[maxLength][maxLength][maxLength],int count);
void ValidOrNot(const int valid[maxLength], int count,char equations[][maxLength][maxLength]);
char*** negativeCases(char equations[][maxLength][maxLength],int count,const int valid[maxLength]);

int main() {
    FILE *ptr;
    ptr = fopen("/Users/shahdyahya/Desktop/datastructure/Project 2/Input", "r");
    if (ptr == NULL) {
        printf("File could not be opened.\n");
        return 1;
    }
    char equation[maxLength][maxLength]; //array of string
    int count = 0;
    while (count < 100 && fscanf(ptr, "%s", equation[count]) == 1) {//Read equation from file
        count++;
    }
    fclose(ptr);

    int valid[maxLength] = {0};
    char equations[count][maxLength][maxLength];//array of array of strings
    char temp[maxLength];// to temporarily store the equation contents
    int i = 0, j = 0, Ind = 0;
    while (i < count) {
        j = 0;
        while (equation[i][j] != '\0') {
            if (equation[i][j] == ' ' || equation[i][j] == '(' || equation[i][j] == ')' ||
                equation[i][j] == '+' || equation[i][j] == '-' || equation[i][j] == '*' || equation[i][j] == '/' ||
                equation[i][j] == '[' || equation[i][j] == ']') {//if it an operator or parenthesis turn it to string and add it to an array
                temp[0] = equation[i][j];
                temp[1] = '\0';
                strcpy(equations[i][Ind], temp);
                Ind++;
                j++;
            }
            else {//if it a digit add it to a string
                int k = 0;
                while (equation[i][j] != ' ' && equation[i][j] != '(' && equation[i][j] != ')' &&
                       equation[i][j] != '+' && equation[i][j] != '-' && equation[i][j] != '*' &&
                       equation[i][j] != '/' && equation[i][j] != '[' && equation[i][j] != ']'
                       && equation[i][j] != '\0') {
                    temp[k] = equation[i][j];
                    k++;
                    j++;
                }
                temp[k] = '\0';
                strcpy(equations[i][Ind], temp);
                Ind++;
                memset(temp, '\0', sizeof(temp));
            }
        }
        i++;
        Ind = 0;
    }

    for (int i = 0; i < count; i++) {
        if (!IsBalanced(equations[i]).balanceOrNot || !ValidOperators(equations[i]).validity) {//see if it valid or not
            valid[i] = -1;
        }
        else valid[i] = 1;
    }

    char tempArray[count][maxLength][maxLength];// make copy of equations array
    for (int i = 0; i < count; i++) {
        int j = 0;
        while (equations[i][j][0] != '\0') {
            strcpy(tempArray[i][j], equations[i][j]);
            j++;
        }
    }
    char*** tempArray1 = negativeCases(tempArray,count,valid);//make copy of tempArray array
    char tempArray2[count][maxLength][maxLength];
    for (int i = 0; i < count; i++) {
        int j = 0;
        while (tempArray1[i][j][0] != '\0') {
            strcpy(tempArray2[i][j], tempArray1[i][j]);
            j++;

        }
    }


    char*** arr = InfixToPrefix(tempArray2, count, valid);
    char arr1[count][maxLength][maxLength];//create an array to save prefix expressions
    char arr2[count][maxLength][maxLength];//create an array to save prefix expressions reversed
    for (int i = 0; i < count; i++) {
        int j = 0;
        while (arr[i][j][0] != '\0') {
            int k = 0;
            while (arr[i][j][k] != '\0') {
                arr1[i][j][k] = arr[i][j][k];
                arr2[i][j][k] = arr[i][j][k];
                k++;
            }
            arr1[i][j][k] = '\0';
            arr2[i][j][k] = '\0';
            j++;
        }
        reverse(arr1[i]);
    }

    char** ans = evaluation(arr2,count,valid);//call evaluation function and save the answers in ans array

    printf("welcome to my calculator select (1 - 7):\n1-Enter the name of the file to read it\n2-Check the validity of equations\n3-print the prefix expressions\n4-Evaluate the prefix expressions\n5-Print invalid equations\n6-Print all equations to a file indicating for each input equation if it is valid or not and if valid, print out the prefix expression and its result\n7-exit\n");
    int choice;
    scanf("%d", &choice);
    while (choice != 1 && choice != 7) { // to make sure that the user will choose 1 at first to see the numbers
        printf("choose 1 first\n");
        scanf("%d", &choice);
    }
    bool start = false;
    while (choice != 7) {
        if (start) scanf("%d", &choice);// to not scan a choice at the first time
        else {
            start = true;
        }

        if (choice == 1) {
            printf("enter the file name\n");
            char str[maxLength]; //to save the name of file the user enter
            scanf("%s", str);
            while (strcmp(str, "Input")) {//check if it the file name
                printf("wrong name ,enter another file name\n");
                scanf("%s", str);
            }
            PrintEquations(equations, count);

        }
        else if (choice == 2) {//print validity of equations
            ValidOrNot(valid, count,equations);
        }
        else if (choice == 3) {//print prefix expression for valid equations only
            for (int i = 0; i < count; i++) {
                if (valid[i] == 1) {
                    printf("equation %d:\n", i + 1);
                    int j = 0;
                    while (strcmp(arr1[i][j], "\0") != 0) {
                        printf("%s ", arr1[i][j]);
                        j++;
                    }
                    printf("\n");
                }
            }
        }

        else if (choice == 4) {//print answers of equations
            for(int i = 0; i < count; i++){
                if(valid[i] == 1) printf("equation %d -> %s\n",i+1,ans[i]);
            }
        }

        else if (choice == 5) {//print invalid equations
            printf("invalid equations\n");
            for(int i = 0; i < count; i++){
                if(valid[i] == -1){
                    int j =0;
                    while(strcmp(equations[i][j],"\0") != 0){
                        printf("%s",equations[i][j]);
                        j++;
                    }
                    printf("\n");
                }
            }
        }
        else if (choice == 6) {//print on file
            FILE* outputFile = fopen("/Users/shahdyahya/Desktop/datastructure/Project 2/OutputEquation", "a");
            if (outputFile == NULL) {
                printf("Failed to open output file\n");
                return 1;
            }
            for(int i = 0; i < count; i++){
                int j = 0;
                fprintf(outputFile,"equation #%d -> ",i+1);
                while(strcmp(equations[i][j],"\0")){
                    fprintf(outputFile,"%s",equations[i][j]);
                    j++;
                }
                fprintf(outputFile,"\n");
            }
            for(int i = 0; i < count; i++){
                if(valid[i] == 1) fprintf(outputFile,"equation #%d -> valid\n",i+1);
                else if(valid[i] == -1){
                    fprintf(outputFile,"equation #%d -> invalid -> ",i+1);
                    if(!IsBalanced(equations[i]).balanceOrNot)  fprintf(outputFile,"%s\n", IsBalanced(equations[i]).val);
                    else if(!ValidOperators(equations[i]).validity)   fprintf(outputFile,"%s\n", ValidOperators(equations[i]).val);
                }
            }
            i = 0;
            while (i < count) {
                if (valid[i] == 1) {
                    fprintf(outputFile,"prefix equation %d:\n", i + 1);
                    j = 0;
                    while (strcmp(arr1[i][j], "\0") != 0) {
                        fprintf(outputFile,"%s ", arr1[i][j]);
                        j++;
                    }
                    fprintf(outputFile,"\n");

                }
                i++;
            }
            for(int i = 0; i < count; i++){
                if(valid[i] == 1) fprintf(outputFile,"equation %d -> %s\n",i+1,ans[i]);
            }
            fclose(outputFile);
        }
        else{
            printf("invalid input\n");
        }

        if(choice != 7) printf("You can select other option\n");
    }
    printf("The program ended");
}



balance IsBalanced(char equation[maxLength][maxLength]) {//check if the equation is balanced
    balance bal;
    int isBalanced = 1;
    char *str = malloc(maxLength * sizeof(char));
    stack st = createStack();
    int i = 0;
    while (strcmp(equation[i], "\0") != 0) {
        if (strcmp(equation[i], "(") == 0 || strcmp(equation[i], "[") == 0)//if it an open parenthesis add it to the stack
            push(equation[i], st);
        else if (!IsEmpty(st) && strcmp(equation[i], ")") == 0 && strcmp(Top(st), "(") == 0)
            pop(st);
        else if (!IsEmpty(st) && strcmp(equation[i], "]") == 0 && strcmp(Top(st), "[") == 0)
            pop(st);
        else if (IsEmpty(st) && (strcmp(equation[i], ")") == 0 )) {
            isBalanced = 0;
            strcpy(str,"there is no ( for )");
        }
        else if (IsEmpty(st) && strcmp(equation[i], "]") == 0){
            isBalanced = 0;
            strcpy(str,"there is no [ for ]");
        }
        i++;
    }

    if (!IsEmpty(st)){
        if(strcmp(Top(st), "[") == 0) strcpy(str,"[ is not closed");
        if(strcmp(Top(st), "(") == 0) strcpy(str,"( is not closed");
        isBalanced = 0;
    }
    strcpy(bal.val,str);
    bal.balanceOrNot =  isBalanced;
    return bal;
}
valid ValidOperators(char equation[maxLength][maxLength]) {//check if the equation is valid
    valid valid1;
    stack st = createStack();
    push(equation[0], st);
    int i = 1;
    int valid = 1;
    char* str = malloc(maxLength * sizeof(char));
    char* temp = malloc(maxLength * sizeof(char));
    while (strcmp(equation[i], "\0") != 0) {
        if ((strcmp(equation[i], "+") == 0 || strcmp(equation[i], "-") == 0 || strcmp(equation[i], "*") == 0 || strcmp(equation[i], "/") == 0) &&
            (strcmp(Top(st), "+") == 0 || strcmp(Top(st), "-") == 0 || strcmp(Top(st), "*") == 0 || strcmp(Top(st), "/") == 0)) {//if there is 2 operation in a row
            if(strcmp(equation[i], "-") == 0){//check if the minus is negative sign
                strcpy(str,Top(st));
                pop(st);
                if(!IsEmpty(st) && strcmp(Top(st),"(") != 0 && strcmp(Top(st),"[") != 0) {
                    push(str,st);
                }
                else{//if it is not negative sign it is invalid
                    push(str,st);
                    sprintf(temp, "%s%s is not valid(2 operations on a row)", Top(st), equation[i]);
                    valid = 0;
                    break;
                }


            }
            else {
                sprintf(temp, "%s%s is not valid(2 operations on a row)", Top(st), equation[i]);
                valid = 0;
                break;
            }

        }
            //to test this case number( without any operation
        else if ((strcmp(equation[i], "(") == 0 || strcmp(equation[i], "[") == 0) &&
                 ( strcmp(Top(st), "+") != 0 && strcmp(Top(st), "-") != 0 && strcmp(Top(st), "*") != 0 && strcmp(Top(st), "/") != 0 && strcmp(Top(st), "(") != 0) && strcmp(Top(st), "[")) {
            sprintf(temp,"there is no operation %s%s", Top(st), equation[i]);

            valid = 0;
            break;
        }
            //to test this case )number without any operation
        else if ((strcmp(Top(st), ")") == 0 || strcmp(Top(st), "]") == 0) &&
                 strcmp(equation[i], "+") != 0 && strcmp(equation[i], "-") != 0 && strcmp(equation[i], "*") != 0 && strcmp(equation[i], "/") != 0 && strcmp(equation[i], ")") != 0 && strcmp(Top(st), "]")) {
            sprintf(temp,"there is no operation %s%s", Top(st), equation[i]);
            valid = 0;
            break;
        }
            //to test this case()
        else if (strcmp(Top(st), "(") == 0 && strcmp(equation[i], ")") == 0) {
            sprintf(temp,"%s%s is not valid", Top(st), equation[i]);
            valid = 0;
            break;
        }
            //to test this case[]
        else if (strcmp(Top(st), "[") == 0 && strcmp(equation[i], "]") == 0) {
            sprintf(temp,"%s%s is not valid", Top(st), equation[i]);
            valid = 0;
            break;
        }
        push(equation[i], st);
        i++;
    }
    //if the last element in an array is an operation it is invalid
    if(valid == 1 && !IsEmpty(st) &&( strcmp(Top(st), "+") == 0 || strcmp(Top(st), "-") == 0 || strcmp(Top(st), "*") == 0 || strcmp(Top(st), "/") == 0)){
        sprintf(temp,"the equation end with %s is not valid", Top(st));
        valid = 0;
    }
    valid1.validity = valid;
    strcpy(valid1.val,temp);


    return valid1;
}

void reverse(char array[maxLength][maxLength]) {//reverse an equation
    int size = 0;
    int i = 0;
    while(strcmp(array[i], "\0") != 0){
        size++;
        i++;
    }
    char temp[maxLength];
    for (int i = 0; i < size / 2; i++) {
        strcpy(temp,array[i]);
        strcpy(array[i],array[size - 1 - i]);
        strcpy(array[size - 1 - i],temp);
    }
}

char*** InfixToPrefix(char equations[maxLength][maxLength][maxLength],int count,const int valid[maxLength]) {
    stack st = createStack();
    //memory allocation for an array
    char*** array = malloc(count * sizeof(char***));
    for (int i = 0; i < count; i++) {
        array[i] = malloc(maxLength * sizeof(char**));
        for (int j = 0; j < maxLength; j++) {
            array[i][j] = malloc(maxLength * sizeof(char*));
        }
    }

    for (int i = 0; i < count; i++) {
        if (valid[i] == -1) {
            continue;
        }
        reverse((equations[i]));//first we reverse an equation
        int countArray = 0;
        int j = 0;
        while (equations[i][j][0] != '\0') {
            if (strcmp(equations[i][j], ")") == 0 || strcmp(equations[i][j], "]") == 0) {//push ) and ] to the stack
                push(equations[i][j], st);
            }
            else if (strcmp(equations[i][j], "+") == 0) {

                while (!IsEmpty(st) && strcmp(Top(st), ")") != 0 && strcmp(Top(st), "]") != 0) {//we keep pop until the top is ] or ) it become empty
                    strcpy(array[i][countArray], Top(st));
                    pop(st);
                    countArray++;

                }

                push(equations[i][j], st);//we then push +

            }
            else if (strcmp(equations[i][j], "-") == 0) {
                while (!IsEmpty(st) && strcmp(Top(st), ")") != 0 && strcmp(Top(st), "]") != 0) {//we keep pop until the top is ] or ) it become empty
                    strcpy(array[i][countArray], Top(st));
                    countArray++;
                    pop(st);
                }
                push(equations[i][j], st);//we then push -
            }
            else if (strcmp(equations[i][j], "*") == 0) {
                while (!IsEmpty(st) && (strcmp(Top(st), "*") == 0 || strcmp(Top(st), "/") == 0)) {//we keep pop if the top is / or *
                    if (strcmp(Top(st), ")") != 0 && strcmp(Top(st), "]") != 0) {
                        strcpy(array[i][countArray], Top(st));
                        countArray++;
                    }
                    pop(st);
                }
                push(equations[i][j], st);//we then push *
            }
            else if (strcmp(equations[i][j], "/") == 0) {
                while (!IsEmpty(st) && (strcmp(Top(st), "*") == 0 || strcmp(Top(st), "/") == 0)) {//we keep pop if the top is / or *
                    if (strcmp(Top(st), ")") != 0 && strcmp(Top(st), "]") != 0) {
                        strcpy(array[i][countArray], Top(st));
                        countArray++;
                    }
                    pop(st);
                }
                push(equations[i][j], st);//we then push /
            }
            else if (strcmp(equations[i][j], "(") == 0) {
                while (!IsEmpty(st) && strcmp(Top(st), ")") != 0) {//we keep pop until the stack become empty or the top becomes )
                    strcpy(array[i][countArray], Top(st));
                    countArray++;
                    pop(st);
                }
                if (!IsEmpty(st) && strcmp(Top(st), ")") == 0) {//we the pop the top if it )
                    pop(st);
                }
            }
            else if (strcmp(equations[i][j], "[") == 0) {//we keep pop until the stack become empty or the top becomes ]
                while (!IsEmpty(st) && strcmp(Top(st), "]") != 0) {
                    strcpy(array[i][countArray], Top(st));
                    countArray++;
                    pop(st);
                }
                if (!IsEmpty(st) && strcmp(Top(st), "]") == 0) {//we the pop the top if it ]
                    pop(st);
                }
            }
            else {

                strcpy(array[i][countArray], equations[i][j]);
                countArray++;

            }
            j++;
        }

        while (!IsEmpty(st)) {//if the stack is not empty yet we add the element to an array
            strcpy(array[i][countArray], Top(st));
            countArray++;
            pop(st);
        }
    }
    return array;
}
//to evaluate the prefix expression
char** evaluation(char arr[maxLength][maxLength][maxLength], int count, const int valid[maxLength]) {
    char** ans = (char**)malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        ans[i] = (char*)malloc(maxLength * sizeof(char));
    }
    stack st = createStack();
    for (int i = 0; i < count; i++) {
        if (valid[i] == -1) continue;
        int operand1, operand2, result;
        int j = 0;
        while (arr[i][j][0] != '\0') {//we add numbers to the stack
            if (strcmp(arr[i][j], "+") != 0 && strcmp(arr[i][j], "-") != 0 && strcmp(arr[i][j], "*") != 0 &&
                strcmp(arr[i][j], "/") != 0) {
                push(arr[i][j], st);
            }

            else {//when we face an operation we pop 2 element and do an operation on them
                char *str = malloc(maxLength * sizeof(char));
                operand1 = atoi(Top(st));
                pop(st);
                operand2 = atoi(Top(st));
                pop(st);
                if (strcmp(arr[i][j], "+") == 0) {
                    result = operand1 + operand2;
                } else if (strcmp(arr[i][j], "-") == 0) {
                    result = operand1 - operand2;
                } else if (strcmp(arr[i][j], "*") == 0) {
                    result = operand1 * operand2;
                } else if (strcmp(arr[i][j], "/") == 0) {
                    result = operand1 / operand2;
                }


                sprintf(str, "%d", result);

                push(str, st);
            }
            j++;

        }
        strcpy(ans[i], Top(st));
        pop(st);
    }
    return ans;
}


void PrintEquations(char equations[maxLength][maxLength][maxLength],int count){
    for(int i = 0; i < count; i++){
        int j = 0;
        printf("equation #%d -> ",i+1);
        while(strcmp(equations[i][j],"\0")){
            printf("%s",equations[i][j]);
            j++;
        }
        printf("\n");
    }
}
//function to print if it valid or not and the reason if it invalid
void ValidOrNot(const int valid[maxLength], int count,char equations[][maxLength][maxLength]){
    for(int i = 0; i < count; i++){
        if(valid[i] == 1) printf("equation #%d -> valid\n",i+1);
        else if(valid[i] == -1){
            printf("equation #%d -> invalid -> ",i+1);
            if(!IsBalanced(equations[i]).balanceOrNot) printf("%s\n", IsBalanced(equations[i]).val);
            else if(!ValidOperators(equations[i]).validity)  printf("%s\n", ValidOperators(equations[i]).val);
        }
    }
}

//to handle the equations with negative numbers for example 3+-5 becomes 3 + -5
char*** negativeCases(char equations[][maxLength][maxLength], int count, const int valid[maxLength]) {
    //allocate a memory for an array
    char*** array = malloc(count * sizeof(char***));
    for (int i = 0; i < count; i++) {
        array[i] = malloc(maxLength * sizeof(char**));
        for (int j = 0; j < maxLength; j++) {
            array[i][j] = malloc(maxLength * sizeof(char*));
        }
    }

    for (int i = 0; i < count; i++) {
        bool negative = false;
        bool startP = false;
        int countP = 0;//to trace open parenthesis
        if (valid[i] == -1) continue;
        else {
            int j = 0;
            int arrayInd = 0;
            while (strcmp(equations[i][j], "\0") != 0) { //the number is negative if the minus is in the beginning or if it came after another operation
                if ((j == 0 && strcmp(equations[i][j], "-") == 0) || (j > 0 && strcmp(equations[i][j], "-") == 0 && (strcmp(equations[i][j - 1], "+") == 0 || strcmp(equations[i][j - 1], "*") == 0 || strcmp(equations[i][j - 1], "/") == 0 || strcmp(equations[i][j - 1], "-") == 0))) {
                    negative = true;
                }
                    //to track ( or [ and correctly distribute the negative sign
                else if (strcmp(equations[i][j], "(") == 0 || strcmp(equations[i][j], "[") == 0) {
                    startP = true;
                    countP++;
                    strcpy(array[i][arrayInd], equations[i][j]);
                    arrayInd++;
                }

                else if (strcmp(equations[i][j], ")") == 0 || strcmp(equations[i][j], "]") == 0) {
                    countP--;
                    if (negative) {
                        if (countP == 0) negative = false; //if all parenthesis was closed no need to keep add minus to numbers
                    }
                    strcpy(array[i][arrayInd], equations[i][j]);
                    arrayInd++;
                }
                else if (strcmp(equations[i][j], "+") == 0 || strcmp(equations[i][j], "*") == 0 || strcmp(equations[i][j], "/") == 0 || strcmp(equations[i][j], "-") == 0) {

                    strcpy(array[i][arrayInd], equations[i][j]);
                    arrayInd++;

                }
                else {

                    if (negative) {
                        char* negative_num = malloc(maxLength * sizeof(char));
                        negative_num[0] = '-';
                        strcpy(negative_num + 1, equations[i][j]);
                        if (startP == false) negative = false;
                        strcpy(array[i][arrayInd], negative_num); //add the negative number to the array
                        arrayInd++;
                        free(negative_num); // Free allocated memory
                    }
                    else {
                        strcpy(array[i][arrayInd], equations[i][j]);
                        arrayInd++;
                    }
                }
                j++;
            }
        }
    }
    return array;
}
