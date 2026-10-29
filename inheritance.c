// Simulate genetic inheritance of blood type
#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srandom(time(0));

    // Create a family with three generations
    person *p = create_family(GENERATIONS);

    // Print the family tree
    print_family(p, 0);

    // Free the memory
    free_family(p);
}

  person *create_family(int generations)
{
    // Create memory for a new person
    person *new_person = malloc(sizeof(person));

    // Check if memory allocation failed
    if (new_person == NULL)
    {
        return NULL;
    }


    // Create parents if more generations are needed
    if (generations > 1)
    {
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        if (parent0 == NULL || parent1 == NULL)
        {
            free_family(parent0);
            free_family(parent1);
            free(new_person);
            return NULL;
        }

        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // Get one allele from each parent
        new_person->alleles[0] = parent0->alleles[random() % 2];
        new_person->alleles[1] = parent1->alleles[random() % 2];
    }
    else
    {
        // Base case: no parents
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    return new_person;
}



// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // Base case: stop if person is NULL
    if (p == NULL)
    {
        return;
    }

    // Free both parents first
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free the current person last
    free(p);
}


// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = random() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
