#include <stdio.h>
#include <string.h>
#include <stdlib.h>


double average(int N, double sumai)     //среднее количество вхождений слова в документ
{
    double aver;
    double NN = (double)N;
    aver = sumai/NN;
    return aver;
}


double sumup(double ai[], double aver, int N)        //считает значение числителя (см. формулу дисперсии)
{
    double sum = 0.0;
    for(int i = 0; i < N; i++)
    {
        sum += pow((ai[i]-aver), 2.0);
    }
    return sum;
}


double dispersion(int N, double sumup)
{
    double D;
    D = sumup/((double)N-1.0);

    return sqrt(D);
}


int main()
{
    char word[50];      //хранит слово, по которому ведется поиск
    char filePath[50];
    int N = 0;
    double buffai = 0.0;        //значение ai для открытого документа
    double sumai = 0.0;

    printf("Enter word: ");
    scanf("%s", word);

    printf("Enter amount of files: ");
    scanf("%d", &N);
    double ai[N];       //массив значений ai для каждого документа

    int j = 0;      //счетчик для массива ai

    for (int i = 0; i < N; i++){
        printf("Enter the path of the file: ");
        scanf("%s", filePath);


        FILE *file;
        file = fopen(filePath, "r");


        if (file == NULL)
        {
            printf("\nCan't open file!\n");
        }
        else
        {
            char buff = NULL;
            while(buff != EOF)
            {
                int k = 0;      //счетчик для wordBuff
                char wordBuff[50] = {};

                while(isspace((buff = fgetc(file))) == 0 && ispunct(buff) == 0 && buff != EOF)
                {
                    wordBuff[k] = buff;
                    k++;
                }
                if(strcmp(word, wordBuff) == 0)
                {
                    buffai++;
                }
            }
        }
        fclose(file);

        sumai += buffai;

        printf("\n%d matches!\n\n", (int)buffai);

        ai[j] = buffai;
        j++;
        buffai = 0.0;       //обнуляем значение счетчика слов в документе
    }

    printf("matches at all: %d\n", (int)sumai);
    printf("dispersion of word %s: %f", word, dispersion(N, sumup(ai, average(N, sumai), N)));

}
