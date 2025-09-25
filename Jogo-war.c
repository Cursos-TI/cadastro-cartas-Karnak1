#include <stdio.h>
#include <string.h>

struct território {

char nome[30];
char cor[10];
int tropas;
};

for (int i = 0; i < 5; i++)
{
printf ("Cadastro do território %d:\n", i + 1);

printf ("Digite o nome do território: ");
scanf (" %[^\n]",terriotorios[i].nome);

printf ("Digite a cor do exército: ");
scanf (" %[^\n]",territorios[i].cor );

printf ("Digite a quantidade das tropas: ");
scanf ( "%d", &territorios[i].tropas);

printf ("\n");

for (int i = 0; i < 5; i++)
{
printf (" Território %d:\n", i + 1);

printf (" Nome: %s\n", territorios[i].nome);
printf (" Cor do exército: %s\n", territorios[i].cor);
printf (" Tropas: %d\n", territorios[i].tropas]);
printf ("\n");

printf("--------------------------\n");

}

return;0
}

