<?php

function deletePhrase()
{
	$request = \Slim\Slim::getInstance()->request();

    $id = json_decode($request->getBody());

    $sql = "DELETE FROM word WHERE id = ".$id." OR -1 = ".$id;

    print_r($sql);

    $conn = getConn();
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    print_r($stmt->errorInfo());
}


function getPhrase($id)
{
    $stmt = getConn()->query("SELECT * FROM Word WHERE deck_id = ".$id." OR 0 = ".$id);
    $phrase = $stmt->fetchAll(PDO::FETCH_OBJ);
    echo json_encode($phrase);
}

function updatePhrase()
{
	print_r("not implemented yet! :(");
}

function addPhrase()
{

	$request = \Slim\Slim::getInstance()->request();
	$phrase = json_decode($request->getBody());

	verifyIfPharseIsValid($phrase);

	$sql = "INSERT INTO Word (back,front, deck_id) values (:back,:front,:deck_id) ";

    $conn = getConn();

    $stmt = $conn->prepare($sql);

	$stmt->bindParam("back",$phrase->back);
    $stmt->bindParam("front",$phrase->front);
	$stmt->bindParam("deck_id",$phrase->deck_id);
    $stmt->execute();

    $phrase->id = $conn->lastInsertId();

    echo json_encode($phrase);   
}

function verifyIfPharseIsValid($phrase)
{
	$result = "";
    
    if(strlen($phrase->front) < 1)
    	$result = "\n front shouldn't be empty";

    $stmt = getConn()->query("SELECT Count(*) as count FROM deck WHERE id = '".$phrase->deck_id."' ");

    $value = $stmt->fetchAll(PDO::FETCH_OBJ);

    if($value[0]->count <= 0)
        $result .= "\n Deck id is invalid";

 	if(strlen($result) > 0)
    {
        print_r($result);
        exit();
    }
}

