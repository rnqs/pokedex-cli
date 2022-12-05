#include <stdio.h>
#include <string.h>

#define POKEDEX_FILE_PATH "./pokedex.dat"

void fileSave();
void fileLoad();
void fillPokedex();
void updatePokedex();
void pokeNumericSearch();
void pokeNameSearch();
void pokeLogicRemove();
void pokeRemove();
void pokeTrash();
void pokeSort(int n);
int pokeBinarySearch(int left, int right, int x);
void pokePrintTable(int start, int end, int active);
void repeat(char *input, int count);

typedef struct {
  int pokedexNum;
  char pokeName[32];
  double height;
  double weight;
  char pokeType[32];
  char gender[32];
  int isActive;
} Pokemon;

Pokemon pokedex[152];
int pokemonsOnPokedex = 0;

int main(void) {
  printf(
      "┌─────────────────────────────────────────────────────────────────┐\n"
      "│                             Pokedex                             │\n"
      "└─────────────────────────────────────────────────────────────────┘\n"
      "\n\n");

  printf(
      "                         \\:.             .:/\n"
      "                          \\``._________.''/ \n"
      "                           \\             / \n"
      "                   .--.--, / .':.   .':. \\\n"
      "                  /__:  /  | '::' . '::' |\n"
      "                     / /   |`.   ._.   .'|\n"
      "                    / /    |.'         '.|\n"
      "                   /___-_-,|.\\  \\   /  /.|\n"
      "                        // |''\\.;   ;,/ '|\n"
      "                        `==|:=         =:|\n"
      "                           `.          .'\n"
      "                             :-._____.-:\n"
      "                            `''       `''\n\n");

  fileLoad();

  pokePrintTable(0, pokemonsOnPokedex, 1);

  int repeat = 1;
  do {
    int operation;
    do {
      printf("\nSelecione uma das operações abaixo:\n");
      printf("1 - Buscar\n");
      printf("2 - Cadastrar\n");
      printf("3 - Alterar\n");
      printf("4 - Excluir\n");
      printf("5 - Lixeira\n");

      scanf("%d", &operation);

      if (operation < 1 || operation > 5)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (operation < 1 || operation > 5);

    if (operation == 1) {
      int searchType;

      do {
        printf("\nComo deseja fazer a busca?\n");
        printf("1 - Número do Pokémon na pokedex\n");
        printf("2 - Nome do Pokémon\n");

        scanf("%d", &searchType);

        if (searchType < 1 || searchType > 2)
          printf("\nOpção invalida! Tente novamente.\n");
      } while (searchType < 1 || searchType > 2);

      if (searchType == 1) {
        pokeNumericSearch();
      } else {
        pokeNameSearch();
      }
    }

    if (operation == 2) {
      fillPokedex();
    }

    if (operation == 3) {
      updatePokedex();
    }

    if (operation == 4) {
      int removeType;

      do {
        printf("\nComo deseja fazer a exclusão?\n");
        printf("1 - Exclusão lógica\n");
        printf("2 - Exclusão física\n");

        scanf("%d", &removeType);

        if (removeType < 1 || removeType > 2)
          printf("\nOpção invalida! Tente novamente.\n");
      } while (removeType < 1 || removeType > 2);

      if (removeType == 1) {
        pokeLogicRemove();
      } else {
        pokeRemove();
      }
    }

    if (operation == 5) {
      pokeTrash();
    }

    do {
      printf("\nDeseja realizar outra operação?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);
  } while (repeat == 1);

  return 0;
}

void fileSave() {
  pokeSort(pokemonsOnPokedex);

  FILE *file = fopen(POKEDEX_FILE_PATH, "wb");

  fwrite(&pokemonsOnPokedex, sizeof(pokemonsOnPokedex), 1, file);

  for (int i = 0; i < pokemonsOnPokedex; i++) {
    fwrite(&pokedex[i].pokedexNum, sizeof(pokedex[i].pokedexNum), 1, file);
    fwrite(pokedex[i].pokeName, sizeof(pokedex[i].pokeName), 1, file);
    fwrite(&pokedex[i].height, sizeof(pokedex[i].height), 1, file);
    fwrite(&pokedex[i].weight, sizeof(pokedex[i].weight), 1, file);
    fwrite(pokedex[i].pokeType, sizeof(pokedex[i].pokeType), 1, file);
    fwrite(pokedex[i].gender, sizeof(pokedex[i].gender), 1, file);
    fwrite(&pokedex[i].isActive, sizeof(pokedex[i].isActive), 1, file);
  }

  fclose(file);
}

void fileLoad() {
  FILE *file;

  if ((file = fopen(POKEDEX_FILE_PATH, "r")) == NULL) {
    file = fopen(POKEDEX_FILE_PATH, "wb");
  } else {
    fread(&pokemonsOnPokedex, sizeof(pokemonsOnPokedex), 1, file);

    for (int i = 0; i < pokemonsOnPokedex; i++) {
      fread(&pokedex[i].pokedexNum, sizeof(pokedex[i].pokedexNum), 1, file);
      fread(pokedex[i].pokeName, sizeof(pokedex[i].pokeName), 1, file);
      fread(&pokedex[i].height, sizeof(pokedex[i].height), 1, file);
      fread(&pokedex[i].weight, sizeof(pokedex[i].weight), 1, file);
      fread(pokedex[i].pokeType, sizeof(pokedex[i].pokeType), 1, file);
      fread(pokedex[i].gender, sizeof(pokedex[i].gender), 1, file);
      fread(&pokedex[i].isActive, sizeof(pokedex[i].isActive), 1, file);
    }
  }

  fclose(file);
}

void fillPokedex() {
  int currentIndex = pokemonsOnPokedex;
  int repeat = 1;

  do {
    printf("\nNúmero do Pokémon na Pokedex: ");
    scanf(" %d", &pokedex[currentIndex].pokedexNum);

    printf("\nNome do Pokémon: ");
    scanf(" %[^\n]s", pokedex[currentIndex].pokeName);

    printf("\nAltura do Pokémon: ");
    scanf(" %lf", &pokedex[currentIndex].height);

    printf("\nPeso do Pokémon: ");
    scanf(" %lf", &pokedex[currentIndex].weight);

    printf("\nTipo do pokémon: ");
    scanf(" %[^\n]s", pokedex[currentIndex].pokeType);

    printf("\nGênero do pokémon: ");
    scanf(" %[^\n]s", pokedex[currentIndex].gender);

    pokedex[currentIndex].isActive = 1;

    currentIndex++;
    pokemonsOnPokedex = currentIndex;

    fileSave();

    do {
      printf("\nDeseja continuar a cadastrar?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);

  fileSave();
}

void updatePokedex() {
  int foundOnIndex = -1;

  do {
    int pokeIndexToUpdate = 0;

    printf("\nDigite o número do Pokémon: ");
    scanf("%d", &pokeIndexToUpdate);

    for (int i = 0; i < pokemonsOnPokedex; i++) {
      if (pokedex[i].pokedexNum == pokeIndexToUpdate) {
        foundOnIndex = i;
      }
    }

    if (foundOnIndex == -1) {
      printf("Pokémon não encontrado, tente novamente.\n");
    }
  } while (foundOnIndex == -1);

  int repeat = 1;
  do {
    int propToUpdate = 0;
    printf("\nSelecione a propriedade para alteração em %s:\n",
           pokedex[foundOnIndex].pokeName);
    printf("1 - Número da Pokedex\n");
    printf("2 - Nome\n");
    printf("3 - Altura\n");
    printf("4 - Peso\n");
    printf("5 - Tipo\n");
    printf("6 - Gênero\n");

    scanf("%d", &propToUpdate);

    switch (propToUpdate) {
      case 1: {
        printf("\nDigite o novo número da Pokedex: ");
        scanf("%d", &pokedex[foundOnIndex].pokedexNum);
        break;
      }

      case 2: {
        printf("\nDigite o novo nome do Pokémon: ");
        scanf(" %[^\n]s", pokedex[foundOnIndex].pokeName);
        break;
      }

      case 3: {
        printf("\nDigite a nova altura do Pokémon: ");
        scanf("%lf", &pokedex[foundOnIndex].height);
        break;
      }

      case 4: {
        printf("\nDigite o novo peso do Pokémon: ");
        scanf("%lf", &pokedex[foundOnIndex].weight);
        break;
      }

      case 5: {
        printf("\nDigite o novo tipo do Pokémon: ");
        scanf(" %[^\n]s", pokedex[foundOnIndex].pokeType);
        break;
      }

      case 6: {
        printf("\nDigite o novo gênero do Pokémon: ");
        scanf(" %[^\n]s", pokedex[foundOnIndex].gender);
        break;
      }

      default: {
        printf("\nOpção inválida!");
        break;
      }
    }

    do {
      printf("\nVocê deseja alterar mais algum dado de %s?\n",
             pokedex[foundOnIndex].pokeName);
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);

  fileSave();
}

void pokeNumericSearch() {
  int userSearch = 0;
  int pokeFoundAt;

  pokeSort(pokemonsOnPokedex);

  int repeat = 1;
  do {
    printf("\nDigite o número do Pokémon na Pokedex: ");
    scanf("%d", &userSearch);

    pokeFoundAt = pokeBinarySearch(0, pokemonsOnPokedex - 1, userSearch);

    if (pokeFoundAt == -1) {
      printf("\nO Pokémon buscado não foi encontrado.\n");
    } else {
      pokePrintTable(pokeFoundAt, pokeFoundAt + 1, 1);
    }

    do {
      printf("\nVocê deseja buscar outro Pokémon?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);
}

void pokeNameSearch() {
  char userSearch[32];
  int pokeFoundAt;

  int repeat = 1;
  do {
    printf("\nDigite o nome do Pokémon desejado: ");
    scanf(" %[^\n]s", userSearch);

    pokeFoundAt = -1;
    for (int i = 0; i < pokemonsOnPokedex; i++) {
      if (strcmp(userSearch, pokedex[i].pokeName) == 0) {
        pokeFoundAt = i;
      }
    }

    if (pokeFoundAt == -1) {
      printf("\nO Pokémon buscado não foi encontrado.\n");
    } else {
      pokePrintTable(pokeFoundAt, pokeFoundAt + 1, 1);
    }

    do {
      printf("\nVocê deseja buscar outro Pokémon?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);
}

void pokeLogicRemove() {
  int foundOnIndex = -1;

  int repeat = 1;
  do {
    do {
      int pokeIndexToRemove = 0;

      printf("\nDigite o número do Pokémon: ");
      scanf("%d", &pokeIndexToRemove);

      for (int i = 0; i < pokemonsOnPokedex; i++) {
        if (pokedex[i].pokedexNum == pokeIndexToRemove) {
          foundOnIndex = i;
        }
      }

      if (foundOnIndex == -1) {
        printf("Pokémon não encontrado, tente novamente.\n");
      }
    } while (foundOnIndex == -1);

    pokedex[foundOnIndex].isActive = 0;

    printf("\nPokemon excluído com sucesso.\n");

    do {
      printf("\nVocê deseja excluir mais algum Pokémon?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);

  fileSave();
}

void pokeRemove() {
  int foundOnIndex = -1;

  int repeat = 1;
  do {
    do {
      int pokeIndexToRemove = 0;

      printf("\nDigite o número do Pokémon: ");
      scanf("%d", &pokeIndexToRemove);

      for (int i = 0; i < pokemonsOnPokedex; i++) {
        if (pokedex[i].pokedexNum == pokeIndexToRemove) {
          foundOnIndex = i;
        }
      }

      if (foundOnIndex == -1) {
        printf("Pokémon não encontrado, tente novamente.\n");
      }
    } while (foundOnIndex == -1);

    pokedex[foundOnIndex].pokedexNum = 100000;

    pokeSort(pokemonsOnPokedex);

    pokemonsOnPokedex--;

    printf("\nPokemon excluído com sucesso.\n");

    do {
      printf("\nVocê deseja excluir mais algum Pokémon?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);

  fileSave();
}

void pokeTrash() {
  int foundOnIndex = -1;

  int repeat = 1;
  do {
    pokePrintTable(0, pokemonsOnPokedex, 0);

    do {
      int pokeIndexToRemove = 0;

      printf("\nDigite o número do Pokémon para restaurar: ");
      scanf("%d", &pokeIndexToRemove);

      for (int i = 0; i < pokemonsOnPokedex; i++) {
        if (pokedex[i].pokedexNum == pokeIndexToRemove) {
          foundOnIndex = i;
        }
      }

      if (foundOnIndex == -1) {
        printf("Pokémon não encontrado, tente novamente.\n");
      }
    } while (foundOnIndex == -1);

    pokedex[foundOnIndex].isActive = 1;

    printf("\nPokemon restaurado com sucesso.\n");

    do {
      printf("\nVocê deseja restaurar mais algum Pokémon?\n");
      printf("1 - Sim\n2 - Não\n");

      scanf("%d", &repeat);

      if (repeat < 1 || repeat > 2)
        printf("\nOpção invalida! Tente novamente.\n");
    } while (repeat < 1 || repeat > 2);

  } while (repeat == 1);

  fileSave();
}

void pokeSort(int n) {
  if (n == 1)
    return;

  int count = 0;

  for (int i = 0; i < n - 1; i++)
    if (pokedex[i].pokedexNum > pokedex[i + 1].pokedexNum) {
      Pokemon temp = pokedex[i];
      pokedex[i] = pokedex[i + 1];
      pokedex[i + 1] = temp;

      count++;
    }

  if (count == 0)
    return;

  pokeSort(n - 1);
}

int pokeBinarySearch(int left, int right, int x) {
  if (right >= left) {
    int mid = left + (right - left) / 2;

    if (pokedex[mid].pokedexNum == x)
      return mid;

    if (pokedex[mid].pokedexNum > x)
      return pokeBinarySearch(left, mid - 1, x);

    return pokeBinarySearch(mid + 1, right, x);
  }

  return -1;
}

void pokePrintTable(int start, int end, int active) {
  printf(
      "\n"
      "┌─────┬────────────────┬────────┬─────────┬──────────┬────────────┐\n"
      "│ ID  │ Nome           │ Altura │ Peso    │ Tipo     │ Gênero     │\n"
      "├─────┼────────────────┼────────┼─────────┼──────────┼────────────┤\n");

  for (int i = start; i < end; i++) {
    if (active ? pokedex[i].isActive : !pokedex[i].isActive) {
      printf("│ ");
      printf("%3d", pokedex[i].pokedexNum);
      printf(" │ ");
      printf("%s", pokedex[i].pokeName);
      if (strlen(pokedex[i].pokeName) < 14)
        repeat(" ", 14 - strlen(pokedex[i].pokeName));
      printf(" │ ");
      if (pokedex[i].height < 10)
        repeat(" ", 1);
      printf(" %.2lf", pokedex[i].height);
      printf(" │ ");
      if (pokedex[i].weight < 10)
        repeat(" ", 1);
      if (pokedex[i].weight < 100)
        repeat(" ", 1);
      if (pokedex[i].weight < 1000)
        repeat(" ", 1);
      printf("%.2lf", pokedex[i].weight);
      printf(" │ ");
      printf("%s", pokedex[i].pokeType);
      if (strlen(pokedex[i].pokeType) < 8)
        repeat(" ", 8 - strlen(pokedex[i].pokeType));
      printf(" │ ");
      printf("%s", pokedex[i].gender);
      if (strlen(pokedex[i].gender) < 10)
        repeat(" ", 10 - strlen(pokedex[i].gender));
      printf(" │\n");
    }
  }

  printf(
      "└─────┴────────────────┴────────┴─────────┴──────────┴────────────┘\n");
}

void repeat(char *input, int count) {
  for (int i = 0; i != count; i++)
    printf("%s", input);
}
