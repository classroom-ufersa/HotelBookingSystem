
typedef struct hospede Hospede;

typedef struct quarto Quarto;

Hospede *inicializa_reserva(void);

Hospede *cria_reserva(Hospede *h, Quarto *q, char nome[81], int estadia, int quantidade, float documento);

int destruir_reserva(Hospede *h);

void imprime_reserva(Hospede *h);

void consulta_quantitativo(Hospede *h);

Hospede *busca_reserva(int numero, Hospede *h);

Hospede *exclui_reserva(Hospede *h, int numero);

void libera_reserva(Hospede *h);

void escreve_lista(Hospede *h);

Hospede * ler_lista(Hospede *h, Quarto **q);

Hospede * editar_reserva(Hospede * h, Quarto **q);
