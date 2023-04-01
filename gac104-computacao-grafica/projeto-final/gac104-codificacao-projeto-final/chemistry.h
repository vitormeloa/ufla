#pragma once

typedef struct {
    char *name;
    float color[4];
} Substance;

typedef struct {
    int subs[2];
    int result;
    int time;
} Reaction;

void loadChemistry(char *filename);
void getSubstances(Substance **subs, int *n);
void getReactions(Reaction **reacts, int *n);
int findSubstance(char *name);
int findReaction(Substance *s1, Substance *s2);
