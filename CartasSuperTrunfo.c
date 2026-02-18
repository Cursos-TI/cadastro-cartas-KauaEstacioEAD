#include <assert.h>
#include <stdio.h>
#include <string.h>

// =============================================================
// Super Trunfo - Países
// Nível: Mestre
// Descrição: Cadastra duas cartas de cidades, calcula
// propriedades derivadas e compara usando operadores relacionais.
// =============================================================

// ---------------------------------------------------------
// Limpa o buffer de entrada
// ---------------------------------------------------------
void clearBuffer() {
  while (getchar() != '\n')
    ;
}

// ---------------------------------------------------------
// Lê e valida os dados de uma carta
// Repete até que o valor correto seja inserido
// ---------------------------------------------------------
void readCard(char *state, char *code, char *city, long int *population,
              double *area, double *gdp, int *tourism) {

  while (1) {
    printf("State (A-H): ");
    scanf(" %c", state);
    if (*state >= 'A' && *state <= 'H')
      break;
    printf("  Invalid! State must be a letter between A and H.\n");
  }

  while (1) {
    printf("Card Code (ex: %c01): ", *state);
    scanf("%3s", code);
    if (code[0] == *state && strlen(code) == 3)
      break;
    printf("  Invalid! Code must start with '%c' and have 3 characters.\n",
           *state);
  }

  while (1) {
    printf("City Name: ");
    scanf(" %[^\n]", city);
    if (strlen(city) > 0)
      break;
    printf("  Invalid! City name cannot be empty.\n");
  }

  while (1) {
    printf("Population: ");
    scanf("%ld", population);
    if (*population > 0)
      break;
    printf("  Invalid! Population must be greater than 0.\n");
    clearBuffer();
  }

  while (1) {
    printf("Area (km2): ");
    scanf("%lf", area);
    if (*area > 0)
      break;
    printf("  Invalid! Area must be greater than 0.\n");
    clearBuffer();
  }

  while (1) {
    printf("GDP (billions): ");
    scanf("%lf", gdp);
    if (*gdp > 0)
      break;
    printf("  Invalid! GDP must be greater than 0.\n");
    clearBuffer();
  }

  while (1) {
    printf("Number of Tourist Spots: ");
    scanf("%d", tourism);
    if (*tourism >= 0)
      break;
    printf("  Invalid! Tourist spots must be 0 or greater.\n");
    clearBuffer();
  }
}

// ---------------------------------------------------------
// Exibe todas as propriedades da carta, incluindo as calculadas
// ---------------------------------------------------------
void printCard(int number, char state, char *code, char *city,
               long int population, double area, double gdp, int tourism,
               double density, double gdp_per_capita, double super_power) {

  printf("Card %d:\n", number);
  printf("  State:              %c\n", state);
  printf("  Code:               %s\n", code);
  printf("  City Name:          %s\n", city);
  printf("  Population:         %ld\n", population);
  printf("  Area:               %.2lf km2\n", area);
  printf("  GDP:                %.2lf billion reais\n", gdp);
  printf("  Tourist Spots:      %d\n", tourism);
  printf("  Pop. Density:       %.2lf hab/km2\n", density);
  printf("  GDP per Capita:     %.2lf reais\n", gdp_per_capita);
  printf("  Super Power:        %.2lf\n", super_power);
}

// ---------------------------------------------------------
// Compara uma propriedade entre duas cartas e exibe o vencedor
// lower_wins: 1 = menor valor vence (densidade), 0 = maior vence
// ---------------------------------------------------------
void compareProperty(const char *property, double val1, double val2,
                     int lower_wins) {
  int card1_wins = lower_wins ? (val1 < val2) : (val1 > val2);
  int card2_wins = lower_wins ? (val2 < val1) : (val2 > val1);

  const char *winner = card1_wins ? "Card 1" : card2_wins ? "Card 2" : "Draw";

  printf("  %-22s Card 1: %12.2lf | Card 2: %12.2lf | Winner: %s\n", property,
         val1, val2, winner);
}

// ---------------------------------------------------------
// Função principal
// ---------------------------------------------------------
int main() {

  // Área para definição das variáveis para armazenar as propriedades das
  // cidades
  char state1, state2;
  char code1[4], code2[4];
  char city1[50], city2[50];
  long int population1, population2;
  double area1, area2;
  double gdp1, gdp2;
  int tourism1, tourism2;

  // Área para entrada de dados
  printf("=== Card 1 ===\n");
  readCard(&state1, code1, city1, &population1, &area1, &gdp1, &tourism1);

  printf("\n=== Card 2 ===\n");
  readCard(&state2, code2, city2, &population2, &area2, &gdp2, &tourism2);

  // Cálculo das propriedades derivadas
  double density1 = population1 / area1;
  double gdp_per_capita1 = (gdp1 * 1e9) / population1;
  double super_power1 = population1 + area1 + (gdp1 * 1e9) + tourism1 +
                        gdp_per_capita1 + density1;

  double density2 = population2 / area2;
  double gdp_per_capita2 = (gdp2 * 1e9) / population2;
  double super_power2 = population2 + area2 + (gdp2 * 1e9) + tourism2 +
                        gdp_per_capita2 + density2;

  // Área para exibição dos dados da cidade
  printf("\n============================================================\n");
  printCard(1, state1, code1, city1, population1, area1, gdp1, tourism1,
            density1, gdp_per_capita1, super_power1);
  printf("\n");
  printCard(2, state2, code2, city2, population2, area2, gdp2, tourism2,
            density2, gdp_per_capita2, super_power2);

  // Comparação das cartas
  printf("\n============================================================\n");
  printf("Comparison:\n");
  compareProperty("Population", (double)population1, (double)population2, 0);
  compareProperty("Area", area1, area2, 0);
  compareProperty("GDP", gdp1, gdp2, 0);
  compareProperty("Tourist Spots", (double)tourism1, (double)tourism2, 0);
  compareProperty("Pop. Density", density1, density2, 1);
  compareProperty("GDP per Capita", gdp_per_capita1, gdp_per_capita2, 0);
  compareProperty("Super Power", super_power1, super_power2, 0);

  printf("============================================================\n");

  return 0;
}