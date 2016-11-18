#include <stdio.h>

/* Transaction string length */
#define TRANSACTION_STRING_LENGTH   256

/* Max number of running transactions */
#define MAX_TRANSACTIONS            4096

/* Transaction status */
#define STATUS_UNDEFINED            1
#define STATUS_RUNNING              2
#define STATUS_COMMITED             3

struct ui_list {
  unsigned int elements[MAX_TRANSACTIONS];
  unsigned int size;
};

int check_seriability() {
  return 0;
}

void init_list(struct ui_list *list) {
  list->size = 0;
}

void insert(struct ui_list *list, unsigned int element) {
  list->elements[list->size++] = element;
}

void delete(struct ui_list *list, unsigned int element) {
  unsigned int i, j;

  for(i = 0; i < list->size; ++i) {
    if(list->elements[i] == element) {
      for(j = i; j < list->size - 1; ++j) {
        list->elements[j] = list->elements[j + 1];
      }

      --list->size;
    }
  }
}

int contains(struct ui_list *list, unsigned int element) {
  unsigned int i;

  for(i = 0; i < list->size; ++i) {
    if(list->elements[i] == element) {
      return 1;
    }
  }

  return 0;
}

int empty(struct ui_list *list) {
  return (list->size == 0);
}

int main(int argc, const char *argv[]) {
  char transaction_string[TRANSACTION_STRING_LENGTH];
  struct ui_list running_transactions;
  char operation, attribute;
  unsigned int time, transaction, sptr, i;
  unsigned int scheduling_counter = 1;

  init_list(&running_transactions);

  while(fscanf(stdin, "%u %u %c %c", &time, &transaction, &operation, &attribute) != EOF) {
    if(contains(&running_transactions, transaction) == 0) {
      insert(&running_transactions, transaction);

      sptr = snprintf(transaction_string, sizeof transaction_string, "%u", running_transactions.elements[0]);
      for(i = 1; i < running_transactions.size; ++i) {
        sptr += snprintf(transaction_string + sptr, sizeof transaction_string, ",%u", running_transactions.elements[i]);
      }

      transaction_string[sptr] = '\0';
    }

    if(operation == 'C') {
      delete(&running_transactions, transaction);

      if(empty(&running_transactions)) {
        fprintf(stdout, "%u %s %s\n", scheduling_counter, transaction_string, (check_seriability() == 0) ? ("NAO") : ("SIM"));
        transaction_string[0] = '\0';
        ++scheduling_counter;
      }
    }
  }

  return 0;
}
