<?php

	require '../Slim/Slim/Slim.php';
	include 'conexao.php';


	\Slim\Slim::registerAutoloader();

	$app = new \Slim\Slim();

	$app->response()->header('Content-Type', 'application/json;charset=utf-8');

	$app->get('/', function () {

		echo "It's work!";

	});

	$app->get('/frases','getFrases');

	$app->run();



function getFrases()
{
	$stmt = getConn()->query("SELECT * FROM Word");
	$Word = $stmt->fetchAll(PDO::FETCH_OBJ);
	echo "{Word:".json_encode($Word)."}";
	
}

?>