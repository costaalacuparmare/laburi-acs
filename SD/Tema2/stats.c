#include "quadtree.h"

int nrLvs(TQuad qtree) {
	if (!qtree)
		return 0;
	int nr_tL = nrLvs(qtree->topL);
	int nr_tR = nrLvs(qtree->topR);
	int nr_bL = nrLvs(qtree->botL);
	int nr_bR = nrLvs(qtree->botR);
	int nr_t = MAX(nr_tL,nr_tR);
	int nr_b = MAX(nr_bL,nr_bR);
	return 1 + MAX(nr_t ,nr_b);
}

void nrLeafs (TQuad qtree, int *nr_lfs) {
	if (!qtree)
		return;
	if (qtree->type)
		(*nr_lfs)++;
	nrLeafs(qtree->topL, nr_lfs);
	nrLeafs(qtree->topR, nr_lfs);
	nrLeafs(qtree->botL, nr_lfs);
	nrLeafs(qtree->botR, nr_lfs);
}

int highLeaf (TQuad qtree, int lvl) {
	if (!qtree)
		return 0;
	if (qtree->type) {
		return lvl;
	}
	int min_tL = highLeaf(qtree->topL, lvl + 1);
	int min_tR = highLeaf(qtree->topR, lvl + 1);
	int min_bR = highLeaf(qtree->botR, lvl + 1);
	int min_bL = highLeaf(qtree->botL, lvl + 1);
	int min_t = MIN(min_tL, min_tR);
	int min_b = MIN(min_bL, min_bR);
	return MIN(min_t, min_b);
}

void stats(TQuad qtree, FILE *output, unsigned int size) {
	fprintf(output, "%d\n", nrLvs(qtree));
	int nr_lfs = 0;
	nrLeafs(qtree,&nr_lfs);
	fprintf(output, "%d\n", nr_lfs);
	int lvl = highLeaf(qtree, 0);
	int div = 1;
	for (int i = 0; i < lvl; i++)
		div *= 2;
	fprintf(output, "%d\n", size/div);
}