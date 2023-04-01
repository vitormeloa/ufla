# Projeto da Disciplina Sistemas Distribuídos

### Este projeto tem por objetivo criar uma aplicação que consuma uma API em node.js

## Como executar o projeto

1. Instale o Node.js, NPM, Mongodb, Mongodb Compass e o Insomnia.
2. Abra o diretório src em um terminal.
3. Rode o comando "npm install". Sem aspas.
4. Rode o comando "npm run serve". Sem aspas.
5. Tenha aberto o Mongodb e o Insomnia.
6. No Insomnia, crie requisições do tipo GET, POST, PUT e DELETE.
7. Use a URL: http://localhost:3000/tasks como base para todas as requisições. Nas requisições de PUT e DELETE, é obrigatório o uso de um ID após tasks, ficando: http://localhost:3000/tasks/{ID}, onde ID é um atributo dos objetos tasks no banco. Caso seja feita uma requisição GET com um ID no final, http://localhost:3000/tasks/{ID}, o retorno será o objeto com aquele ID.
