# trabalhoCPP2
 
Elabore   um  programa  que   permita  a  gerência  de  sócios   e  dependentes   de   um determinado clube.

    - Funcionalidades:
    1.Cadastro   e   manutenção   de   dados   de   associados   –   lembrando   que   um associado pode ter 
    mais de um dependente;
    2.Cadastro e manutenção de dados dependentes;
    3.Cadastro e manutenção de dados visitantes – devem estar sempre ligados a um associado;
    4.Aviso automático quando dependente atinge maioridade;
    5.Registro de visita;
    6.Relatório de dependentes/associados – gere uma consulta e liste os dados na tela;
    7.Relatório de visitas por associado – gera a consulta e liste os dados na tela;
    
    - Sugestão de estruturas:
        - Pessoa – cpf, nome, data_nasc, endereço, sexo, telefone, e-mail;
        - Associado    –   código   (auto   incremento),   cpf,   data_associação,tipo_socio(proprietário ou contribuinte), 
        mensalidade ( este valor depende daqtde de dependentes taxa 200 + 30 por dependente);
        - Dependente  – código (auto incremento), codExterno (ano associação + valorcampo código), cpf_associado, nome, 
        data_nasc, sexo;
        - Visitante - código (auto incremento), cpf, código_associado, nome, data_nasc,sexo, data_visita_inicial, 
        data_visita_final;
    
    - Considerações: O programa deve oferece um menu que só será finalizado quando o usuário optar por encerrar o programa.
    Deverão ser usadas ao menos 5 funções, dessas ao menos 2 deverão usar passagem de parâmetro por referências. 
    Para que se possa fazer alteração e exclusão de registros será necessário efetuar buscas. Os dados serão armazenados 
    em arquivos.

