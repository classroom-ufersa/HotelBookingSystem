typedef struct quarto Quarto;

Quarto *captura_quartos(int n, char disp[81], float preco, char local[81]);

void exibir_quartos(Quarto **q);

void escreve_quarto(Quarto **quartos);

int verifica_quarto(Quarto **q, int numero);

char *transforma_nome(char *nome);

void exibir_quartos_disponiveis(Quarto **q);

void exibir_quartos_ocupados(Quarto **q);

void LimpaBuffer(void);

int LeInteiro(void);