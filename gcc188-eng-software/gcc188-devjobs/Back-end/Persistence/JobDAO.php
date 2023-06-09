<?php

class JobDAO
{
    function __construct(){}

    function cadastrarJob($job, $connection)
    {
        $inserirJob = "INSERT INTO Jobs(descricao, requisitos, beneficios, salario, remoto, qtdVagas, cpfContratante, jobNome) VALUES ('" . $job->getDescricao() . "','" . $job->getRequisitos() . "','" . $job->getBeneficios() . "'," . $job->getSalario() . ",'" . $job->getRemoto() . "'," . $job->getQtdVagas() . ",'" . $job->getCpfContratante() . "','" . $job->getJobNome() . "')";

        if($connection->query($inserirJob) == TRUE)
        {
            echo "Job inserido com sucesso!";
            header("Location: ../../Front-end/views/jobsContratante.html");
        }
        else
        {
            echo "Erro no cadastramento: " . $connection->error;
            header("Location: ../../Front-end/views/cadastrarJob.html");
        }
    }

    function excluirJob($jobNome, $connection)
    {
        $excluirJob = "DELETE FROM Jobs WHERE jobNome = '" . $jobNome . "'";

        if($connection->query($excluirJob) == TRUE)
        {
            echo "Job excluído com sucesso!";
            header("Location: ../../Front-end/views/jobsContratante.html");
        }
        else
        {
            echo "Erro na Exclusao: " . $connection->error;
            header("Location: ../../Front-end/views/jobsContratante.html");
        }
    }

    function alterarJob($job, $connection)
    {
        $alterarJob = "UPDATE Jobs SET qtdVagas = " . $job->getQtdVagas() . ", descricao = '" . $job->getDescricao() . "', requisitos = '" . $job->getRequisitos() . "', beneficios = '" . $job->getBeneficios() . "', salario = " . $job->getSalario() . ", remoto = '" . $job->getRemoto() . "' WHERE jobNome = '" . $job->getJobNome() . "'";
        return $connection->query($alterarJob);
    }

    function consultarJob($jobNome, $connection)
    {
        $consultarJob = "SELECT * FROM Jobs WHERE jobNome = '" . $jobNome . "'";
        $job = $connection->query($consultarJob);
        return $job;
    }

    function consultarTodosJobs($cpf, $connection)
    {
        $consultarJobs = "SELECT * FROM Jobs WHERE cpfContratante = '" . $cpf . "'";
        $jobs = $connection->query($consultarJobs);
        return $jobs;
    }

    function jobsDisponiveis($connection)
    {
        $consultarJobs = "SELECT * FROM Jobs";
        $jobsDisponiveis = $connection->query($consultarJobs);
        return $jobsDisponiveis;
    }

}

?>