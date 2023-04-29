#include "quadtree.h"

int nrLvs(TQuad qtree) {
	int nr_tL = 0;
	int nr_tR = 0;
	int nr_bL = 0;
	int nr_bR = 0;
	if (!qtree)
		return 0;
	nr_tL = nrLvs(qtree->topL);
	nr_tR = nrLvs(qtree->topR);
	nr_bL = nrLvs(qtree->botL);
	nr_bR = nrLvs(qtree->botR);
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

int maxLength (TQuad qtree, int niv, int size) {
	if (!qtree)
		return 0;
	if (qtree->type) {
		return niv;
	}
	maxLength(qtree->topL, niv + 1, size);
	maxLength(qtree->topR, niv + 1, size);
	maxLength(qtree->botR, niv + 1, size);
	maxLength(qtree->botL, niv + 1, size);
}

void task1(TQuad qtree, FILE *output, unsigned int size) {
	fprintf(output, "%d\n", nrLvs(qtree));
	int nr_lfs = 0;
	nrLeafs(qtree,&nr_lfs);
	fprintf(output, "%d\n", nr_lfs);
	fprintf(output, "%d\n", maxLength(qtree, 0, size));
}