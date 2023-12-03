# Trabalho Algoritmo e Estrutura de Dados II
 
## Elabore um programa que permita a gerência de sócios e dependentes de um determinado clube.

### Funcionalidades:
- Cadastro e manutenção de dados de associados – lembrando que um associado pode ter mais de um dependente;
- Cadastro e manutenção de dados dependentes;
- Cadastro e manutenção de dados visitantes – devem estar sempre ligados a um associado;
- Aviso automático quando dependente atinge maioridade;
- Registro de visita;
- Relatório de dependentes/associados – gere uma consulta e liste os dados na tela;
- Relatório de visitas por associado – gera a consulta e liste os dados na tela;
    
### Sugestões de estruturas:
- Pessoa: cpf, nome, data_nasc, endereço, sexo, telefone, e-mail;
- Associado: código (auto incremento), cpf, data_associação, tipo_socio(proprietário ou contribuinte), mensalidade (este valor depende da qtde de dependentes taxa 200 + 30 por dependente);
- Dependente: código (auto incremento), codExterno (ano associação + valorcampo código), cpf_associado, nome, data_nasc, sexo;
- Visitante: código (auto incremento), cpf, código_associado, nome, data_nasc,sexo, data_visita_inicial, data_visita_final;

### - Considerações: O programa deve oferece um menu que só será finalizado quando o usuário optar por encerrar o programa.
### - Deverão ser usadas ao menos 5 funções, dessas ao menos 2 deverão usar passagem de parâmetro por referências. 
### - Para que se possa fazer alteração e exclusão de registros será necessário efetuar buscas. Os dados serão armazenados em arquivos.