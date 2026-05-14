#include <stdio.h>

int main() {
    // Declaração de variáveis
    char nome[64];
    int tipo_usuario;
    int hora_inicio;
    int duracao_min;
    double energia_kwh = 0.0;
    double custo_bruto = 0.0;
    double desconto = 0.0;
    double custo_final = 0.0;
    int minuto, hora_atual;
    double tarifa_minuto;

    // Cabeçalho principal
    printf("====================================================\n");
    printf("   SIMULADOR DE SESSÃO DE RECARGA - ELETROCHARGE\n");
    printf("====================================================\n\n");

    
    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", nome);


    printf("\nSelecione o tipo de usuário:\n");
    printf("1 - Padrão\n");
    printf("2 - Premium (15%% de desconto)\n");
    printf("Escolha uma opção:\n");
    scanf("%d", &tipo_usuario);

    // Validação da opção do usuário
    while (tipo_usuario < 1 || tipo_usuario > 2) {
        printf("Opção inválida! Escolha uma opção (1 ou 2):\n");
        scanf("%d", &tipo_usuario);
    }

    // Estrutura switch-case similar ao modelo aprendido
    switch (tipo_usuario) {
        case 1:
            printf("Perfil selecionado: Padrão\n\n");
            break;
        case 2:
            printf("Perfil selecionado: Premium\n\n");
            break;
    }

    // Coleta e validação da hora de início
    printf("Hora de início da recarga (0-23): ");
    scanf("%d", &hora_inicio);
    while (hora_inicio < 0 || hora_inicio > 23) {
        printf("Hora inválida! Digite a hora novamente (0-23): ");
        scanf("%d", &hora_inicio);
    }

    // Coleta e validação da duração
    printf("Duração desejada em minutos (1-480): ");
    scanf("%d", &duracao_min);
    while (duracao_min < 1 || duracao_min > 480) {
        printf("Duração inválida! Digite a duração novamente (1-480): ");
        scanf("%d", &duracao_min);
    }

    printf("\n----------------------------------------------------\n");
    printf("Iniciando sessão de recarga...\n");
    printf("----------------------------------------------------\n");

    // Simulação do carregamento minuto a minuto
    for (minuto = 1; minuto <= duracao_min; minuto++) {
       
        hora_atual = (hora_inicio + (minuto - 1) / 60) % 24;

        // Definição da tarifa com base no horário
        if (hora_atual >= 18 && hora_atual < 22) {
            tarifa_minuto = 1.20; // Horário de Pico
        } else if (hora_atual >= 22 || hora_atual < 6) {
            tarifa_minuto = 0.45; // Horário Noturno
        } else {
            tarifa_minuto = 0.75; // Horário Padrão
        }

       
        energia_kwh += 0.10;
        custo_bruto += 0.10 * tarifa_minuto;
    }

    // Cálculo de descontos e total
    if (tipo_usuario == 2) {
        desconto = custo_bruto * 0.15;
    } else {
        desconto = 0.0;
    }
    custo_final = custo_bruto - desconto;

    
    int hora_fim = (hora_inicio + duracao_min / 60) % 24;
    int min_fim  = duracao_min % 60;

    // Exibição do Relatório Final
    printf("\n====================================================\n");
    printf("              RELATÓRIO DA SESSÃO\n");
    printf("====================================================\n");
    printf("Usuário      : %s\n", nome);
    printf("Perfil       : %s\n", tipo_usuario == 2 ? "Premium" : "Padrão");
    printf("----------------------------------------------------\n");
    printf("Início       : %02d:00\n", hora_inicio);
    printf("Duração      : %d min  (término aprox. %02d:%02d)\n", duracao_min, hora_fim, min_fim);

    // Identifica e exibe a faixa tarifária inicial
    printf("Faixa tarifária inicial : ");
    if (hora_inicio >= 18 && hora_inicio < 22) {
        printf("Pico (R$ 1.20/kWh)\n");
    } else if (hora_inicio >= 22 || hora_inicio < 6) {
        printf("Noturna (R$ 0.45/kWh)\n");
    } else {
        printf("Padrão (R$ 0.75/kWh)\n");
    }
    printf("----------------------------------------------------\n");

    printf("Energia carregada : %.3f kWh\n", energia_kwh);
    printf("Custo bruto       : R$ %.2f\n", custo_bruto);

    if (tipo_usuario == 2) {
        printf("Desconto Premium  : R$ %.2f  (15%%)\n", desconto);
    }

    printf("TOTAL A PAGAR     : R$ %.2f\n", custo_final);
    printf("====================================================\n");

    // Mensagem final baseada no valor gasto
    if (custo_final < 10.0) {
        printf("Sessão econômica! Bom proveito.\n");
    } else if (custo_final < 50.0) {
        printf("Sessão concluída com sucesso.\n");
    } else {
        printf("Sessão longa. Considere recargas parciais.\n");
    }
    printf("====================================================\n");

    return 0;
}