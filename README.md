# Compétition d'algo — ENSISA 1A

Dépôt d'équipe pour préparer et résoudre les problèmes d'une compétition d'algorithmique (format HackerRank : lecture sur l'entrée standard, réponse sur la sortie standard).

## Contenu

| Fichier | Problème |
|---|---|
| `infiniteLabrary.c` | Infinite Library (squelette fourni, à compléter) |

## Compiler et tester (C)

```sh
gcc -Wall -Wextra -O2 -o infiniteLabrary infiniteLabrary.c -lm
./infiniteLabrary < entree.txt
```

Les exécutables (`*.exe`, `a.out`, …) sont ignorés par git : ne committer que les sources.

## Travailler à plusieurs

1. `git pull` avant de commencer.
2. Une branche par problème ou par personne : `git switch -c nom-du-probleme`.
3. Commits petits et clairs, puis `git push -u origin nom-du-probleme`.
4. Ouvrir une Pull Request sur GitHub pour fusionner dans `main`.
