<?php

require 'Slim/Slim.php';

include 'conexao.php';
include 'account.php';
include 'phrase.php';
include 'deck.php';


    \Slim\Slim::registerAutoloader();

    $app = new \Slim\Slim();

    $app->response()->header('Content-Type', 'application/json;charset=utf-8');

    $app->get('/', function () {

        echo "It's work!";
    });


    $app->get('/deck/:id','getDeck');
    $app->post('/deck','addDeck');
    $app->post('/deletedeck','deleteDeck');
    $app->post('/updatedeck','updateDeck');

    $app->get('/phrase/:id','getPhrase');
    $app->post('/addphrase','addPhrase');
    $app->post('/deletephrase','deletePhrase');
    $app->post('/updatephrase','updatePhrase');

    $app->get('/user/:id','getUser');
    $app->post('/deleteuser','deleteUser');
    $app->post('/adduser','addUser');

    $app->post('/login','logIn');

    $app->run();
