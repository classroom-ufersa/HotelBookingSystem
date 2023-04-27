typedef struct quarto Quarto;

typedef struct hospede Hospede;

Quarto * inicializa_quartos(int i);

void exibir_quartos(Quarto * q[]);

Hospede * inicializa_reserva(void);

Hospede * cria_reserva(char nome[81], int estadia, float documento, Hospede *h);