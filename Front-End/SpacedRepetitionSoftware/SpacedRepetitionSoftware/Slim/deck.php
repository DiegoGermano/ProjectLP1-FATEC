<?php

function deleteDeck()
{
	$request = \Slim\Slim::getInstance()->request();

    $id = json_decode($request->getBody());

    $sql = "DELETE FROM deck WHERE id = ".$id." OR 0 = ".$id;

    $conn = getConn();
    $stmt = $conn->prepare($sql);
    $stmt->execute();

    print_r($stmt->errorInfo());
}


function getDeck($id)
{
    $stmt = getConn()->query("SELECT * FROM deck WHERE User_id = ".$id." OR -1 = ".$id);

    $deck = $stmt->fetchAll(PDO::FETCH_OBJ);
    echo json_encode($deck);   
}

function updateDeck()
{
	print_r("not implemented yet! :(");
}

function addDeck()
{

	$request = \Slim\Slim::getInstance()->request();
	$deck = json_decode($request->getBody());

	verifyIfDeckIsValid($deck);

	$sql = "INSERT INTO deck (description,activated, language_id,user_id) values (:description,1,:language_id,:user_id) ";

    $conn = getConn();

    $stmt = $conn->prepare($sql);

	$stmt->bindParam("description",$deck->description);
    $stmt->bindParam("language_id",$deck->language_id);
	$stmt->bindParam("user_id",$deck->user_id);
    $stmt->execute();

    $deck->id = $conn->lastInsertId();

    echo json_encode($deck);   
}

function verifyIfDeckIsValid($deck)
{
	$result = "";
    
    if(strlen($deck->description) < 1)
    	$result = "\n Description shouldn't be empty";

    $stmt = getConn()->query("SELECT Count(*) as count FROM user WHERE id = '".$deck->user_id."' ");

    $value = $stmt->fetchAll(PDO::FETCH_OBJ);

    if($value[0]->count <= 0)
        $result .= "\n User id is invalid";

 	if(strlen($result) > 0)
    {
        print_r($result);
        exit();
    }

}

