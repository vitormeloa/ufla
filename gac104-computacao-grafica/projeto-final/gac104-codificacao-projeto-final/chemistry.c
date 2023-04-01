#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chemistry.h"

static struct {
    int n;
    Substance *subs;
} substances;

static struct {
    int n;
    Reaction *reacts;
} reactions;

static char *strip(char *s) {
    while (*s == ' ') s++;
    char *end = s;
    while (*end++ != '\0');
    while (*end-- == ' ' && end > s);
    if (end[0] == ' ') end[0] = '\0';
    return s;
}

static int htoi(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

static void parseSubstance(char *buf, Substance *sub) {
    char *pch = strtok(&buf[2], "|");
    pch = strip(pch);
    int namelen = strlen(pch);
    char *name = malloc(namelen + 1);
    strcpy(name, pch);
    sub->name = name;

    pch = strtok(NULL, "|");
    pch = strip(pch);
    int colorlen = strlen(pch);
    pch++;
    for (int i = 0; i < 4; i++, pch += 2) {
        if (pch[0] == 0 || pch[1] == 0) break;
        sub->color[i] = (htoi(pch[0]) * 16 + htoi(pch[1])) / 255.;
    }
}

int findSubstance(char *name) {
    for (int i = 0; i < substances.n; i++) {
        Substance *s = &substances.subs[i];
        if (strcmp(s->name, name) == 0) return i;
    }
    return -1;
}

static void parseReaction(char *buf, Reaction *react) {
    char *toks[] = {"+", "=", "|"};
    char *pch = strtok(&buf[2], toks[0]);

    int subs[3];
    for (int i = 0; i < 3; i++) {
        if (i > 0) pch = strtok(NULL, toks[i]);

        pch = strip(pch);
        subs[i] = findSubstance(pch);
        if (subs[i] == -1) {
            fprintf(stderr, "Reação com substância desconhecida: %s\n", pch);
            continue;
        }
    }

    pch = strtok(NULL, "|");
    pch = strip(pch);
    float time;
    sscanf(pch, "%f%*[s]", &time);

    react->subs[0] = subs[0];
    react->subs[1] = subs[1];
    react->result = subs[2];
    react->time = time * 1000;
}

void loadChemistry(char *filename) {
    char buf[256];
    FILE *file = fopen(filename, "r");

    substances.n = 0;
    reactions.n = 0;
    while (!feof(file)) {
        int v = fscanf(file, "%[^\n]%*c", buf);
        if (v == 0) {
            fgetc(file);
            continue;
        }
        if (v == EOF) break;

        if (strcmp("S: ", buf) < 0) {
            substances.n += 1;
        } else if (strcmp("R: ", buf) < 0) {
            reactions.n += 1;
        }
    }

    substances.subs = calloc(substances.n, sizeof(Substance));
    reactions.reacts = calloc(reactions.n, sizeof(Reaction));

    fseek(file, 0, SEEK_SET);
    for (int i = 0, j = 0; i < substances.n || j < reactions.n; ) {
        int v = fscanf(file, "%[^\n]%*c", buf);
        if (v == 0) {
            fgetc(file);
            continue;
        }
        if (v == EOF) break;

        if (strcmp("S: ", buf) < 0) {
            parseSubstance(buf, &substances.subs[i]);
            i++;
        } else if (strcmp("R: ", buf) < 0) {
            parseReaction(buf, &reactions.reacts[j]);
            j++;
        }
    }
}

void getSubstances(Substance **subs, int *n) {
    *subs = substances.subs;
    *n = substances.n;
}

void getReactions(Reaction **reacts, int *n) {
    *reacts = reactions.reacts;
    *n = reactions.n;
}

int findReaction(Substance *s1, Substance *s2) {
    int s1idx = s1 - substances.subs;
    int s2idx = s2 - substances.subs;
    for (int i = 0; i < reactions.n; i++) {
        int *subs = reactions.reacts[i].subs;
        if (subs[0] == s1idx && subs[1] == s2idx || subs[1] == s1idx && subs[0] == s2idx) {
            return i;
        }
    }
    return -1;
}
