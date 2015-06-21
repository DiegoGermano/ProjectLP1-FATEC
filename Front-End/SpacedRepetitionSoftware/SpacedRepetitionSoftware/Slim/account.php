<?php
	
class User {

	public $Id;
	public $Password;
	public $Email;
	public $Name;

	public $Contacts = array();	
}

class Contact {

	public $Id;
	public $Description;
	public $Value;
	public $UserId;
}

function deleteUser()
{
    $request = \Slim\Slim::getInstance()->request();

    $id = json_decode($request->getBody());
    
    $sql = "DELETE FROM User WHERE id = ".$id." OR 0 = ".$id;
    $conn = getConn();
    $stmt = $conn->prepare($sql);
    $result = $stmt->execute();
}

function getUser($id)
{
    $stmt = getConn()->query("SELECT * FROM User WHERE id = ".$id." OR 0 = ".$id);
    $user = $stmt->fetchAll(PDO::FETCH_OBJ);
    echo json_encode($user);
}

function verifyIfUserIsValid($user)
{
    $result = "";
    
    if(strlen($user->password) < 5)
        $result .= "\n password should be greater than 5 characters";

    if(strlen($user->name) < 3)
        $result .= "\n name should be greater than 3 characters";

    if (filter_var($user->email, FILTER_VALIDATE_EMAIL) === FALSE) 
        $result .= "\n email is invalid";

    $sql ="SELECT Count(*) as count FROM user WHERE email = '".$user->email."' ";

    $stmt = getConn()->query($sql);

    $value = $stmt->fetchAll(PDO::FETCH_OBJ);


    if($value[0]->count > 0)
        $result .= "\n Email is not available";


    if(strlen($result) > 0)
    {
        print_r($result);
        exit();
    }

}

function logIn()
{
    $request = \Slim\Slim::getInstance()->request();

    $user = json_decode($request->getBody());

    $stmt = getConn()->query("SELECT *, CONCAT(UUID(), UUID()) as Token FROM user WHERE email = '".$user->email."' ");

    $result = $stmt->fetchAll(PDO::FETCH_OBJ);

    if(count($result) <= 0)
    {
        print_r("user not found");
        exit();
    }


    if($result[0]->Password !== md5($user->password))
    {
        print_r("password invalid");
        exit();   
    }

    echo json_encode($result[0]);
}


function addUser()
{
    $request = \Slim\Slim::getInstance()->request();

    $user = json_decode($request->getBody());

    verifyIfUserIsValid($user);

    $user->password = md5($user->password);

    $sql = "INSERT INTO user (name,email,password) values (:name,:email,:password) ";
    $conn = getConn();

    $stmt = $conn->prepare($sql);

    $stmt->bindParam("name",$user->name);
    $stmt->bindParam("email",$user->email);
    $stmt->bindParam("password",$user->password);
    $stmt->execute();

    $user->id = $conn->lastInsertId();

    foreach ($user->contacts as &$contact) 
    {
    	$sql = "INSERT INTO contact (description,value,user_id) values (:description,:value,:user_id) ";

    	$stmt = $conn->prepare($sql);

    	$stmt->bindParam("description",$contact->description);
		$stmt->bindParam("value",$contact->value);
		$stmt->bindParam("user_id",$user->id);
		$stmt->execute();

		$contact->id = $conn->lastInsertId();
	}

    echo json_encode($user);
}