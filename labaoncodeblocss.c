#include "functions_headings.h"

//--------------------------------main---------------------------------------

int main()
{
	FILE* Laba = NULL;
	FILE* LabaNew = NULL;

	if (OpenFiles(&Laba, &LabaNew) == -1)
		return -1;

	fseek(Laba, 0, SEEK_SET);
	fseek(LabaNew, 0, SEEK_SET);

	Topic(LabaNew);

	while (!CheckTheType(Laba))
        MoveToNewStr(Laba);

    int while_breaker = 1;

	while (while_breaker == 1)
	{
        switch (PrintUIRx3(Laba, LabaNew))
        {
        case 1:
            break;
        case 0:
            {
            while_breaker = 0;
            break;
            }
        case -1:
            {
            printf("Are you sure your data is correct? Please, check it.\n\n");

            fclose(Laba);
            fclose(LabaNew);

            return 0;
            }
        default:
        {
            fclose(Laba);
            fclose(LabaNew);

            return -1;
        }
        }
	}

	fclose(Laba);
	fclose(LabaNew);

	printf("Your lab project is ready. It is put into file labanew.\n");

	return 0;
}

//------------------------------------functions------------------------------------------

int OpenFiles(FILE** Laba, FILE** LabaNew)
{
    printf("Please, enter adress of the file with lab project. Write it in format: *.txt.\n");
    char name[60] = {};
    scanf("%s", name);
	*Laba = fopen(name, "r");

	if (*Laba == NULL)
	{
	    printf("Sorry, this file doesn't exist.");
		return -1;
	}

	*LabaNew = fopen("labanew.txt", "w");

	return 0;
}

//------------------------------------------------------------------------------------

void Topic(FILE* LabaNew)
{
	fprintf(LabaNew, "l = 20 cm\t\t\tl = 30 cm\t\t\tl = 50 cm\n");
	fprintf(LabaNew, "V, mV  I, mA  R, Om\t\tV, mV  I, mA  R, Om\t\tV, mV  I, mA  R, Om\n");
}

//-------------------------------------------------------------------------------------------

void MoveToNewStr(FILE* Laba)
{
	char CurrentChar = getc(Laba);
	int StrLen = 0;
	for (StrLen = 0; CurrentChar != '\n'; StrLen++)
	{
		CurrentChar = getc(Laba);
	}
}

//------------------------------------------------------------------------------------------

int CheckTheType(FILE* Laba)
{
    int Type;

    Type = getc(Laba);
    fseek(Laba, -1, SEEK_CUR);

    if (Type >= '0' && Type <= '9')
    {
        return 1;
    }
    else
        return 0;
}

//--------------------------------------------------------------------------------------------

int PrintUIR(FILE* Laba, FILE* LabaNew)
{
	double U = 0;
	fscanf(Laba, "%lf", &U);

	double I = 0;
	fscanf(Laba, "%lf", &I);

	if (U > 10000 || I > 10000 || I < 0.001)
        return -1;

	double R = 0;
	R = U / I;

	fprintf(LabaNew, "%5.1lf  %5.1lf  %5.1lf", U, I, R);

	return 0;
}

//------------------------------------------------------------------------------------------

int PrintUIRx3(FILE* Laba, FILE* LabaNew)
{
	if (PrintUIR(Laba, LabaNew) == -1)
        return -1;
	fprintf(LabaNew, "\t\t");
	if (PrintUIR(Laba, LabaNew) == -1)
        return -1;
	fprintf(LabaNew, "\t\t");
	if (PrintUIR(Laba, LabaNew) == -1)
        return -1;
	fprintf(LabaNew, "\n");

	fseek(Laba, 1, SEEK_CUR);
	if (getc(Laba) == EOF)
        return 0;

    fseek(Laba, -1, SEEK_CUR);
    return 1;
}
