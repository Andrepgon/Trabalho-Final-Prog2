#ifndef PESSOA_H
#define PESSOA_H

#include "biblioteca.h"

typedef struct {
    char *nome;
    char *cpf;
    LIVRO *livro_emprestado;
    size_t count_livros_emprestados;
} PESSOA;

#ifdef PESSOA_IMPLEMENTATION

PESSOA *cria_PESSOA(const char *nome, const char *cpf)
{
    /** 
     * Retorna uma alocacao dinamica de uma estrutura PESSOA 
     */ 
    PESSOA *p = (PESSOA*) malloc(sizeof(PESSOA));

    if (p == NULL) {
        #ifdef DEBUG
            print_error(MALLOC_ERR);
        #else   
            perror("Erro ao alocar memoria");
        #endif
        return false;
    }

    p->nome = strdup(nome);
    p->cpf = strdup(cpf);
    p->livro_emprestado = NULL;
    p->count_livros_emprestados = 0;
    return p;
}

bool empresta_Livro(PESSOA *p, LIVRO *l)
{   
    /**
     * A funcao empresta livro define o endereco do livro emprestado como um 
     * dos campos do usuario, e define o livro como indisponivel
     * 
     * Cada pessoa so pode ter apenas 1 livro emprestado por vez
     * Caso ja tenha um, nao vai conseguir pegar outro 
     * Caso o livro nao esteja disponivel, tambem nao vai conseguir pegar emprestado
     */
    if (p->count_livros_emprestados > 0) {
        fprintf(stdout, "%s\n", "Voce ja tem um livro emprestado, devolva-o antes de pegar outro");
        return false;
    }
    if(!l->disponivel) {
        fprintf(stdout, "%s\n", "O livro nao esta disponivel para emprestimo");
        return false;
    }

    p->livro_emprestado = l;
    l->disponivel = false;
    p->count_livros_emprestados++;

    return true; 
}

bool devolve_Livro(PESSOA *p)
{
    /**
     * Operacao inversa da empresta_LIVRO, caso nao tenha nenhum livro
     * emprestado, a funcao avisa e retorna falso, de resto, ela devolve
     * o livro emprestado
     */
    if (p->livro_emprestado == NULL) {
        fprintf(stdout, "%s\n", "Voce nao tem nenhum livro emprestado no momento");
        return false;
    }

    p->livro_emprestado->disponivel = true;
    p->livro_emprestado = NULL;
    p->count_livros_emprestados = 0;
    return true;
}

#endif // PESSOA_IMPLEMENTATION

#endif // PESSOA_H