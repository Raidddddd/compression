#ifndef COMPRESSION_H_
#define COMPRESSION_H_

void occurence (uint8_t* chaine , uint32_t tab[256]);
struct noeud{
	uint16_t c;
	uint32_t occurence;
	uint32_t code;
	uint32_t tailleCode;
	struct noeud *gauche,*droite;

};

void printTree(struct noeud *node, int depth);
void creerFeuille(struct noeud *arbre[256], uint32_t tab[256]);
void afficheOccurence (uint32_t tab[256]);

void AfficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);

void triArbre(struct noeud* arbre[256], uint32_t taille);
struct noeud* racine(struct noeud* arbre[256], uint32_t taille);
void parcourirArbre(struct noeud* ptrNoeud);

#endif
