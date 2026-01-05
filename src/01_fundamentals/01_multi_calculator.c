#include <stdbool.h>
#include <stdio.h>

// --- Constantes de mensajes y formatos ---
const char *MENU_TITLE = "=== Calculadora Científica ===\n\n";
const char *MENU_OPTIONS = "1. Suma\n"
                           "2. Resta\n"
                           "3. Multiplicación\n"
                           "4. División\n"
                           "5. Potencia\n"
                           "6. Raíz cuadrada\n"
                           "7. Factorial\n"
                           "8. Salir\n";

const char *PROMPT_OPTION = "\nSeleccione una opción: ";
const char *PROMPT_FIRST_NUM = "Ingrese el primer número: ";
const char *PROMPT_SECOND_NUM = "Ingrese el segundo número: ";
const char *PROMPT_NUMBER = "Ingrese el número: ";
const char *PROMPT_BASE = "Ingrese la base: ";
const char *PROMPT_EXPONENT = "Ingrese el exponente (entero): ";

const char *RESULT_FORMAT = "\n  - El resultado es: %.6f\n\n";
const char *RESULT_INT_FORMAT = "\n  - El resultado es: %.0f\n\n";

const char *ERROR_INVALID_OPTION = "Opción no válida. Por favor intente de nuevo.\n\n";
const char *ERROR_DIV_ZERO = "Error: No se puede dividir por cero.\n\n";
const char *ERROR_SQRT_NEG =
    "Error: No se puede calcular la raíz cuadrada de un número negativo.\n\n";
const char *ERROR_FACT_NEG =
    "Error: El factorial solo está definido para enteros no negativos.\n\n";
const char *ERROR_FACT_NON_INT = "Error: El factorial solo se calcula para números enteros.\n\n";

// --- Enum para opciones del menú ---
typedef enum {
  OPC_SALIR = 0, // Usamos 0 internamente para facilitar inicialización
  OPC_SUMA = 1,
  OPC_RESTA,
  OPC_MULT,
  OPC_DIV,
  OPC_POT,
  OPC_RAIZ,
  OPC_FACT
} OpcionMenu;

// --- Prototipos ---
double add(double num1, double num2);
double sub(double num1, double num2);
double mult(double num1, double num2);
double div(double num1, double num2);
double power(double base, int exp);
double sqrt_custom(double num);
double fact(double num);
void mostrar_menu();
void menu_interactivo();

int main() {
  // Pruebas iniciales
  printf("Prueba sqrt(10): %.6f\n", sqrt_custom(10));
  printf("Prueba 2^3: %.6f\n", power(2, 3));
  printf("Prueba 6!: %.0f\n", fact(6));

  menu_interactivo();
  return 0;
}

// --- Operaciones básicas ---
double add(double num1, double num2) { return num1 + num2; }
double sub(double num1, double num2) { return num1 - num2; }
double mult(double num1, double num2) { return num1 * num2; }

double div(double num1, double num2) {
  if (num2 == 0) {
    printf("%s", ERROR_DIV_ZERO);
    return 0; // Valor dummy, ya se mostró error
  }
  return num1 / num2;
}

double power(double base, int exp) {
  double res = 1.0;
  if (exp < 0) {
    base = 1.0 / base;
    exp = -exp;
  }
  for (int i = 0; i < exp; i++) {
    res *= base;
  }
  return res;
}

double sqrt_custom(double num) {
  if (num < 0) {
    printf("%s", ERROR_SQRT_NEG);
    return 0; // Valor dummy
  }
  if (num == 0)
    return 0;

  double res = num;
  for (int i = 0; i < 20; i++) {
    res = 0.5 * (res + num / res);
  }
  return res;
}

double fact(double num) {
  // Validar que sea entero no negativo
  if (num < 0) {
    printf("%s", ERROR_FACT_NEG);
    return 0;
  }
  int n = (int)num;
  if (n != num) {
    printf("%s", ERROR_FACT_NON_INT);
    return 0;
  }

  double res = 1.0;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
}

// --- Interfaz ---
void mostrar_menu() {
  printf("%s", MENU_TITLE);
  printf("%s", MENU_OPTIONS);
}

void menu_interactivo() {
  OpcionMenu opcion = OPC_SUMA; // Valor inicial cualquiera, el bucle lo manejará
  double num1, num2, resultado;
  int exp;

  while (true) {
    mostrar_menu();
    printf("%s", PROMPT_OPTION);

    if (scanf("%u", (unsigned int *)&opcion) != 1) {
      printf("%s", ERROR_INVALID_OPTION);
      while (getchar() != '\n')
        ; // Limpiar buffer
      continue;
    }

    // Si se ingresa 8, salir
    if (opcion == 8) {
      printf("¡Gracias por usar la calculadora!\n");
      break;
    }

    switch (opcion) {
    case OPC_SUMA:
      printf("\n  === SUMA === \n\n");
      printf("%s", PROMPT_FIRST_NUM);
      scanf("%lf", &num1);
      printf("%s", PROMPT_SECOND_NUM);
      scanf("%lf", &num2);
      resultado = add(num1, num2);
      printf(RESULT_FORMAT, resultado);
      break;

    case OPC_RESTA:
      printf("\n  === RESTA === \n\n");
      printf("%s", PROMPT_FIRST_NUM);
      scanf("%lf", &num1);
      printf("%s", PROMPT_SECOND_NUM);
      scanf("%lf", &num2);
      resultado = sub(num1, num2);
      printf(RESULT_FORMAT, resultado);
      break;

    case OPC_MULT:
      printf("\n  === MULTIPLICACIÓN === \n\n");
      printf("%s", PROMPT_FIRST_NUM);
      scanf("%lf", &num1);
      printf("%s", PROMPT_SECOND_NUM);
      scanf("%lf", &num2);
      resultado = mult(num1, num2);
      printf(RESULT_FORMAT, resultado);
      break;

    case OPC_DIV:
      printf("\n  === DIVISIÓN === \n\n");
      printf("%s", PROMPT_FIRST_NUM);
      scanf("%lf", &num1);
      printf("%s", PROMPT_SECOND_NUM);
      scanf("%lf", &num2);
      resultado = div(num1, num2);
      if (num2 != 0) { // Solo mostrar resultado si no hubo error
        printf(RESULT_FORMAT, resultado);
      }
      break;

    case OPC_POT:
      printf("\n  === POTENCIA === \n\n");
      printf("%s", PROMPT_BASE);
      scanf("%lf", &num1);
      printf("%s", PROMPT_EXPONENT);
      scanf("%d", &exp);
      resultado = power(num1, exp);
      printf(RESULT_FORMAT, resultado);
      break;

    case OPC_RAIZ:
      printf("\n  === RAÍZ CUADRADA === \n\n");
      printf("%s", PROMPT_NUMBER);
      scanf("%lf", &num1);
      resultado = sqrt_custom(num1);
      if (num1 >= 0) { // Solo mostrar si no hubo error
        printf(RESULT_FORMAT, resultado);
      }
      break;

    case OPC_FACT:
      printf("\n  === FACTORIAL === \n\n");
      printf("%s", PROMPT_NUMBER);
      scanf("%lf", &num1);
      resultado = fact(num1);
      if (num1 >= 0 && num1 == (int)num1) { // Solo mostrar si válido
        printf(RESULT_INT_FORMAT, resultado);
      }
      break;

    default:
      printf("%s", ERROR_INVALID_OPTION);
      break;
    }
  }
}
