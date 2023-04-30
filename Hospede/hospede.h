
typedef struct hospede Hospede;

Hospede * inicializa_reserva(void);

Hospede * cria_reserva(char nome[81], int estadia, float documento, int numero, Hospede **h);

int destruir_reserva(Hospede *h);

void imprime_reserva(Hospede *h);

Hospede * busca_reserva(int numero, Hospede * h);

Hospede * exclui_reserva(Hospede * h, int numero);

void libera_reserva(Hospede * h);