<?php
	
function getConn()
{
	
	return new PDO('mysql:host=localhost;dbname=campo485_repeticaoespacada',
		'campo485',
		'ql8FU04r3u',
		array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8")
	);

	return new PDO('mysql:host=127.0.0.1;dbname=spacedrepetition',
		'root',
		'lexos2009',
		array(PDO::MYSQL_ATTR_INIT_COMMAND => "SET NAMES utf8")
	);

}

?>