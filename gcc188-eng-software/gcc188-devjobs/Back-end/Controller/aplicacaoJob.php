<?php

session_start();

$jobNome = $_POST['jobNome'];
$_SESSION['jobNome'] = $jobNome;

echo
"<!DOCTYPE html>

<html lang = 'pt-BR'>

    <head>
        <meta charset = 'UTF-8'>
        <meta http-equiv = 'X-UA-Compatible' content='IE=edge'>
        <meta name = 'viewport' content = 'width = device-width, initial-scale = 1.0'>
        <title>Aplicacao Job</title>
        <link rel = 'stylesheet' href = '../../Front-end/css/estilo.css'>
    </head>

    <body>
        <header id = 'header'>
            <nav class = 'container'>
                <a class = 'logo' href = '#'>Dev<span>Jobs</span></a>
            </nav>
        </header>

        <div class = 'loginBox'>

            <section class = 'section'>

                <div class = 'container grid'>

                    <form action = '../../Back-end/Controller/cadastrarAplicacao.php' method = 'POST' autocomplete = 'off'>
                        <br>
                        <br>
                        <h1>Aplicar Currículo</h1>
                        <p>Informe o currículo que você deseja usar para aplicar sua candidatura a esta vaga:</p>
                        <br>

                        <div class = 'userBox'>
                            <label for = 'curriculoNome'>*Nome do Currículo:</label>
                            <br>
                            <br>
                            <input type = 'text' name = 'curriculoNome' placeholder = 'Mesmo nome usado no cadastro do currículo' required>
                            <br>
                        </div>

                        <div class = 'userBox'>
                            <label for = 'motivo'>Motivo:</label>
                            <br>
                            <br>
                            <textarea name = 'motivo' placeholder = 'Pequena descricao sobre o motivo da aplicacao!'></textarea>
                            <br>
                        </div>

                        <div class = 'userBox'>
                            <label for = 'aplicacaoNome'>*Nome da Aplicação:</label>
                            <br>
                            <br>
                            <input type = 'text' name = 'aplicacaoNome' placeholder = 'Dê um nome único :D' required>
                            <br>
                        </div>

                        <div class = 'userBox'>
                            <br>
                            <button class = 'button' type = 'submit'>Aplicar</button>
                            <br>
                        </div>

                    </form>

                </div>

            </section>

        </div>

    </body>

</html>";

?>