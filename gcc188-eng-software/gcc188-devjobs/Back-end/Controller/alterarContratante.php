<?php

$cpf = $_POST['cpf'];
$nome = $_POST['nome'];
$email = $_POST['email'];
$senha = $_POST['senha'];
$dataNasc = $_POST['dataNasc'];
$telefone = $_POST['telefone'];
$nomeEmpresa = $_POST['nomeEmpresa'];
$cnpj = $_POST['cnpj'];
$dataAberturaEmpresa = $_POST['dataAberturaEmpresa'];

echo "<!DOCTYPE html>

    <html lang='pt-BR'>

        <head>
            <meta charset='UTF-8'>
            <meta http-equiv='X-UA-Compatible' content='IE=edge'>
            <meta name='viewport' content='width=device-width, initial-scale=1.0'>
            <title>Perfil|DevJobs</title>
            <link rel='stylesheet' href='../../Front-end/css/estilo.css'>
        </head>

        <body>
            <header id='header'>
                <nav class='container'>
                    <a class='logo' href='#'>Dev<span>Jobs</span></a>
                </nav>
            </header>

            <div class='loginBox'>

                <div class = 'perfilBox'>

                    <section class='section'>

                        <div class='container grid'>

                            <form action = 'alterarContratanteDefinitivo.php' method = 'POST'>

                                <h1>Alterar Perfil</h1>

                                <div class = 'userBox'>
                                    <label for = 'cpf'>CPF:</label>
                                    <br>
                                    <input type = 'text' name = 'cpf' value = '" . $cpf . "' pattern = '\d{3}\.?\d{3}\.?\d{3}-?\d{2}' hidden>
                                    <input type = 'text' name = 'cpf' value = '" . $cpf . "' pattern = '\d{3}\.?\d{3}\.?\d{3}-?\d{2}' disabled>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <label for = 'nome'>Nome Completo:</label>
                                    <br>
                                    <input type = 'text' name = 'nome' value = '" . $nome . "'>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'email'>Email:</label>
                                    <br>
                                    <input type = 'email' name = 'email' value = '" . $email . "'>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'senha'>Senha:</label>
                                    <br>
                                    <input type = 'password' name = 'senha' value = '" . $senha . "'>
                                    <br>
                                </div>
                                
                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'telefone'>Telefone:</label>
                                    <br>
                                    <input type='phone' name = 'telefone' value = '" . $telefone . "'>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'dataNasc'>Data de Nascimento:</label>
                                    <br>
                                    <input type = 'date' name = 'dataNasc' value = '" . $dataNasc . "' hidden>
                                    <input type = 'date' name = 'dataNasc' value = '" . $dataNasc . "' disabled>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'nomeEmpresa'>Nome Empresa:</label>
                                    <br>
                                    <input type = 'text' name = 'nomeEmpresa' value = '" . $nomeEmpresa . "'>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'cnpj'>CNPJ:</label>
                                    <br>
                                    <input type = 'text' name = 'cnpj' value = '" . $cnpj . "' hidden>
                                    <input type = 'text' name = 'cnpj' value = '" . $cnpj . "' disabled>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <label for = 'dataAberturaEmpresa'>Data de Abertura da Empresa:</label>
                                    <br>
                                    <input type = 'date' name = 'dataAberturaEmpresa' value = '" . $dataAberturaEmpresa . "' hidden>
                                    <input type = 'date' name = 'dataAberturaEmpresa' value = '" . $dataAberturaEmpresa . "' disabled>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <button class='button' type='submit'>Alterar</button>
                                    <br>
                                </div>

                                <div class = 'userBox'>
                                    <br>
                                    <a href = '../../Front-end/views/mostrarPerfil.html' class = 'button' type = 'submit'>Voltar</a>
                                </div>

                            </form>

                        </div>

                    </section>

                </div>
                
            </div>

        </body>

    </html>";

?>