<?php
  // ini_set('display_startup_errors', 1);
  // ini_set('display_errors', 1);
  // error_reporting(-1);

  require_once __DIR__.'/config.php';
  require_once __DIR__.'/_post.php';
  require_once __DIR__.'/_get.php';

  if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if (!isset($_SERVER['CONTENT_TYPE']) || $_SERVER['CONTENT_TYPE'] != 'application/json') {
      http_response_code(406);
      exit();
    }

    try {
      $pdo = new PDO('mysql:host=localhost;dbname=OfficeTemp', DB_USERNAME, DB_PASSWORD);
    } catch (PDOException $e) {
      http_response_code(500);
      exit('Unable to connect to database');
    }
    $post = new Post($pdo);
    $created = $post->create(file_get_contents("php://input"));
    if ($created == null) {
      http_response_code(204);
      exit();
    }

    http_response_code(200);
    header('Content-Type: application/json');
    exit(json_encode($created));
  } else if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $returnJson = true;
    $slack = true;
    if (isset($_SERVER['CONTENT_TYPE']) && $_SERVER['CONTENT_TYPE'] != 'application/json') {
      $returnJson = false;
    }
    if (isset($_GET['slack']) && $_GET['slack'] == 'false') {
      $slack = false;
    }
    if (isset($_GET['token']) && SLASH_TOKEN != $_GET['token']) {
      http_response_code(400);
      exit('Slack token invalid');
    }

    try {
      $pdo = new PDO('mysql:host=localhost;dbname=OfficeTemp', DB_USERNAME, DB_PASSWORD);
    } catch (PDOException $e) {
      http_response_code(500);
      exit('Unable to connect to database');
    }

    $get = new Get($pdo);
    $data = $get->getLast();
    if ($data == null) {
      http_response_code(204);
      exit();
    }

    http_response_code(200);
    if ($returnJson) {
      header('Content-Type: application/json');
      $res = $slack ? $data->toSlack() : $data;
      exit(json_encode($res));
    }
    header('Content-Type: text/plain');
    exit($data);
  } else {
    http_response_code(405);
    exit();
  }

?>
