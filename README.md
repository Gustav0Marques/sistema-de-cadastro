# Sistema de Cadastro de Clientes

Programa de linha de comando em C para cadastrar e consultar clientes.

## Funcionalidades

- Cadastrar clientes com nome, empresa, e-mail, telefone, CPF, endereco e aniversario.
- Atualizar ou excluir um cliente.
- Listar clientes e pesquisar por empresa ou nome.
- Consultar aniversariantes por mes e gerar relatorios estatisticos.

Os dados ficam na memoria enquanto o programa esta em execucao. Ao fechar o programa, os cadastros nao sao salvos.

## Compilar e executar

Com o GCC instalado, abra o PowerShell nesta pasta e execute:

```powershell
gcc sistema_cadastro.c -o sistema_cadastro.exe
.\sistema_cadastro.exe
```

O programa permite cadastrar ate 100 clientes por execucao.
